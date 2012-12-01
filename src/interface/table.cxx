#include <sql/impl/database.hpp>
#include <sql/interface/interface.hpp>

#if !defined(SQL_CONFIG_HPP_)
#	define SQL_CONFIG_HPP_
#	include <sql/config.hpp>
#endif

table::table(std::string const & name)
	: name_(name)
{
	
}
	
std::list<std::string> table::get_fields() const
{
	std::list<std::string> result;
	for ( std::map<abstract_field*, std::string>::const_iterator it = fields.begin(), end = fields.end(); it != end; ++it)
	{
#if defined(STD_LIST_HAS_EMPLACE)
		result.emplace_back(it->second);
#else
		result.push_back(it->second);
#endif
	}
	return result;
}

std::list<abstract_field*> table::get_field_pointers() const
{
	std::list<abstract_field*> result;
	for (std::map<abstract_field*, std::string>::const_iterator it(fields.begin()),
		end(fields.end()); it != end; ++it)
	{
#if defined(STD_LIST_HAS_EMPLACE)
		result.emplace_back(it->first);
#else
		result.push_back(it->first);
#endif
	}
	return result;   
}

void table::bind_to(query * qry)
{
	for (std::map<abstract_field*, std::string>::const_iterator it(fields.begin()),
		end = fields.end(); it != end; ++it)
	{
		it->first->bind_to(qry);
	}
}

int table::add_column(abstract_field* fld, std::string const & name)
{
	int pos = fields.size();
	fields.insert(std::make_pair(fld, name));
	return pos;
}

void table::create(database * dbptr)
{
	dbptr->get_dialect()->create_table(name_, get_fields());
}

void table::drop(database * dbptr)
{
	dbptr->get_dialect()->drop_table(name_);
}

void table::insert(database * dbptr)
{
	::query * qry = dbptr->get_dialect()->insert_stmt(name(), get_fields());
	bind_to(qry);
	qry->bind_all();
	qry->run();
	delete qry;
}

void table::load(query * qry)
{
	unsigned int i = 0;
	for (std::map<abstract_field*, std::string>::const_iterator it(fields.begin()),
		end(fields.end()); it != end; ++it)
	{
		abstract_field * f = it->first;
		f->get_value(qry);
	}
}


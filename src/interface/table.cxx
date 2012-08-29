#include <sql/impl/database.hpp>
#include <sql/interface/interface.hpp>

table::table(std::string const & name)
	: name_(name)
{
	
}
	
std::list<std::string> table::get_fields() const
{
	std::list<std::string> result;
	for ( std::map<abstract_field*, std::string>::const_iterator it = fields.begin(), end = fields.end(); it != end; ++it)
	{
		result.push_back(it->second);
	}
	return result;
}

std::list<abstract_field*> table::get_field_pointers() const
{
	std::list<abstract_field*> result;
	for (std::map<abstract_field*, std::string>::const_iterator it(fields.begin()),
		end(fields.end()); it != end; ++it)
	{
		result.push_back(it->first);
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
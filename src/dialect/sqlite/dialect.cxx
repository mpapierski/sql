#include <sstream>
#include <stdexcept>
#include <cassert>
#include <stdexcept>
#include <sql/utils/url.hpp>
#include <sql/interface/interface.hpp>
#include <sql/dialect/sqlite/detail/dialect.hpp>
#include <sql/dialect/sqlite/detail/query.hpp>

sqlite_dialect::sqlite_dialect(url const & address)
	: address_(address)
	, connection_(0)
{
	std::string db = address_.path_;
	if (db == "/:memory:") db = ":memory:";
	if (sqlite3_open(db.c_str(), &connection_) != SQLITE_OK)
	{
		throw std::logic_error("Unable to connect to SQLite database " + db);
	}
}

sqlite_dialect::~sqlite_dialect()
{
	if (!connection_)
		return;
	sqlite3_close(connection_);
}

::query * sqlite_dialect::query_factory()
{
	return new sqlite_query(this);
}

void sqlite_dialect::execute(std::string const & stmt)
{
	char * err = 0;
	int result = sqlite3_exec(
		connection_,
		stmt.c_str(),
		0,
		0,
		&err);
	if (err)
	{
		std::string ss = err;
		sqlite3_free(err);
		throw std::logic_error(ss);
	}
}

void sqlite_dialect::create_table(std::string const & tbl_name, std::list<std::string> const & cols)
{
	std::stringstream ss;
	ss << "CREATE TABLE IF NOT EXISTS \"" << tbl_name << "\" (";
	for (std::list<std::string>::const_iterator it(cols.begin()),
		end(cols.end()); it != end; ++it)
	{
		ss << *it;
		std::list<std::string>::const_iterator it2 = it;
		if (++it2 == end)
			break;
		ss << ", ";
	}
	ss << ")";
	execute(ss.str());
}

::query * sqlite_dialect::insert_stmt(std::string const & tbl_name, std::list<std::string> const & fields)
{
	::query * result = query_factory();
	assert(result);
	std::stringstream ss, placeholders;
	ss << "INSERT INTO \"" << tbl_name << "\" (";
	for (std::list<std::string>::const_iterator it = fields.begin(), end = fields.end(); it != end; ++it)
	{
		ss << "\"" << *it << "\"";
		placeholders << result->next_placeholder();
		std::list<std::string>::const_iterator it2 = it;
		if (++it2 == end)
			break;
		ss << ", ";
		placeholders << ", ";
	}
	ss << ") VALUES (" << placeholders.str() << ")";
	result->prepare(ss.str());
	return result;
}
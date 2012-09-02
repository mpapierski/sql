#include <stdexcept>
#include <sstream>
#include <cassert>
#include <sql/dialect/sqlite/detail/dialect.hpp>
#include <sql/dialect/sqlite/detail/query.hpp>

sqlite_query::sqlite_query(sqlite_dialect * d)
	: dialect_(d)
	, placeholder_(0)
	, binding_(0)
	, stmt_(0)
	, results_(0)
{
	
}

sqlite_query::~sqlite_query()
{
	int result = sqlite3_finalize(stmt_);
	if (result == SQLITE_OK)
		return;
	// ???
}

void sqlite_query::bind_int(int value)
{
	assert(stmt_);
	int result = sqlite3_bind_int(stmt_, ++binding_, value);
	if (result != SQLITE_OK)
	{
		std::stringstream ss;
		ss << "Unable to bind value " << value << " at " << binding_ << " placeholder."; 
		throw std::runtime_error(ss.str());
	}
}

void sqlite_query::bind_null()
{
	assert(stmt_);
	int result = sqlite3_bind_null(stmt_, ++binding_);
	if (result != SQLITE_OK)
	{
		std::stringstream ss;
		ss << "Unable to bind NULL value at " << binding_ << " placeholder."; 
		throw std::runtime_error(ss.str());
	}
}

void sqlite_query::bind_text(const char * value, int length)
{
	assert(stmt_);
	int result = sqlite3_bind_text(stmt_, ++binding_, value, length, SQLITE_STATIC);
	if (result != SQLITE_OK)
	{
		std::stringstream ss;
		ss << "Unable to bind value " << value << " at " << binding_ << " placeholder."; 
		throw std::runtime_error(ss.str());
	}
}
    
void sqlite_query::execute(std::string const & q)
{
	int result = sqlite3_exec(
		dialect_->connection_,
		q.c_str(),
		0,
		0,
		0);
	(void)result;
	// ???
}
    
void sqlite_query::prepare(std::string const & q)
{
	int result = sqlite3_prepare_v2(
		dialect_->connection_,
		q.c_str(),
		q.size(),
		&stmt_,
		0);
	if (result != SQLITE_OK)
	{
		std::string const & msg = sqlite3_errmsg(dialect_->connection_);
		throw std::runtime_error(msg);
	}
}
    
std::string sqlite_query::next_placeholder()
{
	std::stringstream ss;
	ss << "?" << ++placeholder_;
	return ss.str();
}
    
void sqlite_query::run()
{
	assert(stmt_);
	results_ = false;
	int result = sqlite3_step(stmt_);
	switch (result)
	{
		case SQLITE_BUSY:
			throw std::runtime_error("Database is busy.");
		case SQLITE_DONE:
			return;    
		case SQLITE_ERROR:
		{
			std::string const & msg = sqlite3_errmsg(dialect_->connection_);
			throw std::runtime_error(msg);
		}
		case SQLITE_OK:
			break;
		case SQLITE_ROW:
			results_ = true;
			break;
		default:
			break; 
	}
}
    
int sqlite_query::column_type(int column)
{
	assert(stmt_);
	return sqlite3_column_type(stmt_, column);
}

bool sqlite_query::is_null(int index)
{
	assert(stmt_);
	return column_type(index) == SQLITE_NULL;
}

void sqlite_query::get_int(int index, int & result)
{
	assert(stmt_);
	result = sqlite3_column_int(stmt_, index);
}

void sqlite_query::get_string(int index, std::string & result) 
{
	const unsigned char * data = sqlite3_column_text(stmt_, index);
	const char * ch = reinterpret_cast<const char *>(data);
	std::string tmp(ch);
	using std::swap;
	std::swap(result, tmp);
}

dialect * sqlite_query::get_dialect()
{
	return dialect_;
}

void sqlite_query::reset()
{
	assert(stmt_);
	if (sqlite3_reset(stmt_) != SQLITE_OK)
	{
		std::string const & msg = sqlite3_errmsg(dialect_->connection_);
		throw std::runtime_error(msg);
	}
}
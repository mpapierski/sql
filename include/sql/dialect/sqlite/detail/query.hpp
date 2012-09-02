#if !defined(SQL_DIALECT_SQLITE_DETAIL_QUERY_INCLUDED_)
#define SQL_DIALECT_SQLITE_DETAIL_QUERY_INCLUDED_

#include <string>
#include <sqlite3.h>
#include <sql/interface/detail/dialect.hpp>
#include <sql/interface/detail/query.hpp>

struct sqlite_dialect;

struct sqlite_query: query
{
	sqlite_dialect * dialect_;
	unsigned int placeholder_;
	unsigned int binding_;
	sqlite3_stmt * stmt_;
	bool results_;
	sqlite_query(sqlite_dialect * d);
	virtual ~sqlite_query();
	void bind_int(int value);
	void bind_null();
	void bind_text(const char * value, int length);
	void execute(std::string const & q);
	void prepare(std::string const & q);
	std::string next_placeholder();
	void run();
	virtual bool has_results() { return results_; }
	int column_type(int column);
	virtual bool is_null(int index);
	virtual void get_int(int index, int & result);
	virtual void get_string(int index, std::string & result);
	dialect * get_dialect();
	
	/**
	 * Reset statement
	 */
	virtual void reset();
};

#endif
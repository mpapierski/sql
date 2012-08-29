#if !defined(SQL_DIALECT_SQLITE_DETAIL_DIALECT_)
#define SQL_DIALECT_SQLITE_DETAIL_DIALECT_

#include <string>
#include <list>
#include <sqlite3.h>
#include <sql/utils/url.hpp>
#include <sql/interface/detail/dialect.hpp>

struct sqlite_dialect: dialect
{
    url address_;
    sqlite3 * connection_;
    
    sqlite_dialect(url const & address);
    virtual ~sqlite_dialect();
    
    virtual void execute(std::string const & stmt);
    virtual query * query_factory();
    
    virtual void create_table(std::string const & tbl_name, std::list<std::string> const & cols);
	
	virtual ::query * insert_stmt(std::string const & tbl_name, std::list<std::string> const & fields);
	sqlite3* get_connection() const { return connection_; }
};

#endif /* SQL_DIALECT_SQLITE_DETAIL_DIALECT_ */

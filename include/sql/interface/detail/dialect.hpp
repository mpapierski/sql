#if !defined(SQL_INTERFACE_DIALECT_INCLUDED_)
#define SQL_INTERFACE_DIALECT_INCLUDED_

#include <string>
#include <list>

struct query;

/**
 * Base interface for SQL dialects
 */
struct dialect
{
	/**
	 * Execute single statement
	 * @param qry SQL query
	 */
	virtual void execute(std::string const & qry) = 0;
	virtual ~dialect() {}
	/**
	 * Create new dialect-specific query instance.
	 * @return New query instance. The memory should be maintained by the caller.
	 */
	virtual query * query_factory() = 0;
	/**
	 * Execute "CREATE TABLE" statement
	 * @todo Constraint support, probably pass in list of abstract_fields
	 * @param tbl_name Table name
	 * @param cols Column names
	 */
	virtual void create_table(std::string const & tbl_name, std::list<std::string> const & cols) = 0;
	 
	/**
	 * Execute "DROP TABLE" statement
	 * @param tbl_name Table name
	 */
	virtual void drop_table(std::string const & tbl_name) = 0;
	
	/**
	 * Create new "INSERT INTO" statement from table name and column names.
	 * For each column generate a new placeholder (for example ?1, ?2, ?3).
	 * Later fields from the SQL model are bound to the placeholders.
	 * @param tbl_name Table name
	 * @param cols Column names
	 * @return Query instance. The memory should be maintained by the caller.
	 */
	virtual query * insert_stmt(std::string const & tbl_name, std::list<std::string> const & cols) = 0;
};

#endif /* SQL_INTERFACE_DIALECT_INCLUDED_ */

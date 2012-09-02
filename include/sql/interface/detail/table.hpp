#if !defined(SQL_INTERFACE_TABLE_INCLUDED_)
#define SQL_INTERFACE_TABLE_INCLUDED_

#include <string>
#include <map>
#include <list>

struct abstract_field;
struct query;
struct database;

struct table
{
	std::string name_;
	std::map<abstract_field*, std::string> fields;
	/**
	 * Get table name
	 * @return Table name
	 */
	inline std::string const & name() const { return name_; }
	/**
	 * Table constructor
	 * @param name Table name
	 */ 
	table(std::string const & name);
	/**
	 * Add new column to the table schema
	 * @param fld Pointer to field instance
	 * @param name Field name
	 * @return Position of the field.
	 */
	int add_column(abstract_field* fld, std::string const & name);
    
	std::list<std::string> get_fields() const;
	std::list<abstract_field*> get_field_pointers() const;
    
	void bind_to(query * qry);
	void load(query * qry);
	
	/**
	 * Issue CREATE TABLE statement on a database.
	 */
	void create(database * dbptr);
	 
	/**
	 * Issue DROP TABLE statement on a database.
	 */
	void drop(database * dbptr);
	 
	/**
	 * Issue INSERT INTO statement on a database.
	 */
	void insert(database * dbptr);
};

#endif /* SQL_INTERFACE_BINDER_INCLUDED_ */

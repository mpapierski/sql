#if !defined(SQL_IMPL_INCLUDED_)
#define SQL_IMPL_INCLUDED_

#include <string>
#include <sql/query/query_wrapper.hpp>

struct database;
struct query;

struct session
{
	database* db_;
	session(database* db);
	~session();
	void commit();
	::query * new_query();   
	template <typename T>
	query_wrapper<T> query()
	{
		::query * qry = this->new_query();
		query_wrapper<T> wrapped(qry);
		return wrapped;
	}
	
	template <typename T>
	void create_table()
	{
		T t;
		t.create(db_);
	}
	
	template <typename T>
	void add(T & model_inst);
	void execute(std::string const & q);
};

#endif /* SQL_IMPL_INCLUDED_ */
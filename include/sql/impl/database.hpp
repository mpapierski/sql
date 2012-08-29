#if !defined(SQL_IMPL_DATABASE_INCLUDED_)
#define SQL_IMPL_DATABASE_INCLUDED_

#include <sql/utils/url.hpp>
#include <sql/impl/session.hpp>

struct dialect;

struct database
{
	dialect* dialect_;
	url address_;
	database(std::string const & addr);
	~database();
	
	void execute(std::string const & stmt);
	
	::session session();
	
	query * query_factory();
	
	dialect * get_dialect();
};

#endif /* SQL_IMPL_DATABASE_INCLUDED_ */

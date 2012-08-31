#include <sql/interface/detail/dialect.hpp>
#include <sql/impl/database.hpp>
#include <sql/impl/session.hpp>

session::session(database* db)
	: db_(db)
{
	
}

session::~session()
{
	
}

void session::execute(std::string const & q)
{
    db_->dialect_->execute(q);
}

::query * session::new_query()
{
	return db_->query_factory();
}
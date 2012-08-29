#include <stdexcept>
#include <cassert>
#include <sql/dialect/sqlite/detail/dialect.hpp>
#include <sql/impl/database.hpp>

database::database(std::string const & addr)
	: dialect_(0)
	, address_(addr)
{
	if (address_.protocol_ == "sqlite")
	{
		dialect_ = new sqlite_dialect(address_);
		return;
	}	
	throw std::runtime_error("Unsupported database engine: " + address_.protocol_);
}

database::~database()
{
	if (!dialect_)
		return;
	delete dialect_;
}

void database::execute(std::string const & stmt)
{
	// TODO
}

query * database::query_factory()
{
	assert(dialect_);
	return dialect_->query_factory();
}

::session database::session()
{
	assert(dialect_);
	return ::session(this);
}

dialect * database::get_dialect()
{
	assert(dialect_);
	return dialect_;
}
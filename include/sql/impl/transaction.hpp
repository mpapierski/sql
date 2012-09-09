#if !defined(SQL_IMPL_TRANSACTION_HPP_INCLUDED_)
#define SQL_IMPL_TRANSACTION_HPP_INCLUDED_

#include <sql/impl/session.hpp>

/**
 * RAII transaction guard.
 * Use it at the beggining of the scope, and if there was exception thrown the
 * current transaction will be rolled back.
 */
class transaction
{
private:
	session * session_;
	volatile bool safe_;
	transaction(transaction const &);
	transaction & operator==(transaction const &);
public:
	explicit transaction(session * s)
		: session_(s)
		, safe_(false)
	{
		s->begin();
	}

	~transaction()
	{
		if (!safe_)
		{
			session_->rollback();
		}
	}

	inline void commit()
	{
		session_->commit();
		safe_ = true;
	}
};

#endif /* SQL_IMPL_TRANSACTION_HPP_INCLUDED_ */
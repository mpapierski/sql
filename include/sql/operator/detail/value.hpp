#if !defined(SQL_EXPRESSION_DETAIL_VALUE_)
#define SQL_EXPRESSION_DETAIL_VALUE_

#include <cassert>
#include <sql/interface/interface.hpp>

/**
 * Value node wrapper.
 * When evaluated a new late binder is added to the query.
 * and returns new placeholder value which is dialect-specific.
 */
template <typename T>
struct value_impl
{
	T value_;

	/**
	 * You can pass any value and it will be valid as long as
	 * type T could be copy-constructed from type F.
	 */
	template <typename F>
	value_impl(F const & t)
		: value_(t)
	{
		
	}
	
	template <typename F>
	std::string operator()(F const & model_inst, query * & qry)
	{
		assert(qry);
		qry->add_bind(new binder<T>(value_));
		return qry->next_placeholder();
	}
};

#endif /* SQL_EXPRESSION_DETAIL_VALUE_ */
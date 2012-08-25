#if !defined(SQL_EXPRESSION_DETAIL_VALUE_)
#define SQL_EXPRESSION_DETAIL_VALUE_

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
	value_impl(T const & t)
		: value_(t)
	{
		
	}
	
	template <typename F>
	std::string operator()(F const & model_inst, query * qry)
	{
		qry->binders_.push_back(new binder<T>(value_));
		return qry->next_placeholder();
	}
};

#endif /* SQL_EXPRESSION_DETAIL_VALUE_ */
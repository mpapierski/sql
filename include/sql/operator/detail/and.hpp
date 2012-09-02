#if !defined(SQL_EXPRESSION_DETAIL_AND_)
#define SQL_EXPRESSION_DETAIL_AND_

#include <sql/operator/aux/nest.hpp>

struct query;

template <typename T1, typename T2>
struct and_impl
{
	typedef and_impl<T1, T2> this_type;
	
	T1 t1_;
	T2 t2_;
	nest_function_t nest_;
	template <typename F1, typename F2, typename F3>
	and_impl(and_impl<F1, F2> const & t1, F3 const & t2)
		: t1_(t1)
		, t2_(t2)
		, nest_(&nest_impl<true, false>)
	{
		
	}
	
	template <typename F1, typename F2, typename F3>
	and_impl(F1 const & t1, and_impl<F1, F2> const & t2)
		: t1_(t1)
		, t2_(t2)
		, nest_(&nest_impl<false, true>)
	{
		
	}
	
	template <typename F1, typename F2, typename F3, typename F4>
	and_impl(and_impl<F1, F2> const & t1, and_impl<F3, F4> const & t2)
		: t1_(t1)
		, t2_(t2)
		, nest_(&nest_impl<true, true>)
	{
		
	}
	
	template <typename F1, typename F2>
	and_impl(F1 const & t1, F2 const & t2)
		: t1_(t1)
		, t2_(t2)
		, nest_(&nest_impl<false, false>) { }
	
	template <typename F1, typename F2, typename F3>
	and_impl(or_impl<F1, F2> const & t1, F3 const & t2)
		: t1_(t1)
		, t2_(t2)
		, nest_(&nest_impl<true, false>)
	{
		
	}
	
	template <typename F1, typename F2, typename F3>
	and_impl(F1 const & t1, or_impl<F1, F2> const & t2)
		: t1_(t1)
		, t2_(t2)
		, nest_(&nest_impl<false, true>)
	{
		
	}
	
	template <typename F1, typename F2, typename F3, typename F4>
	and_impl(or_impl<F1, F2> const & t1, or_impl<F3, F4> const & t2)
		: t1_(t1)
		, t2_(t2)
		, nest_(&nest_impl<true, true>)
	{
		
	}
	
	template <typename T>
	std::string operator()(T const & model_inst, query * args)
	{
		std::string const & lhs = t1_(model_inst, args);
		std::string const & rhs = t2_(model_inst, args);
		nest_pair_t const & e = (*nest_)(lhs, rhs);
		return e.first + " AND " + e.second;
	}
};

#endif /* SQL_EXPRESSION_DETAIL_AND_ */

#if !defined(SQL_EXPRESSION_DETAIL_OR_)
#define SQL_EXPRESSION_DETAIL_OR_

struct query;

template <typename T1, typename T2>
struct or_impl
{
	T1 t1_;
	T2 t2_;
	nest_function_t nest_;
	template <typename F1, typename F2, typename F3>
	or_impl(or_impl<F1, F2> const & t1, F3 const & t2)
		: t1_(t1)
		, t2_(t2)
		, nest_(&nest_impl<!false, false>)
	{
		
	}
	
	template <typename F1, typename F2, typename F3>
	or_impl(F1 const & t1, or_impl<F1, F2> const & t2)
		: t1_(t1)
		, t2_(t2)
		, nest_(&nest_impl<false, true>)
	{
		
	}
	template <typename F1, typename F2, typename F3, typename F4>
	or_impl(or_impl<F1, F2> const & t1, or_impl<F3, F4> const & t2)
		: t1_(t1)
		, t2_(t2)
		, nest_(&nest_impl<true, true>)
	{
		
	}
	
	template <typename F1, typename F2>
	or_impl(F1 const & t1, F2 const & t2)
		: t1_(t1)
		, t2_(t2)
		, nest_(&nest_impl<false, false>)
	{
		
	}
	
	template <typename T>
	std::string operator()(T const & model_inst, query * args)
	{
		std::string const & lhs = t1_(model_inst, args);
		std::string const & rhs = t2_(model_inst, args);
		nest_pair_t const & e = (*nest_)(lhs, rhs);
		return e.first + " OR " + e.second;
	}
};

#endif /* SQL_EXPRESSION_DETAIL_OR_ */

#if !defined(SQL_EXPRESSION_DETAIL_EQ_)
#define SQL_EXPRESSION_DETAIL_EQ_

struct query;

template <typename T1, typename T2>
struct eq_impl
{
	typedef eq_impl<T1, T2> this_type;
	
	T1 t1_;
	T2 t2_;
	eq_impl(T1 const & t1, T2 const & t2)
		: t1_(t1)
		, t2_(t2)
	{
		
	}
	
	template <typename T>
	std::string operator()(T const & model_inst, query * args)
	{
		std::string const & lhs = t1_(model_inst, args);
		std::string const & rhs = t2_(model_inst, args);
		return lhs + " = " + rhs;
	}
};

#endif /* SQL_EXPRESSION_DETAIL_EQ_ */

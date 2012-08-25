#if !defined(SQL_EXPRESSION_AUX_NEST_)
#define SQL_EXPRESSION_AUX_NEST_

/**
 * This method is used for conditional nesting results of
 * evaluated expression nodes.
 * This behaviour is not dialect-specific.
 * For example nest_impl<false, true>("a", "b") returns "(a)", "b" 
 */

typedef std::pair<std::string, std::string> nest_pair_t;
typedef nest_pair_t(*nest_function_t)(std::string const &, std::string const &);

template <bool Lhs, bool Rhs>
nest_pair_t nest_impl(std::string const & t1, std::string const & t2);

template <>
nest_pair_t nest_impl<true, true>(std::string const & t1, std::string const & t2)
{
	return std::make_pair(t1, t2);
}    

template <>
nest_pair_t nest_impl<false, true>(std::string const & t1, std::string const & t2)
{
	return std::make_pair("(" + t1 + ")", t2);
}

template <>
nest_pair_t nest_impl<false, false>(std::string const & t1, std::string const & t2)
{
	return std::make_pair("(" + t1 + ")", "(" + t2 + ")");
}

template <>
nest_pair_t nest_impl<true, false>(std::string const & t1, std::string const & t2)
{
	return std::make_pair(t1, "(" + t2 + ")");
}

#endif /* SQL_EXPRESSION_AUX_NEST_ */
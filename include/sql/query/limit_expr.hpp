#if !defined(SQL_QUERY_LIMIT_EXPR_INCLUDED_)
#define SQL_QUERY_LIMIT_EXPR_INCLUDED_

#include <sstream>
#include <string>

template <typename Lhs>
struct limit_expr
{
	typedef typename Lhs::model_type model_type;
	typedef limit_expr<Lhs> this_type;
	
	Lhs lhs_;
	int value_;
	
	limit_expr(Lhs const & lhs, int value)
		: lhs_(lhs)
		, value_(value)
	{
	}
	
	template <typename T>
	std::string operator()(T const & model_inst, query * args)
	{
		std::string const & e = lhs_(model_inst, args);
		std::stringstream ss;
		ss << e << " LIMIT " << value_;
		return ss.str();
	}
	
	query * get_query()
	{
		return lhs_.get_query();
	}
};

#endif /* SQL_QUERY_LIMIT_EXPR_INCLUDED_ */
#if !defined(SQL_QUERY_EXPR_WRAPPER_INCLUDED_)
#define SQL_QUERY_EXPR_WRAPPER_INCLUDED_

#include <sstream>
#include <string>

#include <sql/query/limit_expr.hpp>
#include <sql/query/count_expr.hpp>

template <typename Lhs, typename T>
struct expr_wrapper
{
	typedef typename Lhs::model_type model_type;
	typedef expr_wrapper<Lhs, T> this_type;
	
	Lhs lhs_;
	T t_;
	
	expr_wrapper(Lhs const & lhs, T const & t)
		: lhs_(lhs)
		, t_(t)
	{
		
	}
	
	template <typename F>
	std::string operator()(F const & model_inst, query * qry)
	{
		std::stringstream ss;
		ss << "SELECT " << lhs_.fields_stmt << " FROM \"" << model_inst.name() << "\" WHERE " << t_(model_inst, qry);        
		return ss.str();
	}
	
	limit_expr<this_type> limit(int N)
	{
		return limit_expr<this_type>(*this, N);
	}
	
	int count()
	{
		return count_expr<this_type>(*this)(model_type(), get_query());
	}
	
	query * get_query()
	{
		return lhs_.get_query();
	}
};

#endif /* SQL_QUERY_EXPR_WRAPPER_INCLUDED_ */
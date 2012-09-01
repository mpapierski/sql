#if !defined(SQL_QUERY_COUNT_EXPR_INCLUDED_)
#define SQL_QUERY_COUNT_EXPR_INCLUDED_

#include <string>
#include <sstream>

template <typename Lhs>
struct count_expr
{
	typedef typename Lhs::model_type model_type;
	typedef count_expr<Lhs> this_type;
	
	Lhs lhs_;
		
	count_expr(Lhs const & lhs)
		: lhs_(lhs)
	{
		
	}
	
	template <typename F>
	int operator()(F const & model_inst, query * qry)
	{
		std::stringstream ss;
		ss << "SELECT COUNT(*) FROM \"" << model_inst.name() << "\"";
		qry->prepare(ss.str());
		qry->bind_all();
		qry->run();
		int result = 0;
		qry->get_int(0, result);
		return result;
	}
	
	query * get_query()
	{
		return lhs_.get_query();
	}
};


#endif /* SQL_QUERY_COUNT_EXPR_INCLUDED_ */
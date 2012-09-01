#if !defined(SQL_QUERY_ALL_INCLUDED_)
#define SQL_QUERY_ALL_INCLUDED_

#include <string>
#include <iostream>

template <typename Lhs>
struct all_expr
{
	typedef typename Lhs::model_type model_type;
	typedef all_expr<Lhs> this_type;
	
	Lhs lhs_;
		
	all_expr(Lhs const & lhs)
		: lhs_(lhs)
	{
		
	}
	
	template <typename F>
	std::string operator()(F const & model_inst, query * qry)
	{
		std::stringstream ss;
		ss << "SELECT " << lhs_.fields_stmt << " FROM \"" << model_inst.name() << "\"";
		return ss.str();
	}
	
	query * get_query()
	{
		return lhs_.get_query();
	}
};


#endif /* SQL_QUERY_ALL_INCLUDED_ */
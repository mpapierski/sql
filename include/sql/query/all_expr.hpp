#if !defined(SQL_QUERY_ALL_INCLUDED_)
#define SQL_QUERY_ALL_INCLUDED_

#include <string>

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
		return lhs_(model_inst, qry);
	}
	
	query * get_query()
	{
		return lhs_.get_query();
	}
	
	void set_query(query * ptr)
	{
		lhs_.set_query(ptr);
	}
};


#endif /* SQL_QUERY_ALL_INCLUDED_ */
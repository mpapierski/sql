#if !defined(SQL_QUERY_COUNT_EXPR_INCLUDED_)
#define SQL_QUERY_COUNT_EXPR_INCLUDED_

#include <string>
#include <sstream>

#if !defined(SQL_CONFIG_HPP_)
#	define SQL_CONFIG_HPP_
#	include <sql/config.hpp>
#endif

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
		std::list<std::string> new_fields;
#if defined(STD_LIST_HAS_EMPLACE)
		new_fields.emplace_back("COUNT(*)");
#else
		new_fields.push_back("COUNT(*)");
#endif
		lhs_.set_fields(new_fields);		
		std::string const & e = lhs_(model_inst, qry);
		qry->prepare(e);
		qry->bind_all();
		qry->run();
		int result = 0;
		qry->get_int(0, result);
		qry->reset();
		set_query(0);
		return result;
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


#endif /* SQL_QUERY_COUNT_EXPR_INCLUDED_ */
#if !defined(SQL_QUERY_QUERY_WRAPPER_INCLUDED_)
#define SQL_QUERY_QUERY_WRAPPER_INCLUDED_

#include <sstream>
#include <list>
#include <string>
#include <sql/interface/detail/query.hpp>
#include <sql/query/expr_wrapper.hpp>
#include <sql/query/all_expr.hpp>

template <typename T>
struct query_wrapper
{
	typedef T model_type;
	typedef query_wrapper<T> this_type;
	std::list<std::string> fields_;
	query * qry_;
	std::string fields_stmt;
	query_wrapper(query * qry)
		: qry_(qry)
	{
		std::list<std::string> const & fields = model_type().get_fields();
		std::stringstream ss;
		for (std::list<std::string>::const_iterator it = fields.begin(), end = fields.end(); it != end; ++it)
		{
			ss << "\"" << *it << "\"";
			std::list<std::string>::const_iterator it2 = it;
			if (++it2 == end) break;
			ss << ", ";
		}
		fields_stmt = ss.str();
	}
	query * get_query() { return qry_; }
	
	template <typename F>
	expr_wrapper<this_type, F> filter(F f)
	{
		return expr_wrapper<this_type, F>(*this, f);
	}
	
	all_expr<this_type> all()
	{
		return all_expr<this_type>(*this);
	}
};

#endif /* SQL_QUERY_QUERY_WRAPPER_INCLUDED_ */
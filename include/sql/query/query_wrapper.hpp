#if !defined(SQL_QUERY_QUERY_WRAPPER_INCLUDED_)
#define SQL_QUERY_QUERY_WRAPPER_INCLUDED_

#include <sstream>
#include <list>
#include <string>
#include <sql/interface/detail/query.hpp>
#include <sql/query/expr_wrapper.hpp>
#include <sql/query/count_expr.hpp>
#include <sql/query/all_expr.hpp>

template <typename T>
struct query_wrapper
{
	typedef T model_type;
	typedef query_wrapper<T> this_type;
	std::list<std::string> fields_;
	std::string tbl_name_;
	query * qry_;
	query_wrapper(query * qry)
		: qry_(qry)
	{
		model_type const & tmp = model_type();
		fields_ = tmp.get_fields();
		tbl_name_ = tmp.name();
		
		// Add trailing ""'s to all columns.
		for (std::list<std::string>::iterator it(fields_.begin()),
			end(fields_.end()); it != end; ++it)
		{
			*it = "\"" + *it + "\"";
		}
	}
	
	query * get_query()
	{
		return qry_;
	}
	
	void set_fields(std::list<std::string> const & f)
	{
		fields_ = f;
	}
	
	/**
	 * Return "FIELDS" statement.
	 * Concatenate all cached columns from model with a ", ".
	 * When query_wrapper is evaluated these fields could be anything.
	 * IE. '1' when evaluating EXISTS, COUNT(*) when evaluating count expression.
	 */
	std::string get_fields_stmt() const
	{
		std::stringstream ss;
		for (std::list<std::string>::const_iterator it(fields_.begin()),
			end(fields_.end()); it != end; ++it)
		{
			ss << *it;
			std::list<std::string>::const_iterator it2 = it;
			if (++it2 == end) break;
			ss << ", ";
		}
		return ss.str();
	}
	
	template <typename F>
	std::string operator()(F const &, query *) const
	{
		return "SELECT " + get_fields_stmt() + " FROM " + tbl_name_;
	}
	
	template <typename F>
	expr_wrapper<this_type, F> filter(F f)
	{
		return expr_wrapper<this_type, F>(*this, f);
	}
	
	all_expr<this_type> all()
	{
		return all_expr<this_type>(*this);
	}
	
	int count()
	{
		return count_expr<this_type>(*this)(model_type(), get_query());
	}
};

#endif /* SQL_QUERY_QUERY_WRAPPER_INCLUDED_ */
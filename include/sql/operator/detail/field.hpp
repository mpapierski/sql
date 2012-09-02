#if !defined(SQL_EXPRESSION_DETAIL_FIELD_)
#define SQL_EXPRESSION_DETAIL_FIELD_

#include <sql/impl/field.hpp>

struct query;

/**
 * Lazy pointer-to-member variable wrapper.
 * Evaluates to the declared field name.
 */
template <typename T, typename Cls>
struct field_impl
{
	typedef field_impl<T, Cls> this_type;
	
	typedef field<T> Cls::*member_field_t;
	member_field_t field_;
	
	field_impl(member_field_t fld)
		: field_(fld)
	{
		
	}

	template <typename F>
	std::string operator()(F const & model_inst, query * args)
	{
		std::string const & name = (model_inst.*field_).name();
		return "\"" + name + "\"";
	}
};

#endif /* SQL_EXPRESSION_DETAIL_FIELD_ */

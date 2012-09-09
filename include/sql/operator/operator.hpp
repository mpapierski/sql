#if !defined(SQL_EXPRESSION_OPERATORS_)
#define SQL_EXPRESSION_OPERATORS_

#include <sql/operator/aux/nest.hpp>
#include <sql/operator/detail/or.hpp>
#include <sql/operator/detail/and.hpp>
#include <sql/operator/detail/eq.hpp>
#include <sql/operator/detail/plus.hpp>
#include <sql/operator/detail/gt.hpp>
#include <sql/operator/detail/value.hpp>
#include <sql/operator/detail/field.hpp>
#include <sql/operator/aux/value_wrapper.hpp>

/**
 * Return model's field wrapper.
 * @param f Pointer to member variable
 * @return Instance of pointer pointer to member wrapped in class.
 */ 
template <typename T, typename Cls>
field_impl<T, Cls> F(field<T> Cls::* f)
{
	return field_impl<T, Cls>(f);
}

/**
 * Return OR expression with two sub-expressions.
 * @param t1 Left side
 * @param t2 Right side
 * @return OR expression node
 */
template <typename T1, typename T2>
or_impl<typename value_wrapper<T1>::type,
        typename value_wrapper<T2>::type> or_(T1 const & t1, T2 const & t2)
{
	return or_impl<
		typename value_wrapper<T1>::type,
		typename value_wrapper<T2>::type
	>(t1, t2);
}

/**
 * Return AND expression with two sub-expressions.
 * @param t1 Left side
 * @param t2 Right side
 * @return AND expression node
 */
template <typename T1, typename T2>
and_impl<typename value_wrapper<T1>::type,
        typename value_wrapper<T2>::type> and_(T1 const & t1, T2 const & t2)
{
	return and_impl<
		typename value_wrapper<T1>::type,
		typename value_wrapper<T2>::type
	>(t1, t2);
}

/**
 * Return EQUALITY expression with two sub-expressions.
 * @param t1 Left side
 * @param t2 Right side
 * @return EQUALITY expression node
 */
template <typename T1, typename T2>
eq_impl<typename value_wrapper<T1>::type,
        typename value_wrapper<T2>::type> eq_(T1 const & t1, T2 const & t2)
{
	return eq_impl<
		typename value_wrapper<T1>::type,
		typename value_wrapper<T2>::type
	>(t1, t2);
}

/**
 * Return PLUS expression node with two sub-expressions.
 * @param t1 Left side
 * @param t2 Right side
 * @return PLUS expression node
 */
template <typename T1, typename T2>
plus_impl<typename value_wrapper<T1>::type,
        typename value_wrapper<T2>::type> plus_(T1 const & t1, T2 const & t2)
{
	return plus_impl<
		typename value_wrapper<T1>::type,
		typename value_wrapper<T2>::type
	>(t1, t2);
}

/**
 * Return GREATER expression node with two sub-expressions.
 * @param t1 Left side
 * @param t2 Right side
 * @return GREATER expression node
 */
template <typename T1, typename T2>
gt_impl<typename value_wrapper<T1>::type,
        typename value_wrapper<T2>::type> gt_(T1 const & t1, T2 const & t2)
{
	return gt_impl<
		typename value_wrapper<T1>::type,
		typename value_wrapper<T2>::type
	>(t1, t2);
}

//
// GLOBAL OPERATORS FOR EXPRESSIONS
//

// N-th template name. Concatenate any token with n. This "any" token should be
// constant (do not use __COUNTER__ here etc)
#define _TPL(n) TEMPLATE_ ## n

#define TEMPLATED_AUX_BASE(n)                                                  \
	template < n , typename _RHS>
#define TEMPLATED_AUX_1                                                        \
	typename _TPL(1)
#define TEMPLATED_AUX_2                                                        \
	typename _TPL(1), typename _TPL(2)
#define TEMPLATED_AUX_3                                                        \
	typename _TPL(1), typename _TPL(2), typename _TPL(3)

// Generate template < typename ..., typename _RHS> declaration for N templates
#define TEMPLATED(n)                                                           \
	TEMPLATED_AUX_BASE(TEMPLATED_AUX_ ## n)

#define PASS_TPL_AUX_1(token)                                                  \
	token < _TPL(1) >
#define PASS_TPL_AUX_2(token)                                                  \
	token < _TPL(1) , _TPL(2) >
#define PASS_TPL_AUX_3(token)                                                  \
	token < _TPL(1), _TPL(2), _TPL(3) >
#define PASS_TPL_(n)                                                           \
	PASS_TPL_AUX_ ## n
// Adds N templates to token.
#define PASS_TPL(n, token)                                                     \
	PASS_TPL_(n)(token)

// Auxiliary implementation of templated operator declaration
#define IMPLEMENT_OPERATOR_AUX(op, node, lhs)                                  \
	node < lhs , typename value_wrapper< _RHS >::type >                        \
	operator op ( lhs const & lhs_, _RHS const & rhs_)                         \
{                                                                              \
	return node < lhs , typename value_wrapper<_RHS>::type>(lhs_, rhs_);       \
}

/**
 * Declare global operator. Left side is a class, there is no right side
 * because this one is always "any". LHS is always "infected" with N templates.
 * This "N" is the same as how many templated parameters are in this function.
 * @param n Templated arguments count. These templates are passed to LHS.
 * @param op Operator name. IE. ==, &&, ||...
 * @param lhs Left side of operator.
 */
#define IMPLEMENT_OPERATOR(n, op, node, lhs) \
	TEMPLATED(n) \
	IMPLEMENT_OPERATOR_AUX(op, node, PASS_TPL(n, lhs))

// FIELD == RHS
IMPLEMENT_OPERATOR(2, ==, eq_impl, field_impl)
// FIELD + RHS
IMPLEMENT_OPERATOR(2, +, plus_impl, field_impl)
// (LHS == RHS) && ...
IMPLEMENT_OPERATOR(2, &&, and_impl, eq_impl)
// ((...) && (...)) && RHS
IMPLEMENT_OPERATOR(2, &&, and_impl, and_impl)
// (LHS == RHS) || ...
IMPLEMENT_OPERATOR(2, ||, or_impl, eq_impl)
// ((...) || (...)) || LHS
IMPLEMENT_OPERATOR(2, ||, or_impl, or_impl)
// LHS > RHS
IMPLEMENT_OPERATOR(2, >, gt_impl, field_impl)

#endif /* SQL_EXPRESSION_OPERATORS_ */
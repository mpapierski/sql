#if !defined(SQL_EXPRESSION_OPERATORS_)
#define SQL_EXPRESSION_OPERATORS_

#include <sql/operator/aux/nest.hpp>
#include <sql/operator/detail/or.hpp>
#include <sql/operator/detail/and.hpp>
#include <sql/operator/detail/eq.hpp>
#include <sql/operator/detail/plus.hpp>
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

#endif /* SQL_EXPRESSION_OPERATORS_ */
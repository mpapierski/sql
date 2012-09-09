#if !defined(SQL_EXPRESSION_AUX_TYPE_WRAPPER_)
#define SQL_EXPRESSION_AUX_TYPE_WRAPPER_

/**
 * Value wrapper is a class for converting expression node types.
 * For example expression type_wrapper<int>::type is equal to
 * value_impl<int>.
 * But any defined overload of this struct ie. value_wrapper<T>::type 
 * gives T.
 */
template <typename T>
struct value_wrapper
{
	typedef value_impl<T> type;
};

template <int N>
struct value_wrapper<char[N]>
{
	typedef value_impl<std::string> type;
};

template <typename T1, typename T2>
struct value_wrapper<plus_impl<T1, T2> >
{
	typedef plus_impl<T1, T2> type;
};

template <typename T1, typename T2>
struct value_wrapper<gt_impl<T1, T2> >
{
	typedef gt_impl<T1, T2> type;
};

template <typename T1, typename T2>
struct value_wrapper<eq_impl<T1, T2> >
{
	typedef eq_impl<T1, T2> type;
};

template <typename T1, typename T2>
struct value_wrapper<or_impl<T1, T2> >
{
	typedef or_impl<T1, T2> type;
};

template <typename T1, typename T2>
struct value_wrapper<and_impl<T1, T2> >
{
	typedef and_impl<T1, T2> type;
};

template <typename T, typename Cls>
struct value_wrapper<field_impl<T, Cls> >
{
	typedef field_impl<T, Cls> type;
};

#endif /* SQL_EXPRESSION_AUX_TYPE_WRAPPER_ */

#if !defined(SQL_INTERFACE_GENERIC_BINDER_)
#define SQL_INTERFACE_GENERIC_BINDER_

struct query;

template <typename T>
struct binder;

template <typename T>
struct binder: abstract_binder
{
	virtual ~binder()
	{
		
	}
	
	T value_;
	binder(T const & value)
		: value_(value)
	{
		
	}
	
	void bind(query * qry)
	{
		qry->bind<T>(value_);
	}
};

#endif /* SQL_INTERFACE_GENERIC_BINDER_ */
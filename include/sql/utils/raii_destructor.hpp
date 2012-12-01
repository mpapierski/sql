#if !defined(SQL_UTILS_RAII_DESTRUCTOR_INCLUDED_)
#define SQL_UTILS_RAII_DESTRUCTOR_INCLUDED_

/**
 * Similiar to std::auto_ptr, but it can take custom destructor.
 * Destroys pointer on scope exit unless commited.
 */
template <typename T>
struct raii_destructor
{
	/**
	 * Static deleter.
	 */
	static void deleter(T * p)
	{
		delete p;
	}

	T * ptr_;
	typedef void (*destructor_t)(T *);
	destructor_t destructor_;
	bool commit_;
	
	raii_destructor(T * ptr, destructor_t destructor = &deleter)
		: ptr_(ptr)
		, destructor_(destructor)
		, commit_(false)
	{
		
	}
	
	~raii_destructor()
	{
		if (commit_)
			return;
		(*destructor_)(ptr_);
	}
	
	inline void commit()
	{
		commit_ = true;
	}
};

#endif /* SQL_UTILS_RAII_DESTRUCTOR_INCLUDED_ */
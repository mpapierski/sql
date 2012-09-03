#if !defined(SQL_UTILS_RAII_DESTRUCTOR_INCLUDED_)
#define SQL_UTILS_RAII_DESTRUCTOR_INCLUDED_

/**
 * Similiar to std::auto_ptr, but it can take custom destructor.
 * Destroys pointer on scope exit unless commited.
 */
template <typename T>
struct raii_destructor
{
	T * & ptr_;
	typedef void (*destructor_t)(T *);
	destructor_t destructor_;
	// Destructor action
	void (raii_destructor::*action_)();
	bool commit_;
	// To make compiler happy we must separate these actions.
	
	void custom_destroy()
	{
		(*destructor_)(ptr_);
	}
	
	void standard_destroy()
	{
		delete ptr_;
	}
	
	raii_destructor(T * & ptr)
		: ptr_(ptr)
		, destructor_(0)
		, action_(&raii_destructor::standard_destroy)
		, commit_(false)
	{
		
	}
	
	raii_destructor(T * & ptr, destructor_t destructor)
		: ptr_(ptr)
		, destructor_(destructor)
		, action_(&raii_destructor::custom_destroy)
		, commit_(false)
	{
		
	}
	
	~raii_destructor()
	{
		if (commit_)
			return;
		(this->*action_)();
		ptr_ = 0;
	}
	
	inline void commit()
	{
		commit_ = true;
	}
};

#endif /* SQL_UTILS_RAII_DESTRUCTOR_INCLUDED_ */
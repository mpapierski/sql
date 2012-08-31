#if !defined(SQL_IMPL_COLLECTION_INCLUDED_)
#define SQL_IMPL_COLLECTION_INCLUDED_

template <typename ModelT>
struct collection
{
	ModelT model_inst_;
	query * qry_;
	std::string expr_;
	    
	template <typename F>
	collection(limit_expr<F> lmt)
		: model_inst_()
		, qry_(lmt.get_query())
		, expr_(lmt(model_inst_, qry_))
	{
		qry_->prepare(expr_);
		qry_->bind_all();
	}
	
	~collection()
	{
		delete qry_;
	}
	
	void execute()
	{
		  
	}
	
	template <typename T>
	struct model_wrapper
	{
		bool present_;
		T wrapper_;
		explicit model_wrapper()
			: present_(false)
		{
			
		}
		explicit model_wrapper(T const & t)
			: present_(true)
			, wrapper_(t)
		{
			
		}
		
		T const & operator*() const
		{
			return wrapper_;
		}
		operator bool()
		{
			return present_;
		}
	};
	
	typedef model_wrapper<ModelT> const_iterator;
	
	model_wrapper<ModelT> next()
	{
		qry_->run();
		assert(qry_);
		if (!qry_->has_results())
		{
			return model_wrapper<ModelT>();
		}
		ModelT obj;
		obj.load(qry_);
		return model_wrapper<ModelT>(obj);
	}
};

#endif /* SQL_IMPL_COLLECTION_INCLUDED_ */
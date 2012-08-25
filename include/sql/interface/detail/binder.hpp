#if !defined(SQL_INTERFACE_BINDER_INCLUDED_)
#define SQL_INTERFACE_BINDER_INCLUDED_

struct query;

struct abstract_binder
{
	virtual ~abstract_binder() {}
	virtual void bind(query * qry) = 0;
};

#endif /* SQL_INTERFACE_BINDER_INCLUDED_ */

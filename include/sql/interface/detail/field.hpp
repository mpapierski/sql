#if !defined(SQL_INTERFACE_FIELD_)
#define SQL_INTERFACE_FIELD_

struct query;

struct abstract_field
{
	virtual ~abstract_field() {}
	virtual std::string name() const = 0;
	virtual std::string as_string() const = 0;
	virtual bool is_null() const = 0;
	virtual void bind_to(query * qry) = 0;
	virtual void get_value(query * qry) = 0;
};

#endif /* SQL_INTERFACE_FIELD_ */

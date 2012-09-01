#if !defined(SQL_DETAIL_FIELD_)
#define SQL_DETAIL_FIELD_

#include <ostream>
#include <sstream>
#include <cassert>
#include <sql/interface/detail/field.hpp>
#include <sql/interface/detail/query.hpp>
#include <sql/interface/detail/null.hpp>

template <typename T>
struct field: abstract_field
{
	virtual ~field() {}
	std::string name_;
	bool null_;
	T value_;
	int position_;
	
	template <typename F>
	field(F* parent, std::string const & name)
		: name_(name)
		, null_(true)
	{
		position_ = parent->add_column(this, name);
	}
	
	std::string name() const { return name_; }
	
	field & operator=(T const & new_value)
	{
		null_ = false;
		value_ = new_value;
		return *this;
	}
	
	inline T const & value() const
	{
		assert(!null_);
		return value_;
	}
	
	std::string as_string() const
	{
		if (null_) return "NULL";
		std::stringstream ss;
		ss << value_;
		return ss.str();
	}
	
	bool is_null() const
	{
		return null_;
	}
	
	void bind_to(query * qry)
	{
		if (null_)
			qry->add_bind(new binder<null_impl>(null_impl()));
		else	
			qry->add_bind(new binder<T>(value_));
	}
	
	void get_value(query * qry)
	{
		if (qry->is_null(position_))
		{
			T t;
			using std::swap;
			swap(value_, t);
			null_ = true;
			return;
		}
		null_ = false;
		value_ = qry->get<T>(position_);
	}
	
	friend std::ostream & operator<<(std::ostream & lhs, field const & f)
	{
		lhs << f.as_string();
		return lhs;
	}
	
	bool operator==(T const & data) const
	{
		return value_ == data;
	}
};


#endif /* SQL_DETAIL_FIELD_ */

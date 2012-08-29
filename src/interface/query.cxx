#include <cstring>
#include <sql/interface/interface.hpp>

void query::bind_all()
{
	for (std::list<abstract_binder*>::iterator it(binders_.begin()),
		end(binders_.end()); it != end; ++it)
	{
		abstract_binder* late_binder = *it;
		late_binder->bind(this);
		delete late_binder;
	}
}

void query::add_bind(abstract_binder* nb)
{
    binders_.push_back(nb);
}

template <>
int query::get(int index)
{
	int value;
	this->get_int(index, value);
	return value;
}

template <>
std::string query::get(int index)
{
	std::string value;
	this->get_string(index, value);
	return value;
}

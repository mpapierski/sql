#if !defined(SQL_INTERFACE_QUERY_INCLUDED_)
#define SQL_INTERFACE_QUERY_INCLUDED_

#include <list>
#include <string>

struct abstract_binder;

/**
 * Querying interface.
 * Each SQL dialect must implement its own query class.
 */
struct query
{
	/**
	 * Late binders.
	 */
	std::list<abstract_binder*> binders_;
	virtual ~query() { }
	virtual void bind_int(int value) = 0;
	virtual void bind_text(const char * data, int length) = 0;
	virtual void bind_null() = 0;
	
	virtual void execute(std::string const &) = 0;
	virtual void prepare(std::string const &) = 0;
	
	/**
	 * Evaluate all late binders.
	 */
	void bind_all();
	
	void add_bind(abstract_binder* nb);
	virtual std::string next_placeholder() = 0;
	
	virtual void run() = 0;
	virtual bool has_results() = 0;
	
	virtual bool is_null(int index) = 0;
	virtual void get_int(int index, int & result) = 0;
	virtual void  get_string(int index, std::string & result) = 0;
	
	template <typename T>
	T get(int index);
	
	template <typename T>
	void bind(T);
};

#endif /* SQL_INTERFACE_QUERY_INCLUDED_ */
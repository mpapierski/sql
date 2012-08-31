#define BOOST_TEST_MODULE sqlite

#include <string>
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/execution_monitor.hpp>
#include <sql/sql.hpp>

using namespace std;
using namespace boost;

class person: public table
{
public:
	field<int> id;
	field<string> first_name;
	field<string> last_name;
	
	person()
		: table("person")
		, id(this, "id")
		, first_name(this, "first_name")
		, last_name(this, "last_name") {}
};

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_connection)
{
	database db("sqlite:///:memory:");
	session s = db.session();
	s.create_table<person>();
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_insert_not_existing_table)
{
	// check if adding new model instance (insert into) throws
	// when table does not exists.
	database db("sqlite:///:memory:");
	session s = db.session();
	
	person p;
	p.first_name = "John";
	p.last_name = "Smith";
	
	// XXX: Throw SQL exceptions instead of std::runtime_error.
	BOOST_REQUIRE_THROW(s.add(p), std::runtime_error);
	//
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_insert_existing_table)
{
	// check if adding new model instance (insert into) nothrows
	// when table exists.
	database db("sqlite:///:memory:");
	session s = db.session();
	// create table
	s.create_table<person>();
	
	// new person
	person p;
	p.first_name = "John";
	p.last_name = "Smith";
	
	// XXX: Throw SQL exceptions instead of std::runtime_error.
	BOOST_REQUIRE_NO_THROW(s.add(p));
	//
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_collection)
{
	// check if adding new model instance (insert into) nothrows
	// when table exists.
	database db("sqlite:///:memory:");
	session s = db.session();
	// create table
	s.create_table<person>();
	
	// new person
	person p;
	p.id = 1234;
	p.first_name = "John";
	p.last_name = "Smith";
	
	// XXX: Throw SQL exceptions instead of std::runtime_error.
	BOOST_REQUIRE_NO_THROW(s.add(p));
	//
	collection<person> cc = s.query<person>().
		filter(eq_(F(&person::id), 1234)).
		limit(1);
	collection<person>::const_iterator p2 = cc.next();
	BOOST_CHECK(!!p2);
	BOOST_REQUIRE_NO_THROW(*p2);
	person const & person_ = *p2;
	BOOST_CHECK(person_.id == 1234);
	BOOST_CHECK(person_.first_name == std::string("John"));
	BOOST_CHECK(person_.last_name == std::string("Smith"));
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_empty_collection)
{
	database db("sqlite:///:memory:");
	session s = db.session();
	// create table
	s.create_table<person>();
	//
	collection<person> cc = s.query<person>().
		filter(eq_(F(&person::id), 1234)).
		limit(1);
	collection<person>::const_iterator p2 = cc.next();
	BOOST_CHECK(!p2);
}
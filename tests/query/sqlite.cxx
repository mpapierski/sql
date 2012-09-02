#define BOOST_TEST_MODULE sqlite

#include <string>
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
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
		filter(F(&person::id) == 1234).
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
		filter(F(&person::id) == 1234).
		limit(1);
	collection<person>::const_iterator p2 = cc.next();
	BOOST_CHECK(!p2);
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_empty_collection_no_table)
{
	database db("sqlite:///:memory:");
	session s = db.session();
	// XXX: Throw SQL error instead of std::runtime_error.
	BOOST_REQUIRE_THROW(collection<person> cc = s.query<person>(). \
		filter(F(&person::id) == 1234). \
		limit(1), std::runtime_error);
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_inserts)
{
	database db("sqlite:///:memory:");
	session s = db.session();
	s.create_table<person>();
	for (unsigned int i = 1; i <= 100; i++)
	{
		person p;
		p.id = i;
		p.first_name = "First name";
		p.last_name = "Last name";
		s.add(p);
	}
	// XXX: Throw SQL error instead of std::runtime_error.
	collection<person> cc = s.query<person>().all();
	unsigned int n = 0;
	while (collection<person>::const_iterator result = cc.next())
	{
		person const & p = *result;
		BOOST_CHECK_EQUAL(p.id, ++n);
		BOOST_CHECK_EQUAL(p.first_name, "First name");
		BOOST_CHECK_EQUAL(p.last_name, "Last name");
	}
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE(test_count)
{
	database db("sqlite:///:memory:");
	session s = db.session();
	s.create_table<person>();
	
	BOOST_CHECK_EQUAL(s.query<person>().count(), 0);
	
	person p;
	p.id = 1000;
	p.first_name = "First name";
	p.last_name = "Last name";
	s.add(p);
	BOOST_CHECK_EQUAL(s.query<person>().count(), 1);
	
	for (int i = 0; i < 1000; i++)
	{
		s.add(p);
	}
	
	BOOST_CHECK_EQUAL(s.query<person>().count(), 1001);
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE(test_filter_count)
{
	database db("sqlite:///:memory:");
	session s = db.session();
	s.create_table<person>();
	
	BOOST_CHECK_EQUAL(s.query<person>().count(), 0);
	
	{
		person p;
		p.id = 1000;
		p.first_name = "First name";
		p.last_name = "Last name";
		s.add(p);
	}

	BOOST_CHECK_EQUAL(s.query<person>().count(), 1);
	
	{
		person p;
		p.id = 1001;
		p.first_name = "First name";
		p.last_name = "Last name";
		s.add(p);
	}
	
	BOOST_CHECK_EQUAL(s.query<person>().count(), 2);
	
	BOOST_CHECK_EQUAL(s.query<person>().filter(F(&person::id) == 1001).count(), 1);
	BOOST_CHECK_EQUAL(s.query<person>().filter(F(&person::id) == 1000).count(), 1);
	BOOST_CHECK_EQUAL(s.query<person>().filter(F(&person::id) == 0).count(), 0);
	BOOST_CHECK_EQUAL(s.query<person>().count(), 2);
}
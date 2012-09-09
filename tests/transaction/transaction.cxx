#define BOOST_TEST_MODULE sqlite

#include <string>
#include <stdexcept>
#include <cstdlib>
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

static std::string DB = std::getenv("DB") ? std::getenv("DB") : std::string();

struct connection_fixture
{
	database db;
	session s;
	connection_fixture()
		: db(DB)
		, s(db.session())
	{
	}
};

struct session_fixture: connection_fixture
{
	session_fixture()
	{
		s.create_table<person>();
	}
	
	~session_fixture()
	{
		s.drop_table<person>();
	}
};

BOOST_FIXTURE_TEST_SUITE(transactional_test_suite, session_fixture)

BOOST_AUTO_TEST_CASE(test_raii_transaction)
{
	BOOST_CHECK_EQUAL(s.query<person>().count(), 0);
	person p;
	p.id = 123;
	p.first_name = "First name";
	p.last_name = "Last name";
	s.add(p);
	
	try
	{
		person p;
		p.id = 1234;
		p.first_name = "XXX";
		p.last_name = "YYY";
		s.add(p);
		throw std::exception();
	} catch (std::exception)
	{
		// Even there was exception thrown in the scope
		// there was an INSERT, and we end up with inconsistent 
		// state.
	}

	BOOST_CHECK_EQUAL(s.query<person>().count(), 2);
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE(test_transaction_rollback_traditional)
{
	BOOST_CHECK_EQUAL(s.query<person>().count(), 0);
	person p;
	p.id = 123;
	p.first_name = "First name";
	p.last_name = "Last name";
	s.add(p);	
	try
	{
		s.begin();
		person p;
		p.id = 1234;
		p.first_name = "XXX";
		p.last_name = "YYY";
		s.add(p);
		//
		throw std::exception();
		//
		s.commit();
	} catch (std::exception)
	{
		s.rollback();
	}
	BOOST_CHECK_EQUAL(s.query<person>().count(), 1);
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE(test_raii_transaction_rollback)
{
	BOOST_CHECK_EQUAL(s.query<person>().count(), 0);
	person p;
	p.id = 123;
	p.first_name = "First name";
	p.last_name = "Last name";
	s.add(p);
	
	try
	{
		transaction tr(&s);
		person p;
		p.id = 1234;
		p.first_name = "XXX";
		p.last_name = "YYY";
		s.add(p);
		throw std::exception();
	} catch (std::exception)
	{

	}
	BOOST_CHECK_EQUAL(s.query<person>().count(), 1);
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE(test_raii_transaction_commit)
{
	BOOST_CHECK_EQUAL(s.query<person>().count(), 0);
	person p;
	p.id = 123;
	p.first_name = "First name";
	p.last_name = "Last name";
	s.add(p);
	
	try
	{
		transaction tr(&s);
		person p;
		p.id = 1234;
		p.first_name = "XXX";
		p.last_name = "YYY";
		s.add(p);
		tr.commit(); // !
		throw std::exception();
	} catch (std::exception)
	{

	}
	BOOST_CHECK_EQUAL(s.query<person>().count(), 2);
}

BOOST_AUTO_TEST_SUITE_END()

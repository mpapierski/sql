#define BOOST_TEST_MODULE sqlite

#include <string>
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


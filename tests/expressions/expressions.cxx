#define BOOST_TEST_MODULE expressions

#include <boost/test/included/unit_test.hpp>
#include <sql/sql.hpp>

using namespace boost;

class test: public table
{
public:
	field<int> id;
	test()
		: table("test")
		, id(this, "id") {}
};

struct mock_query: query
{
	int next_;
	std::string prepared_;
	int bound_;
	
	mock_query(): next_(0), bound_(0)
	{
		
	}
	bool has_results() { return false; }
	void get_int(int, int & out) {}
	void get_string(int, std::string &) {}
	bool is_null(int) { return false; }
	void bind_int(int) { bound_++; }
	void execute(std::string const &) {}
	void prepare(std::string const & qry)
	{
		prepared_ = qry;
	}
	void run() {}
	void bind_null() { bound_++; }
	void bind_text(const char*, int) { bound_++; }
	std::string next_placeholder()
	{
		std::stringstream ss;
		ss << "?" << ++next_;
		return ss.str();
	}
};

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_model_data)
{
	test t;
	BOOST_CHECK(t.fields.size() == 1);
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_query_builder1)
{
	test obj;
	mock_query * qry = new mock_query;
	std::string const & e1 = and_(
		eq_(
			F(&test::id),
			69
		),
		eq_(
			F(&test::id),
			42
		)
	)(obj, qry);
	
	// prepare query
	qry->prepare(e1);
	// bind all late binders
	qry->bind_all();
	
	BOOST_CHECK_EQUAL(qry->prepared_, "(\"id\" = ?1) AND (\"id\" = ?2)");
	BOOST_CHECK_EQUAL(qry->bound_, 2);
	
	delete qry;
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_query_builder1_operators)
{
	test obj;
	mock_query * qry = new mock_query;
	std::string const & e1 = (F(&test::id) == 69 && F(&test::id) == 42)(obj, qry);
	
	// prepare query
	qry->prepare(e1);
	// bind all late binders
	qry->bind_all();
	
	BOOST_CHECK_EQUAL(qry->prepared_, "(\"id\" = ?1) AND (\"id\" = ?2)");
	BOOST_CHECK_EQUAL(qry->bound_, 2);
	
	delete qry;
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_query_builder2)
{
	test obj;
	mock_query * qry = new mock_query;
	std::string const & e1 = and_(
		eq_(
			F(&test::id),
			69
		),
		eq_(
			F(&test::id),
			plus_(
				F(&test::id),
				69
			)
		)
	)(obj, qry);
	
	// prepare query
	qry->prepare(e1);
	// bind all late binders
	qry->bind_all();
	
	BOOST_CHECK_EQUAL(qry->prepared_, "(\"id\" = ?1) AND (\"id\" = \"id\" + ?2)");
	BOOST_CHECK_EQUAL(qry->bound_, 2);
	
	delete qry;
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_query_builder2_operators)
{
	test obj;
	mock_query * qry = new mock_query;
	std::string const & e1 = ((F(&test::id) == 69) && (F(&test::id) == (F(&test::id) + 69)))(obj, qry);
	
	// prepare query
	qry->prepare(e1);
	// bind all late binders
	qry->bind_all();
	
	BOOST_CHECK_EQUAL(qry->prepared_, "(\"id\" = ?1) AND (\"id\" = \"id\" + ?2)");
	BOOST_CHECK_EQUAL(qry->bound_, 2);
	
	delete qry;
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_query_builder3)
{
	test obj;
	mock_query * qry = new mock_query;
	std::string const & e1 = and_(
		and_(
			eq_(
				F(&test::id),
				69
			),
			eq_(
				F(&test::id),
				42
			)
		),
		and_(
			eq_(
				F(&test::id),
				69
			),
			eq_(
				F(&test::id),
				42
			)
		)
	)(obj, qry);
	
	// prepare query
	qry->prepare(e1);
	// bind all late binders
	qry->bind_all();
	
	BOOST_CHECK_EQUAL(qry->prepared_, "(\"id\" = ?1) AND (\"id\" = ?2) AND (\"id\" = ?3) AND (\"id\" = ?4)");
	BOOST_CHECK_EQUAL(qry->bound_, 4);
	
	delete qry;
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_query_builder3_operators)
{
	test obj;
	mock_query * qry = new mock_query;
	std::string const & e1 = ((F(&test::id) == 69) && (F(&test::id) == 42) && (F(&test::id) == 69) && (F(&test::id) == 42))(obj, qry);
	// prepare query
	qry->prepare(e1);
	// bind all late binders
	qry->bind_all();
	
	BOOST_CHECK_EQUAL(qry->prepared_, "(\"id\" = ?1) AND (\"id\" = ?2) AND (\"id\" = ?3) AND (\"id\" = ?4)");
	BOOST_CHECK_EQUAL(qry->bound_, 4);
	
	delete qry;
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_query_builder4)
{
	test obj;
	mock_query * qry = new mock_query;
	std::string const & e1 = and_(
		and_(
			eq_(
				F(&test::id),
				69
			),
			eq_(
				F(&test::id),
				42
			)
		),
		or_(
			eq_(
				F(&test::id),
				69
			),
			eq_(
				F(&test::id),
				42
			)
		)
	)(obj, qry);
	
	// prepare query
	qry->prepare(e1);
	// bind all late binders
	qry->bind_all();
	
	BOOST_CHECK_EQUAL(qry->prepared_, "(\"id\" = ?1) AND (\"id\" = ?2) AND ((\"id\" = ?3) OR (\"id\" = ?4))");
	BOOST_CHECK_EQUAL(qry->bound_, 4);
	
	delete qry;
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_query_builder4_operators)
{
	test obj;
	mock_query * qry = new mock_query;
	std::string const & e1 = ((F(&test::id) == 69) && (F(&test::id) == 42) && ((F(&test::id) == 69) || (F(&test::id) == 42)))(obj, qry);	
	// prepare query
	qry->prepare(e1);
	// bind all late binders
	qry->bind_all();
	
	BOOST_CHECK_EQUAL(qry->prepared_, "(\"id\" = ?1) AND (\"id\" = ?2) AND ((\"id\" = ?3) OR (\"id\" = ?4))");
	BOOST_CHECK_EQUAL(qry->bound_, 4);
	
	delete qry;
}

BOOST_AUTO_TEST_CASE (test_query_builder5)
{
	test obj;
	mock_query * qry = new mock_query;
	std::string const & e1 = or_(
		or_(
			eq_(
				F(&test::id),
				69
			),
			eq_(
				F(&test::id),
				42
			)
		),
		or_(
			eq_(
				F(&test::id),
				69
			),
			eq_(
				F(&test::id),
				42
			)
		)
	)(obj, qry);
	
	// prepare query
	qry->prepare(e1);
	// bind all late binders
	qry->bind_all();
	
	BOOST_CHECK_EQUAL(qry->prepared_, "(\"id\" = ?1) OR (\"id\" = ?2) OR (\"id\" = ?3) OR (\"id\" = ?4)");
	BOOST_CHECK_EQUAL(qry->bound_, 4);
	
	delete qry;
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_query_builder5_operators)
{
	test obj;
	mock_query * qry = new mock_query;
	std::string const & e1 = ((F(&test::id) == 69) || (F(&test::id) == 42) || ((F(&test::id) == 69) || (F(&test::id) == 42)))(obj, qry);	
	// prepare query
	qry->prepare(e1);
	// bind all late binders
	qry->bind_all();
	
	BOOST_CHECK_EQUAL(qry->prepared_, "(\"id\" = ?1) OR (\"id\" = ?2) OR (\"id\" = ?3) OR (\"id\" = ?4)");
	BOOST_CHECK_EQUAL(qry->bound_, 4);
	
	delete qry;
}

//____________________________________________________________________________//

BOOST_AUTO_TEST_CASE (test_expression_tree)
{
	// compiles or not ?
	
	// id
	F(&test::id);
	// id = 42
	eq_(F(&test::id), 42);
	// id = 69 or id = 42
	or_(
		eq_(
			F(&test::id),
			69
		),
		eq_(
			F(&test::id),
			42
		)
	);
	// id = 69 and id = 42
	and_(
		eq_(
			F(&test::id),
			69
		),
		eq_(
			F(&test::id),
			42
		)
	);
}

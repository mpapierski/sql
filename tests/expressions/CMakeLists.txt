CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (expressions)

ADD_EXECUTABLE (expressions
	expressions.cxx)
TARGET_LINK_LIBRARIES (expressions sql)
ADD_TEST (expressions
	expressions)

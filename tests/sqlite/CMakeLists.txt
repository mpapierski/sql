CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (sqlite)

ADD_EXECUTABLE (sqlite
	sqlite.cxx)
TARGET_LINK_LIBRARIES (sqlite sql)
ADD_TEST (sqlite
	sqlite)

CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (sql)

ADD_LIBRARY (sql
	interface/query.cxx
	interface/table.cxx)

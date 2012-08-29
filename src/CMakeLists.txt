CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (sql)

FIND_PACKAGE (Sqlite3 REQUIRED)

SET (SOURCES
	interface/query.cxx
	interface/table.cxx
	utils/url.cxx
	impl/database.cxx
	impl/session.cxx
	dialect/sqlite/dialect.cxx
	dialect/sqlite/query.cxx
)

ADD_LIBRARY (sql
	${SOURCES}
)

INCLUDE_DIRECTORIES (${SQLITE3_INCLUDE_DIR})
TARGET_LINK_LIBRARIES (sql
	${SQLITE3_LIBRARIES}
)

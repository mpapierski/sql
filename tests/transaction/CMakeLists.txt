CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (transaction)

ADD_EXECUTABLE (transaction
	transaction.cxx)
TARGET_LINK_LIBRARIES (transaction sql)
ADD_TEST (transaction
	transaction)

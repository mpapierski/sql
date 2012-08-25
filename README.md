# sql

Object-relational mapper and the database toolkit for C++.

## Introduction

This library primary goal is to provide high level database abstraction layer over many
different SQL dialects. Goals:

* Convention over configuration.
* Easy to understand Object-relational mapper features.
* Compile-time Embedded Domain Specific Language for SQL query generation.
* No dependencies (not even Boost library is needed to build main lib!)
* Usage of exceptions
* Support for SQLite, PostgreSQL, MySQL, Oracle.
* High test coverage.

## Requirements

* C++03 compatible compiler.
* CMake (2.6+)
* Boost.Test (for building tests)

## Building

* cd sql
* mkdir build
* cd build
* cmake ..
* make && make test

## License

GPLv3.

## TODO

* Figure out how to optimize EDSL to generate less assembly.
* Support for constraints.
* Fix possible memory leaks.
* Implement collections, select statements (limit, filter...)
* Documentation

## Help

How to start ?

### Define your model

Let's start with simple example:

Define your schema.

	struct person: table
	{
		field<int> id;
		field<string> first_name;
		field<string> last_name;
		person()
			: table("person")
			, id(this, "id")
			, first_name(this, "first_name")
			, last_name(this, "last_name") {}
	};

### Connect it to the database

Connect to the database and create table.

	database db("sqlite:///:memory:");
	db.create_table<person>();

### Feed it with data

Create new person and store it in the database.

	session s = db.session();
	person obj;
	obj.id = 123;
	obj.first_name = "John";
	obj.last_name = "Smith";
	s.add(obj);
	
And thats all.

### Querying

* Return no more than 10 John Smiths

	collection<person> results =
		session.query<person>().
		filter(
			(F(&person::first_name) == "John") &&
			(F(&person::last_name) == "Smith")
		).
		limit(10)
		
### More

Documentation is under construction. See tests, and examples.

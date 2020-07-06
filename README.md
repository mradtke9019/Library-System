# Library-System
Library Checkout system

## Goals
This project is a C++ implementation of a library system that seeks to touch many areas of computer science and programming.
The goal is to create an interface between a sqlite database and C++. One part of the project creates C++ class files that map
directly to table schemas.

For example:
  Suppose we have the Table Books with columns: ISBN, Title, Summary. The tool created would seek to read the schema
  from the database and create a corresponding C++ class called Books with properties such as int ISBN, std::string Title,etc.
  The goal of the Object relational mapper is to create all the C++ classes automatically by reading from the database.
  
Once the Object Relational Mapper is completed, the goal is to use these freshly created classes to interact with the sqlite database,
whether it be adding records to any of the tables, selecting info, or removing records.

When all the CRUD methods have been implemented dynamically and effectively, a user interface to place on top of the code will be
next. The goal of this is to get exposed to the graphics pipeline and understand OpenGL/Vulkan in a beginner scenario.

This ORM tool does not yet allow users to create tables and schemas from a sqlite database, so queries must be executed onto the table
beforehand to create whatever schemas are desired to a *.db* file. Indexes are also not yet possible with the current work done.

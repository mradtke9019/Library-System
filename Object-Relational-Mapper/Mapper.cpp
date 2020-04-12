
#include <iostream>
#include <string>
#include "sqlite3.h"

/*
Goals
Open Database
Scan Tables
Read types and names of columns
For each table, create a class file
For each column in table, create a field.
Add custom inheritcance for every table class created
Create and write file

*/
static int callback(void* data, int argc, char** argv, char** azColName)
{
	int i;
	//fprintf(stderr, "%s: ", (const char*)data);

	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}

int main()
{

	sqlite3* db;
	char* errMsg;
	std::string dbName = "Library.db";
	int rc = sqlite3_open(dbName.c_str(), &db);
	if (rc) {
		std::cout << "Cant open database" << sqlite3_errmsg(db) << "\n";
	}
	else {
		std::cout << "Opended database succesfully\n";
	}

	std::string tableStmt = "SELECT name FROM sqlite_master WHERE type='table'";
	rc = sqlite3_exec(db, tableStmt.c_str(), (sqlite3_callback)callback, 0, &errMsg);
	if (rc) {
		std::cout << "Failed\n";
	}
	else std::cout << "Success\n";
}
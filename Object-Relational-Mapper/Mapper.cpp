
#include <iostream>
#include <string>
#include "sqlite3.h"
#include <vector>
#include <fstream>

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

class Model {
public: 
	Model() {

	};
	std::string table;
	std::vector<std::string> columns;
	std::string toString() {
		std::string temp = "";
		temp += "#pragma once\n";
		temp += "#include \"Model.h\"\n"; 
		temp += "class " + table + " : " + " public Model {\n";
		temp += "private:\n";

		temp += "public:\n";
		temp += "\t" + table + "(" + ")\n"; 
		temp += "\t{\n";
		temp += "\t\n";
		temp += "\t};\n";
		for (auto x : columns) 
			temp += "\tstd::string " + x + ";\n" ;

		temp += "};";
		return temp;
	};
};

std::vector<Model> models;

bool create(Model model) {
	std::ofstream myfile;
	myfile.open(model.table + ".h");
	if (myfile.is_open()) {
		std::cout << "File is open\n";

		myfile << model.toString();

		myfile.close();
	}
	else {

		return false;
	}

	return true;
}


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

void dbstuff() {
	sqlite3* db;
	char* errMsg;
	std::string dbName = "Library.db";
	int rc = sqlite3_open(dbName.c_str(), &db);
	if (rc) {
		std::cout << "Cant open database" << sqlite3_errmsg(db) << "\n";
	}
	else {
		std::cout << "Opened database succesfully\n";
	}

	std::string tableStmt = "SELECT name FROM sqlite_master WHERE type='table'";
	rc = sqlite3_exec(db, tableStmt.c_str(), (sqlite3_callback)callback, 0, &errMsg);
	if (rc) {
		std::cout << "Failed\n";
	}
	else std::cout << "Success\n";
}

int main()
{
	dbstuff();

	for (auto m: models) 
		create(m);
}

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
class column {
public: 
	column(std::string t, std::string n) {
		type = t; name = n;
	}
	std::string type;
	std::string name;
};

class Model {
public: 
	Model() {

	};
	Model(std::string t, std::vector<column> c) {
		table = t;
		columns = c;
	};
	std::string table;
	std::vector<column> columns;
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
		for (auto x : columns) {
			if (x.type.find("Integer") == 0 || x.type.find("int") == 0) {
				temp += "\tint " + x.name + ";\n";
			}
			else if (x.type.find("DateTime") == 0) {
				temp += "\ttime_t " + x.name + ";\n";
			}
			else {
				temp += "\tstd::string " + x.name + ";\n";
			}
		}

		temp += "};";
		return temp;
	};
};

std::vector<Model*> models;
std::vector<column>* columns =		new std::vector<column>();
std::vector<std::string>* tableNames =	new std::vector<std::string>();

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


static int tableCallback(void* data, int argc, char** argv, char** azColName)
{
	tableNames->push_back(argv[0]);
	return 0;
}

static int columnCallback(void* data, int argc, char** argv, char** azColName)
{
	columns->push_back(column(argv[2],argv[1]));
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

	rc = sqlite3_exec(db, "SELECT name FROM sqlite_master WHERE type='table'", (sqlite3_callback)tableCallback, 0, &errMsg);

	for (auto table : *tableNames)
	{
		std::cout << "Getting columns for " << table << "\n";
		rc = sqlite3_exec(db, std::string("Pragma table_info(" + table +")").c_str(), (sqlite3_callback)columnCallback, 0, &errMsg);

		models.push_back(new Model(table, *columns));
		columns->clear();
	}

	if (rc) {
		std::cout << "Failed\n";
	}
	else std::cout << "Success\n";
}

int main()
{
	dbstuff();

	for (auto m: models) 
		create(*m);
}
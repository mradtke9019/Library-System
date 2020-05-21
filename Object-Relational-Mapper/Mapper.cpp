
#include <iostream>
#include <string>
#include "sqlite3.h"
#include <vector>
#include <fstream>
#include <Windows.h>

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
		type = t; name = n; cType = t;
	}

	std::string type;
	std::string cType;
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
		temp += "#include <vector>\n";
		temp += "#include <string>\n\n";
		temp += "class " + table + " : " + " public Model {\n";
		temp += "private:\n";

		temp += "public:\n";
		temp += "\t" + table + "(" + ")\n"; 
		temp += "\t{\n";
		temp += "\t\n";
		temp += "\t};\n";

		temp += "\tstd::string Table() { return \"" + table + "\"; }\n";
		int i = 0;
		// Create fields that map to columns for class
		for (auto x : columns) {
			if (x.type.find("Integer") == 0 || x.type.find("int") == 0) {
				temp += "\tint " + x.name + ";\n";
				columns.at(i).cType = "int";
			}
			else if (x.type.find("DateTime") == 0) {
				temp += "\ttime_t " + x.name + ";\n";
				columns.at(i).cType = "time_t";
			}
			else {
				temp += "\tstd::string " + x.name + ";\n";
				columns.at(i).cType = "std::string";
			}
			i++;
		}

		// Create function to get names of all columns for this db model object
		temp += "\tstd::vector<std::string> Columns()\n";
		temp += "\t{\n";
		temp += "\t\treturn std::vector<std::string>({";
		for (auto x : columns) {
			temp += "\"" + x.name + "\"";
			if(x.name.compare(columns[columns.size()- 1].name))
				temp += ",";
		}
		temp += "});\n\t}\n";

		//Create function to get the values of current db model object
		temp += "\tstd::vector<std::string> Values()\n";
		temp += "\t{\n";
		temp += "\t\treturn std::vector<std::string>({";
		for (auto x : columns) {
			if (x.type.find("Integer") == 0 || x.type.find("int") == 0 || x.type.find("DateTime") == 0)
				temp += "std::to_string(" + x.name + ")";
			else
				temp += "\"'\" + " + x.name + " + \"'\"";

			if (x.name.compare(columns[columns.size() - 1].name))
				temp += ",";
		}
		temp += "});\n\t}\n";

		// Create callback function for select statements
		i = 0;
		std::string item = "my" + table;
		temp += "\tstatic int selectCallback(void* data, int argc, char** argv, char** azColName)\n";
		temp += "\t{\n";
		temp += "\t\tstd::vector<" + table + "*>* " + table + "List = static_cast<std::vector<" + table +"*>*>(data);\n";
		temp += "\t\t" + table + "* " + item + "= new " + table + "();\n";
		for (auto x : columns)
		{
			std::string conversion;
			if (x.cType.find("int") == 0)
				conversion = "atoi";
			else if (x.cType.find("std::string") == 0)
				conversion = "std::string";

			temp += "\t\t" + item + "->" + x.name + " = (" + conversion + ")(argv[" + std::to_string(i) + "]);\n";
			i++;
		}

		temp += "\n\t\t" + table +"List->push_back(" + item + ");\n";
		temp += "\t\treturn 0;\n";
		temp += "\t}\n";

		temp += "\tstd::string updateStatement()\n";
		temp += "\t{\n";

		temp += "\t\treturn \"Update " + table + " Set ";
		for (auto x : columns) {
			if(x.cType.find("std::string") == 0)
				temp += x.name + " = '\" + " + x.name + " + \"'";
			else if (x.cType.find("int") == 0)
				temp += x.name + " = \" + std::to_string(" + x.name + ") + \"";
			if (x.name.compare(columns[columns.size() - 1].name))
				temp += ",";
		}
		if(columns.at(0).cType.find("std::string") == 0)
			temp += " Where " + columns.at(0).name + " = '\" + " + columns.at(0).name + " + \"'\";\n";
		else if (columns.at(0).cType.find("int") == 0)
			temp += " Where " + columns.at(0).name + " = \" + std::to_string(" + columns.at(0).name + ");\n";

		temp += "\t}\n";

		temp += "};";
		return temp;
	};
};

std::vector<Model*> models;
std::vector<column>* columns =		new std::vector<column>();
std::vector<std::string>* tableNames =	new std::vector<std::string>();

bool create(Model model, std::string path) {
	std::ofstream myfile;
	std::string fileName = path + model.table + ".h";
	myfile.open(fileName);
	if (myfile.is_open()) {
		std::cout << "Opened file " << fileName << ":";

		myfile << model.toString();

		myfile.close();
		std::cout << "\tCreated file " << fileName << "\n";
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
	std::string path = "../Library-System/";
	if (CreateDirectory(path.c_str(), NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError())
	{

		for (auto m : models)
			create(*m, path);
	}
	else
	{
		std::cout << "Unable to get to " << path;
	}
}
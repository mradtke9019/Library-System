#include "sqlite3.h"
#include "Model.h"
#include <iostream>
#include <vector>
#include "SqlException.h"


class Sqlite  {
private:
	sqlite3* db;
	char* errMsg;

	std::string InsertStatement(std::string table, std::string columns, std::string values)
	{
		return  "Insert Into " + table + columns + "\nValues " + values + ";";
	}

	std::string InsertStatement(std::string table, std::vector<std::string> columns, std::vector<std::string> values)
	{
		std::string col = "(", vals = "(";
		std::vector<std::string>::iterator c = columns.begin(), v = values.begin();

		col += *c; vals += *v;

		for (; c != columns.end(); ++c) { col += "," + *c; }
		for (; v != values.end(); ++v) { vals += "," + *v; }

		col += ")"; vals += ")";

		return  "Insert Into " + table + " " + col + "\nValues " + vals + ";";
	}

	std::string DeleteStatement(std::string table, std::string condition)
	{
		return  "Delete From " + table + (!condition.empty() ? " where " + condition : "");
	}
	
	std::string SelectStatement(std::string table, std::string condition)
	{
		return "Select * From " + table + (!condition.empty() ? " where "  + condition : "");
	}

	std::string UpdateStatement(std::string table, std::vector<std::string> columns, std::vector<std::string> values, std::string pk,std::string p)
	{
		std::string vals = "(";
		std::vector<std::string>::iterator c = columns.begin(), v = values.begin();

		vals += *v;

		for (; c != columns.end(); ++c) 
		{
			vals += "," + *v;
			++v;
		}

		//col += ")"; vals += ")";

		return "Update " + table + " Set " + " Where " + pk + "=";
	}


public:
	Sqlite(std::string dbName) 
	{
		this->errMsg = 0;
		int rc;

		rc = sqlite3_open(dbName.c_str(), &db);
		if (rc) {
			std::cout << "Cant open database" << sqlite3_errmsg(db);
		}
		else {
			std::cout << "Opened database succesfully\n";
		}
	}

	~Sqlite() { sqlite3_close(db); }

	char* getErrorMessage() { return errMsg; };

	// Add the item to the database
	int Add(Model* item, void* callback = NULL)
	{
		return sqlite3_exec(db, InsertStatement(item->Table(), item->Columns(), item->Values()).c_str(), (sqlite3_callback)callback, 0, &errMsg);
	}

	//TODO: Update so that it accepts
	int Remove(Model* item, void* callback = NULL)
	{
		return sqlite3_exec(db, DeleteStatement(item->Table(), item->Columns().at(0)).c_str(), (sqlite3_callback)callback, 0, &errMsg);
	}

	// Attempt to select data and place it in our store
	template <typename T>
	std::vector<T*>* Select(std::string table, std::string condition, void* callback) 
	{
		std::vector <T*>* data = new std::vector <T*>();
		int rc = sqlite3_exec(db, SelectStatement(table, condition).c_str(), (sqlite3_callback)callback, data, &errMsg);
		if (rc) 
			throw SqlException(std::string(errMsg));
		return data;
	}

	int Update(Model* item, void* callback = NULL)
	{
		return sqlite3_exec(db, item->updateStatement().c_str(), (sqlite3_callback)callback, 0, &errMsg);
	}


	int Execute(std::string sql, void* callback) 
	{
		return sqlite3_exec(db, sql.c_str(), (sqlite3_callback)callback, 0, &errMsg);
	}
};
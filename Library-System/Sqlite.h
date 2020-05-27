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

	// TODO: Implement some way to pass in primary key with its value for deletion. Gonna be complicated for multi attribute primary keys
	std::string DeleteStatement(std::string table, std::vector<std::string> columns, std::vector<std::string> values, std::vector<std::string> pks)
	{
		std::string pkCondition = "";


		for (int i = 0; i < pks.size(); i++)
		{
			for (int j = 0; j < values.size(); j++)
			{
				if (pks[i].compare(columns[j]) == 0)
				{
					pkCondition += pks[i] + " = " + values[j];
					if (pks.size() > 1 && i < pks.size() - 1)
						pkCondition += " and ";
				}
			}
		}

		return  "Delete From " + table + " Where " + pkCondition;
	}
	
	std::string SelectStatement(std::string table, std::string condition)
	{
		return "Select * From " + table + (!condition.empty() ? " where "  + condition : "");
	}

	std::string UpdateStatement(std::string table, std::vector<std::string> columns, std::vector<std::string> values, std::vector<std::string> pks)
	{

		std::string vals = "";
		std::string pkCondition = "";
		std::vector<std::string>::iterator c = columns.begin(), v = values.begin();


		for (; c != columns.end(); ++c,++v) { vals +=  *c + " = " + *v + (*c != columns.at(columns.size() - 1) ? "," : ""); }
		for (int i = 0; i < pks.size(); i++)
		{
			for (int j = 0; j < values.size(); j++)
			{
				if (pks[i].compare(columns[j]) == 0)
				{
					pkCondition += pks[i] + " = " + values[j];
					if (pks.size() > 1 && i < pks.size() - 1)
						pkCondition += " and ";
				}
			}
		}

		return "Update " + table + " Set " + vals + " Where " + pkCondition;
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

	// Attempts to add an array of items to the database
	int Add(std::vector<Model*>* items, void* callback = NULL)
	{
		int rc = 0;
		for (auto item : *items) 
		{
			rc = sqlite3_exec(db, InsertStatement(item->Table(), item->Columns(), item->Values()).c_str(), (sqlite3_callback)callback, 0, &errMsg);
			if (rc != 0)
				return rc;

		}
		return rc;
	}

	// Removes a record from the database and returns the status code
	int Remove(Model* item, void* callback = NULL)
	{
		return sqlite3_exec(db, DeleteStatement(item->Table(), item->Columns(), item->Values(), item->primaryKeys()).c_str(), (sqlite3_callback)callback, 0, &errMsg);
	}

	// Attempts to remove the database records then delete c++ memory
	int Remove(std::vector<Model*>* items, void* callback = NULL)
	{
		int rc = 0;
		for (auto item : *items) 
		{
			rc = sqlite3_exec(db, DeleteStatement(item->Table(), item->Columns(), item->Values(), item->primaryKeys()).c_str(), (sqlite3_callback)callback, 0, &errMsg);
			if (rc != 0)
				return rc;
			delete item;
		}
		delete items;
		return rc;
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
		return sqlite3_exec(db, UpdateStatement(item->Table(), item->Columns(), item->Values(), item->primaryKeys()).c_str(), (sqlite3_callback)callback, 0, &errMsg);
	}


	int Update(std::vector<Model*>* items, void* callback = NULL)
	{
		int rc = 0;
		for (auto item : *items)
		{
			rc = sqlite3_exec(db, UpdateStatement(item->Table(), item->Columns(), item->Values(), item->primaryKeys()).c_str(), (sqlite3_callback)callback, 0, &errMsg);
			if (rc != 0)
				return rc;
		}
		return rc;
	}


	int Execute(std::string sql, void* callback = NULL, void* data = NULL) 
	{
		return sqlite3_exec(db, sql.c_str(), (sqlite3_callback)callback, data, &errMsg);
	}
};
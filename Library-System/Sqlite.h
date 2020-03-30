#include "sqlite3.h"
#include "Model.h"
#include <iostream>

class Sqlite  {
private:
	sqlite3* db;
	char* errMsg;

	std::string InsertStatement(std::string table, std::string columns, std::string values)
	{
		return  "Insert Into " + table + columns + "\nValues " + values + ";";
	}
	// TODO: Implement
	std::string DeleteStatement(std::string table)
	{
		return  "Delete From " + table + " where ";
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
			std::cout << "Opended database succesfully";
		}
	}

	~Sqlite() { sqlite3_close(db); }

	char* getErrorMessage() { return errMsg; };

	// Add the item to the database
	int Add(Model* item, void* callback)
	{
		return sqlite3_exec(db, InsertStatement(item->getTableName(), item->getColumns(), item->getValues()).c_str(), (sqlite3_callback)callback, 0, &errMsg);
	}

	int Remove(Model* item, void* callback)
	{

	}

	Model* Select(std::string table, std::string condition, void* callback)
	{
		int rc = sqlite3_exec(db, std::string("Select * From Books").c_str(), (sqlite3_callback)callback, 0, &errMsg);
		std::cout << rc;
		return nullptr;
	}

	int Execute(std::string sql, void* callback) 
	{
		return sqlite3_exec(db, sql.c_str(), (sqlite3_callback)callback, 0, &errMsg);
	}
};
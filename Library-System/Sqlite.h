#include "sqlite3.h"
#include "sqlite3.c"
#include "Model.h"
#include <iostream>

class Sqlite : public sqlite3 {
private:
	sqlite3* db;
	char* errMsg;

	std::string InsertStatement(std::string table, std::string columns, std::string values)
	{
		return  "Insert Into " + table + columns + "\nValues " + values + ";";
	}

public:
	Sqlite(std::string dbName) 
	{
		char* errMsg = 0;
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
};
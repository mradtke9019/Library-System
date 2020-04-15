#pragma once
#include <vector>

class Model {
private:
public:

	virtual std::string Table() = 0;
	// Returns the columns names of the table
	virtual std::vector<std::string> Columns() = 0;
	// Returns the values of the current record
	virtual std::vector<std::string> Values() = 0;
	
	//// Returns the name of the table
	//virtual std::string getTableName() = 0;
	//// Returns the columns names of the table
	//virtual std::string getColumns() = 0;
	//// Returns the values of the current record
	//virtual std::string getValues() = 0;
	////Gets the primary key of the object
	//virtual std::string getPrimaryKey() = 0;
	//virtual std::string getPrimaryKeyValue() = 0;
};
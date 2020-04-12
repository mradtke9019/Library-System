#pragma once

class Model {
private:
public:
	
	// Returns the name of the table
	static std::string getTableName() { return ""; };
	// Returns the columns names of the table
	static std::string getColumns() { return ""; };
	// Returns the values of the current record
	virtual std::string getValues() = 0;
	//Gets the primary key of the object
	virtual std::string getPrimaryKey() = 0;
	virtual std::string getPrimaryKeyValue() = 0;
};
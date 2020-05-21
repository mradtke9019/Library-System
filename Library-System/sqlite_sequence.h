#pragma once
#include "Model.h"
#include <vector>
#include <string>

class sqlite_sequence :  public Model {
private:
public:
	sqlite_sequence()
	{
	
	};
	std::string Table() { return "sqlite_sequence"; }
	std::string name;
	std::string seq;
	std::vector<std::string> Columns()
	{
		return std::vector<std::string>({"name","seq"});
	}
	std::vector<std::string> Values()
	{
		return std::vector<std::string>({"'" + name + "'","'" + seq + "'"});
	}
	static int selectCallback(void* data, int argc, char** argv, char** azColName)
	{
		std::vector<sqlite_sequence*>* sqlite_sequenceList = static_cast<std::vector<sqlite_sequence*>*>(data);
		sqlite_sequence* mysqlite_sequence= new sqlite_sequence();
		mysqlite_sequence->name = (std::string)(argv[0]);
		mysqlite_sequence->seq = (std::string)(argv[1]);

		sqlite_sequenceList->push_back(mysqlite_sequence);
		return 0;
	}
	std::string updateStatement()
	{
		return "Update sqlite_sequence Set name = '" + name + "',seq = '" + seq + "' Where name = '" + name + "'";
	}
};
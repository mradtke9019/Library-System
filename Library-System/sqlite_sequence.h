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
};
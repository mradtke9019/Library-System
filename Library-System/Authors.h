#pragma once
#include "Model.h"
#include <vector>
#include <string>

class Authors :  public Model {
private:
public:
	Authors()
	{
	
	};
	std::string Table() { return "Authors"; }
	int Id;
	std::string Name;
	std::string Address;
	std::string Phone;
	std::vector<std::string> Columns()
	{
		return std::vector<std::string>({"Id","Name","Address","Phone"});
	}
	std::vector<std::string> Values()
	{
		return std::vector<std::string>({std::to_string(Id),"'" + Name + "'","'" + Address + "'","'" + Phone + "'"});
	}
};
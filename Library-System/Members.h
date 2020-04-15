#pragma once
#include "Model.h"
#include <vector>
#include <string>

class Members :  public Model {
private:
public:
	Members()
	{
	
	};
	std::string Table() { return "Members"; }
	int Id;
	std::string Name;
	std::string Address;
	std::string Email;
	std::string Phone;
	std::vector<std::string> Columns()
	{
		return std::vector<std::string>({"Id","Name","Address","Email","Phone"});
	}
	std::vector<std::string> Values()
	{
		return std::vector<std::string>({std::to_string(Id),Name,Address,Email,Phone});
	}
};
#pragma once
#include "Model.h"
#include <vector>
#include <string>

class Members :  public Model {
private:
public:
	Members()
	{
		Id = 0;
		Name = "";
		Address = "";
		Email = "";
		Phone = "";
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
	static int selectCallback(void* data, int argc, char** argv, char** azColName)
	{
		std::vector<Members*>* MembersList = static_cast<std::vector<Members*>*>(data);
		Members* myMembers= new Members();
		myMembers->Id = (atoi)(argv[0]);
		myMembers->Name = (std::string)(argv[1]);
		myMembers->Address = (std::string)(argv[2]);
		myMembers->Email = (std::string)(argv[3]);
		myMembers->Phone = (std::string)(argv[4]);

		MembersList->push_back(myMembers);
		return 0;
	}
	std::vector<std::string> primaryKeys()
	{
		return std::vector<std::string>({"Id"});
	}
};
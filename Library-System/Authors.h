#pragma once
#include "Model.h"
#include <vector>
#include <string>

class Authors :  public Model {
private:
public:
	Authors()
	{
		Id = 0;
		Name = "";
		Address = "";
		Phone = "";
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
	static int selectCallback(void* data, int argc, char** argv, char** azColName)
	{
		std::vector<Authors*>* AuthorsList = static_cast<std::vector<Authors*>*>(data);
		Authors* myAuthors= new Authors();
		myAuthors->Id = (atoi)(argv[0]);
		myAuthors->Name = (std::string)(argv[1]);
		myAuthors->Address = (std::string)(argv[2]);
		myAuthors->Phone = (std::string)(argv[3]);

		AuthorsList->push_back(myAuthors);
		return 0;
	}
	std::vector<std::string> primaryKeys()
	{
		return std::vector<std::string>({"Id"});
	}
};
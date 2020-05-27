#pragma once
#include "Model.h"
#include <vector>
#include <string>

class Contributors :  public Model {
private:
public:
	Contributors()
	{
	
	};
	std::string Table() { return "Contributors"; }
	int BookISBN;
	int AuthorId;
	std::vector<std::string> Columns()
	{
		return std::vector<std::string>({"BookISBN","AuthorId"});
	}
	std::vector<std::string> Values()
	{
		return std::vector<std::string>({std::to_string(BookISBN),std::to_string(AuthorId)});
	}
	static int selectCallback(void* data, int argc, char** argv, char** azColName)
	{
		std::vector<Contributors*>* ContributorsList = static_cast<std::vector<Contributors*>*>(data);
		Contributors* myContributors= new Contributors();
		myContributors->BookISBN = (atoi)(argv[0]);
		myContributors->AuthorId = (atoi)(argv[1]);

		ContributorsList->push_back(myContributors);
		return 0;
	}
	std::string updateStatement()
	{
		return "Update Contributors Set BookISBN = " + std::to_string(BookISBN) + ",AuthorId = " + std::to_string(AuthorId) + " Where BookISBN = " + std::to_string(BookISBN);
	}
	std::vector<std::string> primaryKeys()
	{
		return std::vector<std::string>({"BookISBN","AuthorId"});
	}
};
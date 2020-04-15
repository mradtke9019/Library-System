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
};
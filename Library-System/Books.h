#pragma once
#include "Model.h"
#include <vector>
#include <string>

class Books :  public Model {
private:
public:
	Books()
	{
	
	};
	std::string Table() { return "Books"; }
	int ISBN;
	int Copies;
	std::string Title;
	std::string Summary;
	std::vector<std::string> Columns()
	{
		return std::vector<std::string>({"ISBN","Copies","Title","Summary"});
	}
	std::vector<std::string> Values()
	{
		return std::vector<std::string>({std::to_string(ISBN),std::to_string(Copies),"'" + Title + "'","'" + Summary + "'"});
	}
};
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
	static int selectCallback(void* data, int argc, char** argv, char** azColName)
	{
		std::vector<Books*>* BooksList = static_cast<std::vector<Books*>*>(data);
		Books* myBooks= new Books();
		myBooks->ISBN = (atoi)(argv[0]);
		myBooks->Copies = (atoi)(argv[1]);
		myBooks->Title = (std::string)(argv[2]);
		myBooks->Summary = (std::string)(argv[3]);

		BooksList->push_back(myBooks);
		return 0;
	}
	std::string updateStatement()
	{
		return "Update Books Set ISBN = " + std::to_string(ISBN) + ",Copies = " + std::to_string(Copies) + ",Title = '" + Title + "',Summary = '" + Summary + "' Where ISBN = " + std::to_string(ISBN);
	}
};
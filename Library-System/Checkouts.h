#pragma once
#include "Model.h"
#include <vector>
#include <string>

class Checkouts :  public Model {
private:
public:
	Checkouts()
	{
	
	};
	std::string Table() { return "Checkouts"; }
	int BookISBN;
	int MemberId;
	time_t LoanDate;
	time_t DueDate;
	std::vector<std::string> Columns()
	{
		return std::vector<std::string>({"BookISBN","MemberId","LoanDate","DueDate"});
	}
	std::vector<std::string> Values()
	{
		return std::vector<std::string>({std::to_string(BookISBN),std::to_string(MemberId),std::to_string(LoanDate),std::to_string(DueDate)});
	}
};
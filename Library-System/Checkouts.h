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
	static int selectCallback(void* data, int argc, char** argv, char** azColName)
	{
		std::vector<Checkouts*>* CheckoutsList = static_cast<std::vector<Checkouts*>*>(data);
		Checkouts* myCheckouts= new Checkouts();
		myCheckouts->BookISBN = (atoi)(argv[0]);
		myCheckouts->MemberId = (atoi)(argv[1]);
		myCheckouts->LoanDate = (atoll)(argv[2]);
		myCheckouts->DueDate = (atoll)(argv[3]);

		CheckoutsList->push_back(myCheckouts);
		return 0;
	}
	std::string updateStatement()
	{
		return "Update Checkouts Set BookISBN = " + std::to_string(BookISBN) + ",MemberId = " + std::to_string(MemberId) + ",LoanDate = " + std::to_string(LoanDate) + ",DueDate = " + std::to_string(DueDate) + " Where BookISBN = " + std::to_string(BookISBN);
	}
};
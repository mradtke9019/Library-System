#pragma once
#include <stdlib.h>
#include <string>
#include <exception>

class SqlException : public std::exception {
private:
	std::string errMsg;
public:
	SqlException(std::string error)
	{
		errMsg = error;
	}
	SqlException(char* error)
	{
		errMsg = error;
	}
	const char* what() const throw()
	{
		return errMsg.c_str();
	}
};
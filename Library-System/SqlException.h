#pragma once
#include <stdlib.h>
#include <exception>

class SqlException : std::exception {
private:
	std::string errMsg;
public:
	SqlException(std::string error)
	{
		errMsg = error;
	}
	const char* what() const throw()
	{
		return errMsg.c_str();
	}
};
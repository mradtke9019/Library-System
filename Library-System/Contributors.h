#pragma once
#include <string>
#include "Model.h"

class Contributor : public Model {
private:
	long BookISBN;
	int authorId;
public:
	Contributor(long isbn, int aId)
	{
		BookISBN = isbn;
		authorId = aId;
	};
	long getBookISBN() { return BookISBN; }
	int getAuthorId() { return authorId; }

	std::string getTableName() { return "Contributors"; };
	std::string getColumns() { return "(BookISBN, AuthorId)"; };
	std::string getValues() { return "(" + std::to_string(BookISBN) + ',' + std::to_string(authorId) + "')"; };
	std::string getPrimaryKey() { return "BookISBN"; };
	std::string getPrimaryKeyValue() { return std::to_string(BookISBN); };
};
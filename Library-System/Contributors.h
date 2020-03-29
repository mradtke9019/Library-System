#pragma once
#include <string>
#include "Model.h"

class Contributors : Model {
private:
	long BookISBN;
	int authorId;
public:
	Contributors(long isbn, int aId)
	{
		BookISBN = isbn;
		authorId = aId;
	};
	long getBookISBN() { return BookISBN; }
	int getAuthorId() { return authorId; }
	std::string static getColumns() { return "(BookISBN, AuthorId)"; };
	std::string getValues() { return "(" + std::to_string(BookISBN) + ',' + std::to_string(authorId) + "')"; };
};
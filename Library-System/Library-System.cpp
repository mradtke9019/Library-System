// Library-System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Books.h"
#include "Model.h"
#include "Sqlite.h"
#include "Authors.h"
#include <vector>


//Callback function provides us a way to look obtain results from select statements
static int callback(void* data, int argc, char** argv, char** azColName) 
{
	int i;
	//fprintf(stderr, "%s: ", (const char*)data);

	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}


int main()
{
	Sqlite* db = new Sqlite("Library.db");

	Book* myBook = new Book(12, 1, "Old man and the sea", "A book about an old man and some sea");
	Model* dbModel = new Book(1212312, 1, "Old man and the sea", "A book about an old man and some sea");
	Author* a = new Author(1, "Matt R", "NULL", "NULL");

	db->Add(a, callback);

	std::vector<Model*> books;
	if (db->Select(&books, Book::getTableName(), std::string(), callback))
	{
		std::cout << db->getErrorMessage() << std::endl;
	}
	//db->Add(a, callback);
}
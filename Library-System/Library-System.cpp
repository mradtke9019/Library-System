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

	//Books* myBook = new Book(982, 1, "Old man and the sea", "A book about an old man and some sea");
	//Model* dbModel = new Book(1212312, 1, "Old man and the sea", "A book about an old man and some sea");

	Books* b = new Books();
	b->Title = "Physics 101";
	b->ISBN = 5551;
	b->Copies = 1;
	b->Summary = "A book about physics";

	//Author* a = new Author(1, "Matt R", "NULL", "NULL");

	std::cout << "Add: " << db->Add(b) << "\n";
	b->Summary = "Updating physics book";
	std::cout << "Update: " << db->Update(b) << "\n";
	Books* bCheck = db->Select<Books>("Books", "ISBN = 5551", Books::selectCallback)->at(0);
	std::cout << "Remove: " << db->Remove(b) << "\n";
	std::cout<< "Size should be 0. Size: " << db->Select<Books>("Books", "ISBN = 5551", Books::selectCallback)->size() << "\n";

	//std::vector<Books*>* books = db->Select<Books>("Books", "", Books::selectCallback);
	//books->at(0)->Summary = "This is an updated summary";
}
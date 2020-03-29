// Library-System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "Books.h"
#include "sqlite3.h"
#include <vector>

//Callback function provides us a way to look obtain results from select statements
static int callback(void* data, int argc, char** argv, char** azColName) 
{
	int i;
	fprintf(stderr, "%s: ", (const char*)data);

	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	return 0;
}

std::string InsertStatement(std::string table, std::string columns, std::string values)
{
	return  "Insert Into " + table + columns + "\nValues " + values + ";";
}

// Add Book to database and return the status of the insert.
// Return the status of the transaction
int AddBook(sqlite3* db, Book* book, char* errMsg) 
{
	return sqlite3_exec(db,InsertStatement("Books",book->getColumns(), book->getValues()).c_str(), callback, 0, &errMsg);
}

void SelectBook(sqlite3* db, std::string sql) 
{

}


// Iterate over each book and add to database
//int AddBooks(sqlite3* db, vector<Book> books, char errMsg) 
//{
//	//foreach book in books -> AddBook(book)
//
//	return 0;
//}


int main()
{
	sqlite3* db;

	char* errMsg = 0;
	int rc;

	rc = sqlite3_open("Library.db", &db);
	if (rc) {

		std::cout << "Cant open database" << sqlite3_errmsg(db);
	}
	else {
		std::cout << "Opended database succesfully";
	}
	Book* myBook = new Book(123, 1, "Old man and the sea", "A book about an old man and some sea");

	std::cout << "Adding myBook" << std::endl << myBook->getValues() << std::endl;
	if (AddBook(db, myBook, errMsg) != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", errMsg);
		sqlite3_free(errMsg);
	}
	else {
		fprintf(stdout, "Records created successfully\n");
	}

	sqlite3_close(db);
}
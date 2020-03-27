// Library-System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sqlite3.h>



using namespace std;

struct Name {
	std::string first;
	std::string last;
};

struct ContactInfo {
	std::string email;
	long phone;
};

struct Author {
	int id;
	Name name;
};

struct Member {
	int id;
	Name name;
	ContactInfo info;
};


struct Book {
	long ISBN;
	vector<Author> authors;
	int count;
};


struct BookLoan {
	Member borrower;
	Book book;
	time_t dateBorrowed;
};

int main()
{
    std::cout << "Hello World!\n";
}
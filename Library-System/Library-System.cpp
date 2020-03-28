// Library-System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>



using namespace std;

class Name {
private:
	std::string first;
	std::string last;
public:
};

class ContactInfo {
private:
	std::string email;
	long phone;
public:
};

class Author {
private:
	int id;
	Name name;
public:
};

class Member {
private:
	int id;
	Name name;
	ContactInfo info;
public:
};


class Book {
private:
	long ISBN;
	vector<Author> authors;
	int count;
public: 
};


struct BookLoan {
private:
	Member borrower;
	Book book;
	time_t dateBorrowed;
public:
};

int main()
{
    std::cout << "Hello World!\n";
}
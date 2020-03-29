#pragma once
#include <string>

class Book {
private:
	long ISBN;
	int copies;
	std::string title;
	std::string summary;
public:
	Book(long isbn, int Copies, std::string Title, std::string Summary) {
		ISBN = isbn;
		copies = Copies;
		title = Title;
		summary = Summary;
	}
	long getISBN() { return ISBN; };
	int getCopies() { return copies; };
	std::string getTitle() { return title; };
	std::string getSummary() { return summary; };
	std::string static getColumns() { return "(ISBN, Copies, Title, Summary)"; };
	std::string getValues() { return "(" + std::to_string(ISBN) + ',' + std::to_string(copies) + ",'" + title + "','" + summary + "')"; };
};

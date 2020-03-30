#pragma once
#include <string>
#include "Model.h"

class Author : public Model {
private:
	int Id;
	std::string name;
	std::string address;
	std::string phone;
public:
	Author (int id, std::string Name, std::string Address, std::string Phone) {
		Id = id;
		name = Name;
		address = Address;
		phone = Phone;
	}
	int getId() { return Id; };
	std::string getName() { return name; };
	std::string getAddress() { return address; };
	std::string getPhone() { return phone; };

	std::string getTableName() { return "Authors"; };
	std::string getColumns() { return "(Id, Name, Address, Phone)"; };
	std::string getValues() { return "(" + std::to_string(Id) + ",'" + name + "','" + address + "','" + phone + "')"; };
	std::string getPrimaryKey() { return "Id"; };
	std::string getPrimaryKeyValue() { return std::to_string(Id); };
};
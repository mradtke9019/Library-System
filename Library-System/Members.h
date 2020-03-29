#pragma once
#include <string>
#include "Model.h"

class Member : public Model {
private: 
	int Id;
	std::string name;
	std::string address;
	std::string email;
	std::string phone;

public:
	Member(int id, std::string Name, std::string Address, std::string Email, std::string Phone) {
		Id = id;
		name = Name;
		address = Address;
		email = Email;
		phone = Phone;
	}
	int getId() { return Id; };
	std::string getName() { return name; };
	std::string getAddress() { return address; };
	std::string getEmail() { return email; };
	std::string getPhone() { return phone; };

	std::string getTableName() { return "Members"; };
	std::string getColumns() { return "(Id, Name, Address, Email, Phone)"; };
	std::string getValues() { return "(" + std::to_string(Id) + ",'" + name+ "','" + address + "','" + email + "','" + phone + "')"; };
};
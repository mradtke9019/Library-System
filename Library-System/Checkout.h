#pragma once
#include <string>
#include "Model.h"

class Checkout : public Model {
private:
	long BookISBN;
	int memberId;
	time_t loanDate;
	time_t dueDate;

};
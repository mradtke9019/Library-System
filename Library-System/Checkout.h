#pragma once
#include <string>
#include "Model.h"

class Checkout : Model {
private:
	long BookISBN;
	int memberId;
	time_t loanDate;
	time_t dueDate;

};
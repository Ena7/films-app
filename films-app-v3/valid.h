#pragma once
#include "film.h"
#include <string>
#include <vector>
#include <ostream>
using std::vector;
using std::string;
using std::ostream;

class ValidException {
	vector<string> msgs;
public:
	ValidException(const vector<string>& errors): msgs{errors} {}
	friend ostream& operator<<(ostream& out, const ValidException& ex);
};

ostream& operator<<(ostream& out, const ValidException& ex);

class Validator {
public:

	//valideaza un film
	//exceptie daca: titlu este vid, genul este vid, actorul este vid, anul este mai mic decat 1800
	void validate(const Film& film);
};

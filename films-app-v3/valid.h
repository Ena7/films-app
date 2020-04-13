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
	void validate(const Film& film);
};

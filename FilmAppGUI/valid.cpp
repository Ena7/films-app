#include "valid.h"


void Validator::validate(const Film& film){
	vector<string> errors;
	if (film.getTitle().size() == 0) {
		errors.push_back("The title is blank!");
	}	
	if (film.getGenre().size() == 0) {
		errors.push_back("The genre is blank!");
	}	
	if (film.getYear() < 1800) {
		errors.push_back("Invalid year!");
	}
	if (film.getActor().size() == 0) {
		errors.push_back("The actor is blank!");
	}
	if (errors.size() > 0) {
		throw ValidException(errors);
	}
}

ostream& operator<<(ostream& out, const ValidException& ex) {
	for (const string& msg : ex.msgs) {
		out << msg << "\n";
	}
	return out;
}
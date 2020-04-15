#include "srv.h"
#include <algorithm>
#include <string>

void Service::addSRV(const string& title, const string& genre, int year, const string& actor) {
	Film film{ title, genre, year, actor };
	valid.validate(film);
	repo.addREPO(film);
}

const vector<Film>& Service::getAllSRV() const noexcept{
	return repo.getAllREPO();
}

void Service::removeSRV(const string& title, const int& year){
	repo.removeREPO(title, year);
}

void Service::editSRV(const string& title, const string& newtitle, const string& newgenre, const int& newyear, const string& newactor){
	repo.editREPO(title, newtitle, newgenre, newyear, newactor);
}

const Film& Service::findSRV(const string& title, const int& year) const{
	return repo.findREPO(title, year);
}

void Service::filterByTitleSRV(const string& letter, vector<Film>& filter) {

	std::copy_if(getAllSRV().begin(), getAllSRV().end(), std::back_inserter(filter), [&letter](const Film& film) { return film.getTitle().at(0) == letter.at(0); });
}

void Service::filterByYearSRV(const int& upperyear, vector<Film>& filter) {	
	
	std::copy_if(getAllSRV().begin(), getAllSRV().end(), std::back_inserter(filter), [&upperyear](const Film& film) noexcept { return film.getYear() <= upperyear; });
}

void Service::sortBySRV(bool(*compare)(const Film&, const Film&), vector<Film>& sorted) {
	
	std::sort(sorted.begin(), sorted.end(), compare);
}

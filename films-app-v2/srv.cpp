#include "srv.h"
#include <algorithm>
#include <string>
#include <map>
using std::map;

void Service::sort(LkdLst<Film>& sorted, bool(*compara)(const Film&, const Film&)) {
	for (unsigned int i = 0; i < sorted.size() - 1; i++) {
		for (unsigned int j = i + 1; j < sorted.size(); j++) {
			if (!compara(sorted[i], sorted[j])) {
				Film aux = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = aux;
			}
		}
	}
}

void Service::addSRV(const string& title, const string& genre, int year, const string& actor) {
	Film film{ title, genre, year, actor };
	valid.validate(film);
	repo.addREPO(film);
}

const LkdLst<Film>& Service::getAllSRV() const noexcept{
	return repo.getAllREPO();
}

void Service::removeSRV(const string& title, const int& year){
	repo.removeREPO(title, year);
}

void Service::editSRV(const string& title, const string& newtitle, const string& newgenre, const int& newyear, const string& newactor){
	repo.editREPO(title, newtitle, newgenre, newyear, newactor);
}

LkdLst<Film> Service::findSRV(const string& title) const{
	return repo.findREPO(title);
}

void Service::filterByTitleSRV(const string& letter, LkdLst<Film>& filter){
	for (const Film& film : getAllSRV()) {
		if (film.getTitle().at(0) == letter.at(0)) {
			filter.push_back(film);
		}
	}
}

void Service::filterByYearSRV(const int& upperyear, LkdLst<Film>& filter){
	for (const Film& film : getAllSRV()) {
		if (film.getYear() <= upperyear) {
			filter.push_back(film);
		}
	}
}

const LkdLst<Film> Service::sortBySRV(bool(*compare)(const Film&, const Film&)) {
	LkdLst<Film> sorted{ getAllSRV() };
	sort(sorted, compare);
	return sorted;
}

vector<DTO> Service::statistics() {
	map<string, DTO> map;
	for (const Film& film : getAllSRV()) {
		if (map.find(film.getGenre()) == map.end()) {
			DTO f{ film.getGenre() };
			map[film.getGenre()] = f;
		}
		else {
			map[film.getGenre()].inc();
		}
	}
	vector<DTO> DTOs;
	for (const auto& iterator : map)
		DTOs.push_back(iterator.second);
	return DTOs;
}

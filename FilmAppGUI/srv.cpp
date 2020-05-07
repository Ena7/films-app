#include "srv.h"
#include <algorithm>
#include <numeric>
#include <string>
#include <map>
using std::map;

void Service::undo() {
	if (undoActions.empty()) {
		throw RepoException("\nThere is nothing to undo!\n"); }
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

void Service::addSRV(const string& title, const string& genre, int year, const string& actor) {
	Film film{ title, genre, year, actor };
	valid.validate(film);
	repo.addREPO(film);
	undoActions.push_back(std::make_unique<UndoAdd>(repo, film));
}

vector<Film> Service::getAllSRV() const noexcept{
	return repo.getAllREPO();
}

void Service::removeSRV(const string& title, const int& year){
	const Film removed_film = repo.findREPO(title, year);
	repo.removeREPO(title, year);
	undoActions.push_back(std::make_unique<UndoRemove>(repo, removed_film));
}

void Service::editSRV(const string& title, const int& year, const string& newtitle, const string& newgenre, const int& newyear, const string& newactor){
	const Film old_film = repo.findREPO(title, year);
	Film film{ newtitle, newgenre, newyear, newactor };
	valid.validate(film);
	repo.editREPO(title, year, newtitle, newgenre, newyear, newactor);
	undoActions.push_back(std::make_unique<UndoEdit>(repo, old_film, newtitle, newyear));
}

const Film& Service::findSRV(const string& title, const int& year) const{
	return repo.findREPO(title, year);
}

void Service::filterByTitleSRV(const string& letter, vector<Film>& filter) {

	vector<Film> list = getAllSRV();
	std::copy_if(list.begin(), list.end(), std::back_inserter(filter), [&letter](const Film& film) { return film.getTitle().at(0) == letter.at(0); });
}

void Service::filterByYearSRV(const int& upperyear, vector<Film>& filter) {	
	
	vector<Film> list = getAllSRV();
	std::copy_if(list.begin(), list.end(), std::back_inserter(filter), [&upperyear](const Film& film) noexcept { return film.getYear() <= upperyear; });
}

void Service::sortBySRV(bool(*compare)(const Film&, const Film&), vector<Film>& sorted) {
	
	std::sort(sorted.begin(), sorted.end(), compare);
}

vector<DTO> Service::statistics() {
	map<string, DTO> map;
	vector<Film> list = getAllSRV();
	//identifies the genres and set their count to 0
	for (const Film& film : list) {
		if (map.find(film.getGenre()) == map.end()) {
			DTO f{ film.getGenre() };
			map[film.getGenre()] = f;
		}
	}
	//each genre found has its count set using the main list
	for (auto& it : map) {
		int count = 0;
		it.second.setCount(std::accumulate(list.begin(), list.end(), count, [&it](const int& count, const Film& film) { if (it.first == film.getGenre()) return count + 1; return count; }));
	}
	vector<DTO> DTOs;
	std::transform(map.begin(), map.end(), std::back_inserter(DTOs), [](const auto& it) noexcept { return it.second; });
	return DTOs;
}


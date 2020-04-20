#include "repo.h"
#include <algorithm>
#include <exception>
#include <fstream>

ostream& operator<<(ostream& out, const RepoException& ex){
	out << ex.msg;
	return out;
}

void Repository::addREPO(Film& film){
	if (films.size() == 0) {
		films[0] = film;
		uniq = 1;
		return;
	}
	auto match = std::find_if(films.begin(), films.end(), [&film](const auto& it) noexcept { return it.second == film; });
	if (match != films.end()) {
		throw RepoException("\nThe film with this title and year already exists!\n");
	}
	films[uniq++] = film;
}

void Repository::removeREPO(const string& title, const int& year){
	auto match = std::find_if(films.begin(), films.end(), [&title, &year](const auto& it) { return it.second.getTitle() == title && it.second.getYear() == year; });
	if(match != films.end()){
		films.erase(match);
		return;
	}
	throw RepoException("\nThis film does not exist!\n"); }

void Repository::editREPO(const string& title, const string& newtitle, const string& newgenre, const int& newyear, const string& newactor){
	auto match = std::find_if(films.begin(), films.end(), [&title](const auto& it) { return it.second.getTitle() == title; });
	if (match != films.end()) {
		match->second.setTitle(newtitle);
		match->second.setGenre(newgenre);
		match->second.setYear(newyear);
		match->second.setActor(newactor);
		return;
	}
	throw RepoException("\nThe film with the specified title and year does not exist!\n"); }

const Film& Repository::findREPO(const string& title, const int& year) const{
	auto match = std::find_if(films.begin(), films.end(), [&title, &year](const auto& it) { return it.second.getTitle() == title && it.second.getYear() == year; });
	if (match != films.end()) {
		return match->second;
	}
	throw RepoException("\nThe film with the specified title and year does not exist!\n"); }

vector<Film> Repository::getAllREPO() const noexcept{
	vector<Film> list;
	for (const auto& iterator : films) {
		list.push_back(iterator.second);
	}
	return list;
}

void FileRepository::readFile() {
	std::ifstream fin(filename);
	if (!fin.is_open()) { throw RepoException("\nError open file!\n"); }
	while (!fin.eof()) {
		string title, genre, year, actor;
		std::getline(fin, title, ',');
		if (fin.eof()) break;
		std::getline(fin, genre, ',');
		std::getline(fin, year, ',');
		std::getline(fin, actor, '\n');
		Film f{ title, genre, std::stoi(year), actor };
		Repository::addREPO(f);
	}
	fin.close();
}

void FileRepository::writeFile() {
	std::ofstream fout(filename);
	if (!fout.is_open()) { throw RepoException("\nError open file!\n"); }
	for (const Film& film : getAllREPO()) {
		fout << film.getTitle() << "," << film.getGenre() << "," << film.getYear() << "," << film.getActor() << std::endl;
	}
	fout.close();
}


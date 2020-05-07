#include "repo.h"
#include <algorithm>
#include <exception>
#include <fstream>

ostream& operator<<(ostream& out, const RepoException& ex){
	out << ex.msg;
	return out;
}

void Repository::addREPO(Film& film){
	if (films.find(film.getTitle() + std::to_string(film.getYear())) != films.end()) {
		throw RepoException("\nThe film with this title and year already exists!\n");
	}
	films[film.getTitle() + std::to_string(film.getYear())] = film;
}

void Repository::removeREPO(const string& title, const int& year){
	auto match = films.find(title + std::to_string(year));
	if(match != films.end()){
		films.erase(match);
		return;
	}
	throw RepoException("\nThis film does not exist!\n"); }

void Repository::editREPO(const string& title, const int& year, const string& newtitle, const string& newgenre, const int& newyear, const string& newactor){
	auto match = films.find(title + std::to_string(year));
	if (match != films.end()) {
		removeREPO(title, year);
		Film f{ newtitle, newgenre, newyear, newactor };
		addREPO(f);
		return;
	}
	throw RepoException("\nThe film with the specified title and year does not exist!\n"); }

const Film& Repository::findREPO(const string& title, const int& year) const{
	auto match = films.find(title + std::to_string(year));
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


#include "repo.h"
#include <algorithm>
#include <exception>

ostream& operator<<(ostream& out, const RepoException& ex){
	out << ex.msg;
	return out;
}

void Repository::addREPO(const Film& film){
	for (const Film& f : films) {
		if (f.getTitle() == film.getTitle() && f.getYear() == film.getYear()) {
			throw RepoException("\nThe film with this title and year already exists!\n");
		}
	}
	films.push_back(film);
}

void Repository::removeREPO(const string& title, const int& year){
	const auto size = films.size();
	films.erase(remove_if(films.begin(), films.end(), [&title, &year](const Film& film) { return film.getTitle() == title && film.getYear() == year; }), films.end());
	if(size != films.size()){
		return;
	}
	throw RepoException("\nThis film does not exist!\n");
}

void Repository::editREPO(const string& title, const string& newtitle, const string& newgenre, const int& newyear, const string& newactor){
	for (Film& film : films) {
		if (film.getTitle() == title) {
			film.setTitle(newtitle);
			film.setGenre(newgenre);
			film.setYear(newyear);
			film.setActor(newactor);
			return;
		}
	}
	throw RepoException("\nThis film does not exist!\n");
}

const Film& Repository::findREPO(const string& title, const int& year) const{
	auto match = std::find_if(films.begin(), films.end(), [&title, &year](const Film& film) { return film.getTitle() == title && film.getYear() == year; });
	if (match != films.end()) {
		return *match;
	}
	throw RepoException("\nThe film with the specified title and year does not exist!\n"); }

const vector<Film>& Repository::getAllREPO() const noexcept{
	return films;
}


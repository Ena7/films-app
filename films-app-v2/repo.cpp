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
	//for (const Film& film : films) {
	//	if (film.getTitle() == title && film.getYear() == year) {
	//		films.erase(remove(films.begin(), films.end(), film), films.end());
	//		return;
	//	}
	//}
	//throw RepoException("\nThis film does not exist!\n");

	for (unsigned int pos = 0; pos < films.size(); pos++) {
		if (films.at(pos).getTitle() == title && films.at(pos).getYear() == year) {
			//films.erase(films.begin() + pos);
			films.erase(pos);
			return;
		}
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

LkdLst<Film> Repository::findREPO(const string& title) const{
	LkdLst<Film> matches;
	for (const Film& film : films) {
		if (film.getTitle() == title) {
			matches.push_back(film);
		}
	}
	if (matches.size() == 0) {
		throw RepoException("\nFilms with this title do not exist!\n");
	}
	return matches;
}

const LkdLst<Film>& Repository::getAllREPO() const noexcept{
	return films;
}

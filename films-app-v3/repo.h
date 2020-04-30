#pragma once
#include "film.h"
#include <vector>
#include <string>
#include <ostream>
#include <unordered_map>

using std::vector;
using std::string;
using std::ostream;

class RepoException {
	string msg;
public:
	RepoException(const string& err) : msg{ err } {}
	friend ostream& operator<<(ostream& out, const RepoException& ex);
};

ostream& operator<<(ostream& out, const RepoException& ex);

class Repository {
private:
	std::unordered_map<string,Film> films;

public:
	Repository() = default;
	//nu permite copierea de obiecte Repository
	Repository(const Repository& nocopy) = delete;

	//aduga la lista de filme un film
	virtual void addREPO(Film& film);

	//sterge un film avand un titlu si un an dat
	virtual void removeREPO(const string& title, const int& year);

	//cauta filmul cu titlul si anul dat, apoi ii modifica toate atributele cu cele noi
	virtual void editREPO(const string& title, const int& year, const string& newtitle, const string& newgenre, const int& newyear, const string& newactor);

	//returneaza filmul cu titlul si anul dat
	const Film& findREPO(const string& title, const int& year) const;

	//returneaza lista de filme in ordinea adaugarii
	vector<Film> getAllREPO() const noexcept;
	
};

class FileRepository : public Repository {
private:
	string filename;
	void readFile();
	void writeFile();
public:
	FileRepository(const string& filename) : Repository(), filename{ filename } {
		readFile();
	}
	void addREPO(Film& film) override {
		Repository::addREPO(film);
		writeFile();
	}
	void removeREPO(const string& title, const int& year) override {
		Repository::removeREPO(title, year);
		writeFile();
	}
	void editREPO(const string& title, const int& year, const string& newtitle, const string& newgenre, const int& newyear, const string& newactor) override {
		Repository::editREPO(title, year, newtitle, newgenre, newyear, newactor);
		writeFile();
	}
};

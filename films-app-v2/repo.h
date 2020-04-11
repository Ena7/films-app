#pragma once
#include "film.h"
#include "linked_list.h"
#include <vector>
#include <string>
#include <ostream>

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
	LkdLst<Film> films;

public:
	Repository() = default;
	//nu permite copierea de obiecte Repository
	Repository(const Repository& nocopy) = delete;

	//aduga la lista de filme un film
	void addREPO(const Film& film);

	//sterge un film avand un titlu dat
	void removeREPO(const string& title, const int& year);

	//cauta filmul cu titlu dat, apoi ii modifica toate atributele cu cele noi
	void editREPO(const string& title, const string& newtitle, const string& newgenre, const int& newyear, const string& newactor);

	//returneaza filmul cu titlul dat
	LkdLst<Film> findREPO(const string& title) const;

	//returneaza lista de filme in ordinea adaugarii
	const LkdLst<Film>& getAllREPO() const noexcept;
	
};
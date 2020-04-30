#pragma once
#include "film.h"
#include <vector>
#include <unordered_map>

class IRepo {
protected:
	std::unordered_map<string, Film> films;
public:
	virtual void addREPO(Film& film) = 0;

	//sterge un film avand un titlu si un an dat
	virtual void removeREPO(const string& title, const int& year) = 0;

	//cauta filmul cu titlul si anul dat, apoi ii modifica toate atributele cu cele noi
	virtual void editREPO(const string& title, const int& year, const string& newtitle, const string& newgenre, const int& newyear, const string& newactor) = 0;

	//returneaza filmul cu titlul si anul dat
	virtual const Film& findREPO(const string& title, const int& year) const = 0;

	//returneaza lista de filme in ordinea adaugarii
	virtual std::vector<Film> getAllREPO() const noexcept = 0;
};
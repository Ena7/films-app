#pragma once
#include "repo.h"
#include "valid.h"
#include "linked_list.h"
#include "DTO.h"


class Service {
	Repository& repo;
	Validator& valid;

public:
	
	Service(Repository& repo, Validator& valid) noexcept: repo{ repo }, valid{ valid } {}

	//nu permite copierea de obiecte Service
	Service(const Service& nocopy) = delete;

	void sort(LkdLst<Film>& sorted, bool(*compara)(const Film&, const Film&));

	//creeaza un film, avand atributele: titlu, gen, anul aparitiei si actor principal
	void addSRV(const string& title, const string& genre, int year, const string& actor);

	//returneaza lista de filme in ordinea adaugarii
	const LkdLst<Film>& getAllSRV() const noexcept;

	//sterge un film avand titlul dat
	void removeSRV(const string& title, const int& year);

	//cauta filmul cu titlu dat, apoi ii modifica toate atributele cu cele noi
	void editSRV(const string& title, const string& newtitle, const string& newgenre, const int& newyear, const string& newactor);

	//returneaza filmul cu titlul dat
	LkdLst<Film> findSRV(const string& title) const;

	//returneaza o lista de filme ale caror titluri incep cu o litera data
	void filterByTitleSRV(const string& letter, LkdLst<Film>& filter);

	//returneaza o lista de filme ale caror ani de aparitie sunt mai mici decat un an dat
	void filterByYearSRV(const int& upperyear, LkdLst<Film>& filter);

	/*
	returneaza o lista sortata de filme dupa criteriul functiei care compara 2 filme: compare
	compare - poate fi o functie lambda (care nu capteaza nimic)
			- poate fi o functie in afara unei clase, care returneaza bool si are ca parametrii 2 filme
	*/
	const LkdLst<Film> sortBySRV(bool(*compare)(const Film&, const Film&));

	//returneaza un vector reprezentand un raport ce contine numarul de filme pentru fiecare gen existent
	//in baza de date
	vector<DTO> statistics();

};

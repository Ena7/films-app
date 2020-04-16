#pragma once
#include <string>
#include <iostream>

using std::string;

class Film {
	string title;
	string genre;
	int year;
	string actor;
	
public:
	Film() : title{ "" }, genre{ "" }, year{ 1801 }, actor{ "" } {}
	Film(const string t, const string g, const int y, const string a) : title{ t }, genre{ g }, year{ y }, actor{ a } {}
	//Film(const Film& f) : title{ f.title }, genre{ f.genre }, year{ f.year }, actor{ f.actor } {std::cout << " #"; }

	//gettere
	string getTitle() const;
	string getGenre() const;
	int getYear() const noexcept;
	string getActor() const;

	//settere
	void setTitle(const string& newtitle);
	void setGenre(const string& newgenre);
	void setYear(const int& newyear) noexcept;
	void setActor(const string& newactor);

	//overriden operators
	bool operator==(const Film& film) const noexcept;
};

//compara dupa anul aparitiei (criteriu principal) si gen (criteriu secundar)
bool cmpYearAndGenre(const Film& f1, const Film& f2);

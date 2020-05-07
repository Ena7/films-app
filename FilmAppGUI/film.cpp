#include "film.h"

string Film::getTitle() const {
	return title;
}

string Film::getGenre() const {
	return genre;
}

int Film::getYear() const noexcept {
	return year;
}

string Film::getActor() const {
	return actor;
}

//not used
//void Film::setTitle(const string& newtitle) {
//	title = newtitle;
//}
//
//void Film::setGenre(const string& newgenre) {
//	genre = newgenre;
//}
//
//void Film::setYear(const int& newyear) noexcept {
//	year = newyear;
//}
//
//void Film::setActor(const string& newactor) {
//	actor = newactor;
//}

bool Film::operator==(const Film& film) const noexcept {
	return title == film.title && genre == film.genre && year == film.year && actor == film.actor;
}

bool cmpYearAndGenre(const Film& f1, const Film& f2) {
	if (f1.getYear() == f2.getYear()) {
		return f1.getGenre() < f2.getGenre();
	}
	return f1.getYear() < f2.getYear();
}


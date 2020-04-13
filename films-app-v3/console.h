#pragma once
#include "srv.h"
#include "film.h"

class Console {
	Service& srv;

	void addUI();
	void removeUI();
	void editUI();
	void findUI();
	void filterByTitleUI();
	void filterByYearUI();
	void sortUI(bool(*compare)(const Film&, const Film&));
	void printUI(const vector<Film>& films);
public:
	Console(Service& srv) noexcept : srv{ srv } {}
	Console(const Console& nocopy) = delete;

	void run();
};

void checkInt(const int& input);
#pragma once
#include "srv.h"
#include "srvc.h"
#include "film.h"

class Console {
	Service& srv;
	ServiceCart& srvc;

	void addUI();
	void removeUI();
	void editUI();
	void findUI();
	void filterByTitleUI();
	void filterByYearUI();
	void sortUI(bool(*compare)(const Film&, const Film&));
	void printUI(const vector<Film>& films);

	void addToCartUI();
	void generateUI();
	void exportUI();

public:
	Console(Service& srv, ServiceCart& srvc) noexcept : srv{ srv }, srvc{ srvc } {}
	Console(const Console& nocopy) = delete;

	void run();
};

void checkInt(const int& input);
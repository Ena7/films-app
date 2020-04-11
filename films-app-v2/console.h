#pragma once
#include "srv.h"
#include "film.h"
#include "linked_list.h"

class Console {
	Service& srv;

	void addUI();
	void removeUI();
	void editUI();
	void findUI();
	void filterByTitleUI();
	void filterByYearUI();
	void printUI(const LkdLst<Film>& films);
	void statisticsUI();
public:
	Console(Service& srv) noexcept : srv{ srv } {}
	Console(const Console& nocopy) = delete;

	void run();
};

void checkInt(const int& input);
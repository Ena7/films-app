#include "console.h"
#include <iostream>
#include <string>
#include <iomanip>

using std::cin;
using std::cout;
using std::string;

void checkInt(int& input) {
	bool cond;
	do {
		cin >> input;
		cond = cin.fail();
		cin.clear();
		cin.ignore();
		if (cond) {
			cout << "Invalid data type! Try again: ";
		}
	} while (cond);
}

void Console::addUI() {
	string title, genre, actor; int year;
	cout << "Input title: "; cin >> title;
	cout << "Input genre: "; cin >> genre;
	cout << "Input year: "; checkInt(year);
	cout << "Input actor: "; cin >> actor;
	srv.addSRV(title, genre, year, actor);
}

void Console::removeUI() {
	string title; int year;
	cout << "Input title: "; cin >> title;
	cout << "Input year: "; checkInt(year);
	srv.removeSRV(title, year);
}

void Console::editUI() {
	string title, newtitle, newgenre, newactor; int year, newyear;
	cout << "Input title: "; cin >> title;
	cout << "Input year: "; checkInt(year);
	cout << "Input new title: "; cin >> newtitle;
	cout << "Input new genre: "; cin >> newgenre;
	cout << "Input new year: "; checkInt(newyear);
	cout << "Input new actor: "; cin >> newactor;
	srv.editSRV(title, year, newtitle, newgenre, newyear, newactor);
}

void Console::findUI() {
	string title; int year;
	cout << "Input title: "; cin >> title;
	cout << "Input year: "; checkInt(year);
	auto match = srv.findSRV(title, year);
	cout << std::left << std::setw(15) << std::endl << match.getTitle() << " | " << std::setw(10) << match.getGenre() << " | " << std::setw(4) << match.getYear() << " | " << std::setw(13) << match.getActor() << "\n";
}
void Console::filterByTitleUI() {
	string letter;
	cout << "Input letter: "; cin >> letter;
	if (letter.size() != 1) {
		cout << "Input must be a letter! ";
		filterByTitleUI();
		return;
	}
	vector<Film> filtered;
	srv.filterByTitleSRV(letter, filtered);
	printUI(filtered);
}

void Console::filterByYearUI() {
	int upperyear;
	cout << "Input upper year: "; checkInt(upperyear);
	vector<Film> filtered;
	srv.filterByYearSRV(upperyear, filtered);
	printUI(filtered);
}

void Console::sortUI(bool(*compare)(const Film&, const Film&)) {
	auto sorted = srv.getAllSRV();
	srv.sortBySRV(compare, sorted);
	printUI(sorted);
}

void Console::printUI(const vector<Film>& films) {
	if (films.size() == 0) {
		throw RepoException("No results found!");
	}
	cout << "\n";
	for (const Film& film : films) {
		cout << std::left << " | " << std::setw(15) << film.getTitle() << " | " << std::setw(10) << film.getGenre() << " | " << std::setw(4) << film.getYear() << " | " << std::setw(13) << film.getActor() << "\n";
	}
}

void Console::statisticsUI() {
	vector<DTO> DTOs = srv.statistics();
	cout << "\n";
	for (const DTO& dto : DTOs) {
		cout << std::left << " | " << std::setw(10) << dto.getGenre() << " | " << std::setw(4) << dto.getCount() << "\n";
	}
}

//CART

void Console::addToCartUI() {
	string title;
	cout << "Input title: "; cin >> title;
	srvc.addToCartSV(title);
}

void Console::generateUI() {
	int number;
	cout << "Input the number of random films to be added: "; cin >> number;
	srvc.generate(number);
}

void Console::exportUI() {
	string filename;
	cout << "Input filename: "; cin >> filename;
	srvc.exportSV(filename);
}

void Console::run() {
	while (true) {
		cout << "\n   == Films database ==\n\n  1. Add\n  2. Remove\n  3. Edit\n  4. Print\n  5. Find\n  6. Filter by title\n  7. Filter by year\n  8. Sort by title\n  9. Sort by actor\n 10. Sort by year and genre\n 11. Statistics\n 12. Undo\n\n   == Your cart ==\n > You cart has " << srvc.getCart().size() << " film(s)!\n\n 13. Clear cart\n 14. Add to cart\n 15. Add to cart a number of random flims\n 16. Export your cart to a file \n 17. Undo cart\n\n  0. Exit\n\n Input: ";
		int cmd;
		checkInt(cmd);
		try {
			switch (cmd) {
			case 1:
				addUI();
				break;
			case 2:
				if (srv.getAllSRV().size() == 0) {
					throw RepoException("\nThere are no films in the database!");
				}
				removeUI();
				break;
			case 3:
				if (srv.getAllSRV().size() == 0) {
					throw RepoException("\nThere are no films in the database!");
				}
				editUI();
				break;
			case 4:
				if (srv.getAllSRV().size() == 0) {
					throw RepoException("\nThere are no films in the database!");
				}
				printUI(srv.getAllSRV());
				break;
			case 5:
				if (srv.getAllSRV().size() == 0) {
					throw RepoException("\nThere are no films in the database!");
				}
				findUI();
				break;
			case 6:
				if (srv.getAllSRV().size() == 0) {
					throw RepoException("\nThere are no films in the database!");
				}
				filterByTitleUI();
				break;
			case 7:
				if (srv.getAllSRV().size() == 0) {
					throw RepoException("\nThere are no films in the database!");
				}
				filterByYearUI();
				break;
			case 8:
				if (srv.getAllSRV().size() == 0) {
					throw RepoException("\nThere are no films in the database!");
				}
				sortUI([](const Film& f1, const Film& f2) { return f1.getTitle() < f2.getTitle(); });
				break;
			case 9:
				if (srv.getAllSRV().size() == 0) {
					throw RepoException("\nThere are no films in the database!");
				}
				sortUI([](const Film& f1, const Film& f2) { return f1.getActor() < f2.getActor(); });
				break;
			case 10:
				if (srv.getAllSRV().size() == 0) {
					throw RepoException("\nThere are no films in the database!");
				}
				sortUI(cmpYearAndGenre);
				break;
			case 11:
				if (srv.getAllSRV().size() == 0) {
					throw RepoException("\nThere are no films in the database!");
				}
				statisticsUI();
				break;
			case 12:
				srv.undo();
				break;
			case 13:
				if (srvc.getCart().size() == 0) {
					throw RepoException("\nThere are no films in the cart!");
				}
				srvc.clearCartSV();
				break;
			case 14:
				addToCartUI();
				break;
			case 15:
				generateUI();
				break;
			case 16:
				if (srvc.getCart().size() == 0) {
					throw RepoException("\nThere are no films in the cart!");
				}
				exportUI();
				break;
			case 17:
				srvc.undoCart();
				break;
			case 0:
				return;
			default:
				cout << "\n>> Invalid input!\n";
			}
		}
		catch (const RepoException& ex) {
			cout << ex << "\n";
		}
		catch (const ValidException& ex) {
			cout << ex << "\n";
		}
	}
}
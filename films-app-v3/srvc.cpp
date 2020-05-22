#include "srvc.h"
#include <random>
#include <algorithm>
#include <chrono>

#include <iostream>
#include <iomanip>

const vector<Film>& ServiceCart::getCart() const noexcept {
	return repoc.getCart();
}

void ServiceCart::clearCartSV() noexcept{
	undoActionsCart.push_back(std::make_unique<UndoClearCart>(repoc, getCart()));
	repoc.clearCart();
}

void ServiceCart::addToCartSV(const string& title) {
	repoc.addToCart(title);
}

void ServiceCart::generate(const int& number) {
	if (number <= 0) {
		throw RepoException("\nThe number must not be zero or negative!\n");
	}

	if (number > repo.getAllREPO().size()) {
		throw RepoException("\nThe number must not exceed the number of films!\n");
	}

	repoc.clearCart();
	vector<size_t> positions;
	for (size_t pos = 0; pos < number; pos++) {
		positions.push_back(pos);
	}

	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(positions.begin(), positions.end(), std::default_random_engine((unsigned)seed));

	for (auto const& i : positions) {
		std::cout << i << " ";
	}

	for (size_t pos = 0; pos < number; pos++) {
		repoc.add(repo.getAllREPO().at(positions.at(pos)));
	}
	std::cout << "\n";
	for (const Film& film : getCart()) {
		std::cout << std::left << " | " << std::setw(15) << film.getTitle() << " | " << std::setw(10) << film.getGenre() << " | " << std::setw(4) << film.getYear() << " | " << std::setw(13) << film.getActor() << "\n";
	}
}

void ServiceCart::exportSV(const string& filename) {
	std::ofstream out(filename);
	if (!out.is_open()) { throw RepoException("\nError open file!\n"); }
	for (const Film& film : repoc.getCart()) {
		out << film.getTitle() << "," << film.getGenre() << "," << film.getYear() << "," << film.getActor() << std::endl;
	}
	out.close();
}

void ServiceCart::undoCart() {
	if (undoActionsCart.empty()) {
		throw RepoException("\nThere is nothing to undo!\n"); }
	undoActionsCart.back()->doUndo();
	undoActionsCart.pop_back();
}

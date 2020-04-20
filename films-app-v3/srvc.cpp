#include "srvc.h"
#include <random>
#include <algorithm>

const vector<Film>& ServiceCart::getCart() const noexcept {
	return repoc.getCart();
}

void ServiceCart::clearCartSV() noexcept{
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
	auto seed = std::default_random_engine{};
	std::shuffle(positions.begin(), positions.end(), seed);

	for (size_t pos = 0; pos < number; pos++) {
		repoc.add(repo.getAllREPO().at(positions.at(pos)));
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

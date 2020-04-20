#include "repoc.h"

const vector<Film>& RepositoryCart::getCart() const noexcept {
	return cart;
}

void RepositoryCart::clearCart() noexcept{
	cart.clear();
}

void RepositoryCart::addToCart(const string& title) {
	vector<Film> list = repo.getAllREPO();
	auto found_film = std::find_if(list.begin(), list.end(), [&title](const Film& film) { return film.getTitle() == title; });
	if (found_film != list.end()) {
		auto not_found_cart = std::find(cart.begin(), cart.end(), *found_film);
		if (not_found_cart == cart.end()) {
			cart.push_back(*found_film);
			return;
		}
		throw RepoException("\nThe film is already in your cart!\n"); }
	throw RepoException("\nThe film does not exist in the database!\n"); }

void RepositoryCart::add(const Film& film) {
	cart.push_back(film);
}
#include "repoc.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <algorithm>
#include <fstream>

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

void RepositoryCart::generate(const int& number) {
	if (number <= 0) {
		throw RepoException("\nThe number must not be zero or negative!\n"); }

	if (number > repo.getAllREPO().size()) {
		throw RepoException("\nThe number must not exceed the number of films!\n"); }

	clearCart();
	vector<size_t> positions;
	for (size_t pos = 0; pos < number; pos++) {
		positions.push_back(pos);
	}
	//auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	auto seed = std::default_random_engine{};
	std::shuffle(positions.begin(), positions.end(), seed);
	
	for (size_t pos = 0; pos < number; pos++) {
		cart.push_back(repo.getAllREPO().at(positions.at(pos)));
	}
}

void RepositoryCart::exportR(const string& filename) {
	std::ofstream out(filename);
	if (!out.is_open()) { throw RepoException("\nError open file!\n"); }
	for (const Film& film : cart) {
		out << film.getTitle() << "," << film.getGenre() << "," << film.getYear() << "," << film.getActor() << std::endl;
	}
	out.close();
}

//std::mt19937 mt{ std::random_device{}() };
//std::uniform_int_distribution<> dist(0, repo.films.size() - 1);
//int random_pos = dist(mt);// numar aleator intre [0,size-1]
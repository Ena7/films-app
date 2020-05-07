#pragma once
#include "repo.h"

class RepositoryCart {
	vector<Film> cart;
	Repository& repo;

public:
	RepositoryCart(Repository& repo) noexcept: repo { repo } {}
	//nu permite copierea de obiecte Repository
	RepositoryCart(const RepositoryCart& nocopy) = delete;

	const vector<Film>& getCart() const noexcept;
	
	//sterge toate filmele din cos
	void clearCart() noexcept;

	//adauga un film in cos dupa titlu
	//exceptie daca: filmul nu exista in lista de filme sau filmul deja se afla in cos
	void addToCart(const string& title);

	//adauga un film in cos
	void add(const Film& film);
};
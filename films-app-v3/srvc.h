#pragma once
#include "repoc.h"
#include <fstream>
#include "undo.h"

class ServiceCart {
	RepositoryCart& repoc;
	Repository& repo;
	std::vector<std::unique_ptr<UndoAction>> undoActionsCart;

public:
	ServiceCart(RepositoryCart& repoc, Repository& repo) noexcept : repoc{ repoc }, repo{ repo } {}

	//nu permite copierea de obiecte ServiceCart
	ServiceCart(const ServiceCart& nocopy) = delete;

	const vector<Film>& getCart() const noexcept;
	
	//sterge toate filmele din cos
	void clearCartSV() noexcept;
	
	//adauga un film in cos dupa titlu
	//exceptie daca: filmul nu exista in lista de filme sau filmul deja se afla in cos
	void addToCartSV(const string& title);

	//alege aleatoriu un numar dat de filme si le adauga in cos
	//exceptie daca: numarul este negativ/nul sau depaseste numarul de filme din lista de filme
	void generate(const int& number);

	//scrie intr-un fisier dat toate filmele din cos
	//exceptie daca: eroare la deschidere fisier
	void exportSV(const string& filename);

	void undoCart();
};
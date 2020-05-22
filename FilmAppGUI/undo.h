#pragma once
#include "repo.h"
#include "repoc.h"

class UndoAction {
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() {};
};

class UndoAdd : public UndoAction {
	IRepo& repo;
	Film addedFilm;
public:
	UndoAdd(IRepo& repo, const Film& film) : repo{ repo }, addedFilm{ film } {}
	void doUndo() override {
		repo.removeREPO(addedFilm.getTitle(), addedFilm.getYear());
	}
};

class UndoRemove : public UndoAction {
	IRepo& repo;
	Film removedFilm;
public:
	UndoRemove(IRepo& repo, const Film& film) : repo{ repo }, removedFilm{ film } {}
	void doUndo() override {
		repo.addREPO(removedFilm);
	}
};

class UndoEdit : public UndoAction {
	IRepo& repo;
	Film editedFilm;
	string newtitle;
	int newyear;
public:
	UndoEdit(IRepo& repo, const Film& film, const string& newtitle, const int& newyear) : repo{ repo }, editedFilm{ film }, newtitle{ newtitle }, newyear{ newyear } {}
	void doUndo() override {
		repo.removeREPO(newtitle, newyear);
		repo.addREPO(editedFilm);
	}
};

class UndoClearCart : public UndoAction {
	RepositoryCart& repoc;
	vector<Film> deleted_cart;
public:
	UndoClearCart(RepositoryCart& repoc, vector<Film> deletedCart) : repoc{ repoc }, deleted_cart{ deletedCart } {}
	void doUndo() override {
		repoc.clearCart();
		for (const auto& film : deleted_cart) {
			repoc.addToCart(film.getTitle());
		}
	}
};
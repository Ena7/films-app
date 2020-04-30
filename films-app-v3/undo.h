#pragma once
#include "repo.h"

class UndoAction {
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() {};
};

class UndoAdd : public UndoAction {
	Repository& repo;
	Film addedFilm;
public:
	UndoAdd(Repository& repo, const Film& film) : repo{ repo }, addedFilm{ film } {}
	void doUndo() override {
		repo.removeREPO(addedFilm.getTitle(), addedFilm.getYear());
	}
};

class UndoRemove : public UndoAction {
	Repository& repo;
	Film removedFilm;
public:
	UndoRemove(Repository& repo, const Film& film) : repo{ repo }, removedFilm{ film } {}
	void doUndo() override {
		repo.addREPO(removedFilm);
	}
};

class UndoEdit : public UndoAction {
	Repository& repo;
	Film editedFilm;
	string newtitle;
	int newyear;
public:
	UndoEdit(Repository& repo, const Film& film, const string& newtitle, const int& newyear) : repo{ repo }, editedFilm{ film }, newtitle{ newtitle }, newyear{ newyear } {}
	void doUndo() override {
		repo.removeREPO(newtitle, newyear);
		repo.addREPO(editedFilm);
	}
};
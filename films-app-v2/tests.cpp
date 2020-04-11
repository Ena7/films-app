#include "tests.h"
#include "film.h"
#include "repo.h"
#include "srv.h"
#include <assert.h>
#include <exception>
#include <sstream>

void Test::test_addREPO() {
	Repository repo;
	assert(repo.getAllREPO().size() == 0);
	repo.addREPO({ "a", "a", 2000, "a" });
	assert(repo.getAllREPO().size() == 1);
	repo.addREPO({ "b", "b", 2001, "b" });
	assert(repo.getAllREPO().size() == 2);
	repo.addREPO({ "a", "a", 2002, "a" });
	assert(repo.getAllREPO().size() == 3);
	bool exceptionThrown = false;
	try {
		repo.addREPO({ "a", "a", 2000, "a" }); }
	catch (const RepoException& ex) {
		exceptionThrown = true;
		std::stringstream ss;
		ss << ex;
		assert(ss.str().find("exist") >= 0);
	}
	assert(exceptionThrown);
	assert(repo.getAllREPO().size() == 3);
}

void Test::test_removeREPO() {
	Repository repo;
	repo.addREPO({ "a", "a", 2000, "a" });
	repo.addREPO({ "b", "b", 2001, "b" });
	repo.addREPO({ "c", "c", 2002, "c" });
	assert(repo.getAllREPO().size() == 3);
	repo.removeREPO("c", 2002);
	assert(repo.getAllREPO().size() == 2);
	repo.removeREPO("a", 2000);
	assert(repo.getAllREPO().size() == 1);
	assert(repo.getAllREPO().at(0).getTitle() == "b");
	bool exceptionThrown = false;
	try {
		repo.removeREPO("no", 2002); }
	catch (RepoException&) {
		exceptionThrown = true;
	}
	assert(exceptionThrown);
	assert(repo.getAllREPO().size() == 1);
}

void Test::test_editREPO() {
	Repository repo;
	repo.addREPO({ "a", "a", 2000, "a" });
	repo.addREPO({ "b", "b", 2001, "b" });
	repo.addREPO({ "c", "c", 2001, "c" });
	repo.editREPO("b", "m", "n", 1901, "o");
	assert(repo.getAllREPO().size() == 3);
	assert(repo.getAllREPO().at(1).getTitle() == "m");
	assert(repo.getAllREPO().at(1).getGenre() == "n");
	assert(repo.getAllREPO().at(1).getYear() == 1901);
	assert(repo.getAllREPO().at(1).getActor() == "o");
	bool exceptionThrown = false;
	try {
		repo.editREPO("e", "s", "t", 1902, "u"); }
	catch (RepoException&) {
		exceptionThrown = true;
	}
	assert(exceptionThrown);
	assert(repo.getAllREPO().size() == 3);
}

void Test::test_findREPO() {
	Repository repo;
	const Film f1{ "a", "a", 2000, "a" };
	const Film f2{ "b", "b", 2001, "b" };
	const Film f3{ "b", "b", 2002, "b" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	LkdLst<Film> t;
	t.push_back(f2);
	t.push_back(f3);
	assert(repo.findREPO("b").at(0) == f2);
	assert(repo.findREPO("b").at(1) == f3);
	bool exceptionThrown = false;
	try {
		LkdLst<Film> _ = repo.findREPO("no"); }
	catch (RepoException&) {
		exceptionThrown = true;
	}
	assert(exceptionThrown);
}

void Test::test_addSRV() {
	Repository repo;
	Validator valid;
	Service srv{ repo, valid };
	assert(srv.getAllSRV().size() == 0);
	srv.addSRV("a", "a", 2000, "a");
	assert(srv.getAllSRV().size() == 1);
	srv.addSRV("b", "b", 2001, "b");
	assert(srv.getAllSRV().size() == 2);
	srv.addSRV("a", "a", 2002, "a");
	assert(srv.getAllSRV().size() == 3);
	bool exceptionThrown = false;
	try {
		srv.addSRV("a", "a", 2000, "a"); }
	catch (RepoException&) {
		exceptionThrown = true;
	}
	assert(exceptionThrown);
	assert(srv.getAllSRV().size() == 3);

	exceptionThrown = false;
	try {
		srv.addSRV("", "", -404, ""); }
	catch (const ValidException& ex) {
		exceptionThrown = true;
		std::stringstream ss;
		ss << ex;
		assert(ss.str().find("blank") >= 0);
	}
	assert(exceptionThrown);
	assert(srv.getAllSRV().size() == 3);
}

void Test::test_removeSRV() {
	Repository repo;
	Validator valid;
	Service srv{ repo, valid };
	srv.addSRV("a", "a", 2000, "a");
	srv.addSRV("b", "b", 2001, "b");
	srv.addSRV("c", "c", 2002, "c");
	assert(srv.getAllSRV().size() == 3);
	srv.removeSRV("b", 2001);
	assert(srv.getAllSRV().size() == 2);
	srv.removeSRV("a", 2000);
	assert(srv.getAllSRV().size() == 1);
	assert(srv.getAllSRV().at(0).getTitle() == "c");
	bool exceptionThrown = false;
	try {
		srv.removeSRV("no", 2002); }
	catch (RepoException&) {
		exceptionThrown = true;
	}
	assert(exceptionThrown);
	assert(srv.getAllSRV().size() == 1);
}

void Test::test_editSRV() {
	Repository repo;
	Validator valid;
	Service srv{ repo, valid };
	srv.addSRV("a", "a", 2000, "a");
	srv.addSRV("b", "b", 2001, "b");
	srv.addSRV("c", "c", 2002, "c");
	srv.editSRV("b", "m", "n", 1901, "o");
	assert(srv.getAllSRV().size() == 3);
	assert(srv.getAllSRV().at(1).getTitle() == "m");
	assert(srv.getAllSRV().at(1).getGenre() == "n");
	assert(srv.getAllSRV().at(1).getYear() == 1901);
	assert(srv.getAllSRV().at(1).getActor() == "o");
	bool exceptionThrown = false;
	try {
		srv.editSRV("e", "s", "t", 1902, "u"); }
	catch (RepoException&) {
		exceptionThrown = true;
	}
	assert(exceptionThrown);
	assert(srv.getAllSRV().size() == 3);
}

void Test::test_findSRV() {
	Repository repo;
	Validator valid;
	Service const srv{ repo, valid };
	const Film f1{ "a", "a", 2000, "a" };
	const Film f2{ "b", "b", 2001, "b" };
	const Film f3{ "b", "b", 2002, "b" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	LkdLst<Film> t;
	t.push_back(f2);
	t.push_back(f3);
	assert(srv.findSRV("b").at(0) == f2);
	assert(srv.findSRV("b").at(1) == f3);
	bool exceptionThrown = false;
	try {
		LkdLst<Film> _ = srv.findSRV("no"); }
	catch (RepoException&) {
		exceptionThrown = true;
	}
	assert(exceptionThrown);
}

void Test::test_filterByTitleSRV() {
	Repository repo;
	Validator valid;
	Service srv{ repo, valid };
	const Film f1 { "baa", "b", 2000, "b" };
	const Film f2 { "cdd", "c", 2001, "c" };
	const Film f3 { "bcc", "a", 2002, "a" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	LkdLst<Film> filter1;
	srv.filterByTitleSRV("b", filter1);
	assert(filter1.size() == 2);
	assert(filter1.at(0) == f1);
	assert(filter1.at(1) == f3);
	LkdLst<Film> filter2;
	srv.filterByTitleSRV("d", filter2);
	assert(filter2.size() == 0);
}

void Test::test_filterByYearSRV() {
	Repository repo;
	Validator valid;
	Service srv{ repo, valid };
	const Film f1 { "b", "b", 2002, "b" };
	const Film f2 { "c", "c", 2001, "c" };
	const Film f3 { "a", "a", 2000, "a" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	LkdLst<Film> filter1;
	srv.filterByYearSRV(2001, filter1);
	assert(filter1.size() == 2);
	assert(filter1.at(0) == f2);
	assert(filter1.at(1) == f3);
	LkdLst<Film> filter2;
	srv.filterByYearSRV(1999, filter2);
	assert(filter2.size() == 0);
}

void Test::test_sortByTitleSRV() {
	Repository repo;
	Validator valid;
	Service srv{ repo, valid };
	const Film f1 { "b", "b", 2002, "b" };
	const Film f2 { "c", "c", 2001, "c" };
	const Film f3 { "a", "a", 2000, "a" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	LkdLst<Film> filter = srv.sortBySRV([](const Film& f1, const Film& f2) { return f1.getTitle() < f2.getTitle(); });
	assert(filter.size() == 3);
	assert(filter.at(0) == f3);
	assert(filter.at(1) == f1);
	assert(filter.at(2) == f2);
}

void Test::test_sortByActorSRV() {
	Repository repo;
	Validator valid;
	Service srv{ repo, valid };
	const Film f1 { "b", "b", 2002, "m" };
	const Film f2 { "c", "c", 2001, "o" };
	const Film f3 { "a", "a", 2000, "n" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	LkdLst<Film> filter = srv.sortBySRV([](const Film& f1, const Film& f2) { return f1.getActor() < f2.getActor(); });
	assert(filter.size() == 3);
	assert(filter.at(0) == f1);
	assert(filter.at(1) == f3);
	assert(filter.at(2) == f2);
}

void Test::test_sortByYearAndGenreSRV() {
	Repository repo;
	Validator valid;
	Service srv{ repo, valid };
	const Film f1 { "b", "c", 2001, "m" };
	const Film f2 { "c", "b", 2001, "o" };
	const Film f3 { "a", "a", 2000, "n" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	LkdLst<Film> filter = srv.sortBySRV(cmpYearAndGenre);
	assert(filter.size() == 3);
	assert(filter.at(0) == f3);
	assert(filter.at(1) == f2);
	assert(filter.at(2) == f1);
}

void Test::test_statistics() {
	Repository repo;
	Validator valid;
	Service srv{ repo, valid };
	const Film f1{ "AA", "gen1", 2000, "DD" };
	const Film f2{ "BB", "gen2", 1990, "EE" };
	const Film f3{ "CC", "gen1", 2010, "FF" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	vector<DTO> stats = srv.statistics();
	assert(stats.size() == 2);
	assert(stats.at(0).getGenre() == "gen1");
	assert(stats.at(0).getCount() == 2);
	assert(stats.at(1).getGenre() == "gen2");
	assert(stats.at(1).getCount() == 1);
}

void Test::test_LL() {
	LkdLst<Film> list;
	assert(list.size() == 0);
	const Film f1{ "AA", "gen1", 2000, "DD" };
	const Film f2{ "BB", "gen2", 1990, "EE" };
	const Film f3{ "CC", "gen1", 2010, "FF" };
	list.push_back(f1); 
	assert(list.size() == 1);
	list.push_back(f2);
	assert(list.size() == 2);
	assert(list.at(0) == f1);
	assert(list.at(1) == f2);
	list.push_back(f3);
	assert(list.size() == 3);
	assert(list.at(2) == f3);
	list.erase(1); //sterg f2
	assert(list.size() == 2);
	assert(list.at(0) == f1);
	assert(list.at(1) == f3);
}

void Test::testAll() {
	test_addREPO();
	test_removeREPO();
	test_editREPO();
	test_findREPO();
	test_addSRV();
	test_removeSRV();
	test_editSRV();
	test_findSRV();
	test_filterByTitleSRV();
	test_filterByYearSRV();
	test_sortByTitleSRV();
	test_sortByActorSRV();
	test_sortByYearAndGenreSRV();
	test_statistics();
	test_LL();
}
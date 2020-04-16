#include "tests.h"
#include "film.h"
#include "repo.h"
#include "repoc.h"
#include "srv.h"
#include "srvc.h"
#include <assert.h>
#include <exception>
#include <sstream>

void Test::test_addREPO() {
	Repository repo;
	Film f1 { "a", "a", 2000, "a" };
	Film f2 { "b", "b", 2001, "b" };
	Film f3 { "b", "b", 2002, "b" };
	Film fno{ "a", "a", 2000, "a" };
	assert(repo.getAllREPO().size() == 0);
	repo.addREPO(f1);
	assert(repo.getAllREPO().size() == 1);
	repo.addREPO(f2);
	assert(repo.getAllREPO().size() == 2);
	repo.addREPO(f3);
	assert(repo.getAllREPO().size() == 3);
	bool exceptionThrown = false;
	try {
		repo.addREPO(fno); }
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
	Film f1{ "a", "a", 2000, "a" };
	Film f2{ "b", "b", 2001, "b" };
	Film f3{ "b", "b", 2002, "b" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	assert(repo.getAllREPO().size() == 3);
	repo.removeREPO("b", 2001);
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
	Film f1{ "a", "a", 2000, "a" };
	Film f2{ "b", "b", 2001, "b" };
	Film f3{ "b", "b", 2002, "b" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
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
	Film f1{ "a", "a", 2000, "a" };
	Film f2{ "b", "b", 2001, "b" };
	Film f3{ "b", "b", 2002, "b" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	assert(repo.findREPO("b", 2002) == f3);
	bool exceptionThrown = false;
	try {
		auto _ = repo.findREPO("no", 2002); }
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
	Film f1{ "a", "a", 2000, "a" };
	Film f2{ "b", "b", 2001, "b" };
	Film f3{ "b", "b", 2002, "b" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	assert(srv.findSRV("b", 2002) == f3);
	bool exceptionThrown = false;
	try {
		auto _ = srv.findSRV("no", 2000); }
	catch (RepoException&) {
		exceptionThrown = true;
	}
	assert(exceptionThrown);
}

void Test::test_filterByTitleSRV() {
	Repository repo;
	Validator valid;
	Service srv{ repo, valid };
	Film f1 { "baa", "b", 2000, "b" };
	Film f2 { "cdd", "c", 2001, "c" };
	Film f3 { "bcc", "a", 2002, "a" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	vector<Film> filter1;
	srv.filterByTitleSRV("b", filter1);
	assert(filter1.size() == 2);
	assert(filter1.at(0) == f1);
	assert(filter1.at(1) == f3);
	vector<Film> filter2;
	srv.filterByTitleSRV("d", filter2);
	assert(filter2.size() == 0);
}

void Test::test_filterByYearSRV() {
	Repository repo;
	Validator valid;
	Service srv{ repo, valid };
	Film f1 { "b", "b", 2002, "b" };
	Film f2 { "c", "c", 2001, "c" };
	Film f3 { "a", "a", 2000, "a" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	vector<Film> filter1;
	srv.filterByYearSRV(2001, filter1);
	assert(filter1.size() == 2);
	assert(filter1.at(0) == f2);
	assert(filter1.at(1) == f3);
	vector<Film> filter2;
	srv.filterByYearSRV(1999, filter2);
	assert(filter2.size() == 0);
}

void Test::test_sortByTitleSRV() {
	Repository repo;
	Validator valid;
	Service srv{ repo, valid };
	Film f1 { "b", "b", 2002, "b" };
	Film f2 { "c", "c", 2001, "c" };
	Film f3 { "a", "a", 2000, "a" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	auto sorted = srv.getAllSRV();
	srv.sortBySRV([](const Film& f1, const Film& f2) { return f1.getTitle() < f2.getTitle(); }, sorted);
	assert(sorted.size() == 3);
	assert(sorted.at(0) == f3);
	assert(sorted.at(1) == f1);
	assert(sorted.at(2) == f2);
}

void Test::test_sortByActorSRV() {
	Repository repo;
	Validator valid;
	Service srv{ repo, valid };
	Film f1 { "b", "b", 2002, "m" };
	Film f2 { "c", "c", 2001, "o" };
	Film f3 { "a", "a", 2000, "n" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	auto sorted = srv.getAllSRV();
	srv.sortBySRV([](const Film& f1, const Film& f2) { return f1.getActor() < f2.getActor(); }, sorted);
	assert(sorted.size() == 3);
	assert(sorted.at(0) == f1);
	assert(sorted.at(1) == f3);
	assert(sorted.at(2) == f2);
}

void Test::test_sortByYearAndGenreSRV() {
	Repository repo;
	Validator valid;
	Service srv{ repo, valid };
	Film f1 { "b", "c", 2001, "m" };
	Film f2 { "c", "b", 2001, "o" };
	Film f3 { "a", "a", 2000, "n" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	auto sorted = srv.getAllSRV();
	srv.sortBySRV(cmpYearAndGenre, sorted);
	assert(sorted.size() == 3);
	assert(sorted.at(0) == f3);
	assert(sorted.at(1) == f2);
	assert(sorted.at(2) == f1);
}

void Test::test_statistics() {
	Repository repo;
	Validator valid;
	Service srv{ repo, valid };
	Film f1{ "AA", "gen1", 2000, "DD" };
	Film f2{ "BB", "gen2", 1990, "EE" };
	Film f3{ "CC", "gen1", 2010, "FF" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	vector<DTO> stats = srv.statistics();
	assert(stats.size() == 2);
	assert(stats.at(0).getGenre() == "gen1");
	assert(stats.at(0).getCount() == 2);
	assert(stats.at(1).getGenre() == "gen2");
	assert(stats.at(1).getCount() == 1);
}

//CART

void Test::test_addToCart() {
	Repository repo;
	RepositoryCart repoc{ repo };
	ServiceCart srvc{ repoc };
	Film f1{ "b", "c", 2001, "m" };
	Film f2{ "c", "b", 2001, "o" };
	Film f3{ "a", "a", 2000, "n" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	assert(repoc.getCart().size() == 0);
	srvc.addToCartSV("a");
	assert(repoc.getCart().size() == 1);
	srvc.addToCartSV("b");
	assert(repoc.getCart().size() == 2);
	bool exceptionThrown = false;
	try {
		//does not exist
		srvc.addToCartSV("n");
	}
	catch (RepoException&) {
		exceptionThrown = true;
	}
	assert(exceptionThrown);

	assert(repoc.getCart().size() == 2);
	exceptionThrown = false;
	try {
		//already added in the cart
		srvc.addToCartSV("a");
	}
	catch (RepoException&) {
		exceptionThrown = true;
	}
	assert(exceptionThrown);

	assert(repoc.getCart().size() == 2);
	srvc.clearCartSV();
	assert(repoc.getCart().size() == 0);
}

void Test::test_generate() {
	Repository repo;
	RepositoryCart repoc{ repo };
	ServiceCart srvc{ repoc };
	Film f1{ "b", "c", 2001, "m" };
	Film f2{ "c", "b", 2001, "o" };
	Film f3{ "a", "a", 2000, "n" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	bool exceptionThrown = false;
	try {
		//negative or zero value
		srvc.generateSV(-1);
	}
	catch (RepoException&) {
		exceptionThrown = true;
	}
	assert(exceptionThrown);

	assert(repoc.getCart().size() == 0);
	exceptionThrown = false;
	try {
		//exceeds total number
		srvc.generateSV(4);
	}
	catch (RepoException&) {
		exceptionThrown = true;
	}
	assert(exceptionThrown);

	assert(repoc.getCart().size() == 0);
	srvc.generateSV(3);
	assert(repoc.getCart().size() == 3);
}

void Test::test_export() {
	Repository repo;
	RepositoryCart repoc{ repo };
	ServiceCart srvc{ repoc };
	Film f1{ "b", "c", 2001, "m" };
	Film f2{ "c", "b", 2001, "o" };
	Film f3{ "a", "a", 2000, "n" };
	repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3);
	assert(repoc.getCart().size() == 0);
	srvc.addToCartSV("a");
	srvc.addToCartSV("b");
	assert(repoc.getCart().size() == 2);
	srvc.exportSV("test.csv");
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
	//CART
	test_addToCart();
	test_generate();
	test_export();
}
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "tests.h"
#include "repo.h"
#include "valid.h"
#include "srv.h"
#include "console.h"

void mainApp() {
	Test test;
	test.testAll();

	//Repository repo;
	FileRepository repo{ "films.csv" };
	RepositoryCart repoc{ repo };

	Validator valid;

	Service srv{ repo, valid };
	ServiceCart srvc{ repoc, repo };

	Console ui{ srv, srvc };

	//Film f1 = { "avatar", "SF", 2009, "worthington" };
	//Film f2 = { "interstellar", "SF", 2014, "mcconaughey" };
	//Film f3 = { "fury", "War", 2014, "pitt" };
	//Film f4 = { "2012", "Action", 2009, "cusack" };
	//Film f5 = { "aquaman", "Action", 2018, "momoa" };
	//Film f6 = { "life of pi", "Drama", 2012, "sharma" };
	//repo.addREPO(f1); repo.addREPO(f2); repo.addREPO(f3); repo.addREPO(f4); repo.addREPO(f5); repo.addREPO(f6);

	ui.run();
}

int main() {

	mainApp();

	_CrtDumpMemoryLeaks();
	return 0;
}
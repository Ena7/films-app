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

	Repository repo;
	Validator valid;
	Service srv{ repo, valid };
	Console ui{ srv };

	repo.addREPO({ "avatar", "SF", 2009, "worthington" });
	repo.addREPO({ "fury", "War", 2014, "pitt" });
	repo.addREPO({ "interstellar", "SF", 2014, "mcconaughey" });
	repo.addREPO({ "2012", "Action", 2009, "cusack" });
	repo.addREPO({ "aquaman", "Action", 2018, "momoa" });
	repo.addREPO({ "avatar", "SF", 2020, "tba" });
	repo.addREPO({ "life of pi", "Drama", 2012, "sharma" });

	ui.run();
}

int main() {

	mainApp();

	_CrtDumpMemoryLeaks();
	return 0;
}
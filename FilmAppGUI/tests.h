#pragma once

class Test {
	void test_addREPO();
	void test_removeREPO();
	void test_editREPO();
	void test_findREPO();
	void test_addSRV();
	void test_removeSRV();
	void test_editSRV();
	void test_findSRV();
	void test_filterByTitleSRV();
	void test_filterByYearSRV();
	void test_sortByTitleSRV();
	void test_sortByActorSRV();
	void test_sortByYearAndGenreSRV();
	void test_statistics();
	void test_undo();
	//CART
	void test_addToCart();
	void test_generate();
	void test_export();
	void test_undoCart();
	//FILE
	void test_file_addREPO();
	void test_file_removeREPO();
	void test_file_editREPO();

public:
	void testAll();
};


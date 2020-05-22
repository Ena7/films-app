#pragma once
#include "srvc.h"
#include <qwidget.h>
#include <qlistwidget.h>
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qformlayout.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qmessagebox.h>

class CartGUI : public QWidget {
private:
	ServiceCart& srvc;

	QListWidget* qlstcart;
	QFormLayout* fLtT;
	QLineEdit* txtTitle;
	QLabel* currentSelectedFilm;

	QVBoxLayout* mainL;

	QHBoxLayout* generateL;
	QFormLayout* generateF;
	QLineEdit* txtGenerate;
	QPushButton* btnGenerate;

	QHBoxLayout* exportL;
	QFormLayout* exportF;
	QLineEdit* txtExport;
	QPushButton* btnExport;

	QPushButton* btnClear;
	QPushButton* btnAddCart;
	QPushButton* btnUndoCart;

	void initGUI();
	void loadList(QListWidget*, vector<Film> films);
	void connectSignals();

public:
	CartGUI(ServiceCart& srvc) : srvc{ srvc } {
		initGUI();
		loadList(qlstcart, srvc.getCart());
		connectSignals();
	}
	void addCartGUI();
	void clearGUI();
	void generateGUI();
	void exportGUI();
	void undoCartGUI();
};
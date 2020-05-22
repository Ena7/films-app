#pragma once
#include <qwidget.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qformlayout.h>
#include <qlistwidget.h>
#include <qlabel.h>
#include <QMessageBox>
#include <QBrush>
#include "srv.h"
#include "srvc.h"
#include "guicart.h"
#include <string>

class GUI : public QWidget {
private:
	Service& srv;
	ServiceCart& srvc;

	//layouts
	QHBoxLayout* MainLayout;
	QVBoxLayout* Layout1;
	QFormLayout* formLayout;
	QHBoxLayout* ButtonLayout;
	QHBoxLayout* Button2Layout;

	//current selected film details
	QString selectedFilmTitle;
	QString selectedFilmYear;

	//tabs
	QTabWidget* qtab;

	QWidget* q1;
	QGridLayout* qtabgrid1;
	QListWidget* qlst;

	QWidget* q2;
	QGridLayout* qtabgrid2;
	QListWidget* qlst2;

	QWidget* sTY;
	QHBoxLayout* sTYLay;
	QPushButton* btnSortbyTitle;
	QPushButton* btnSortbyActor;

	QPushButton* btnSortbyYearAndGenre;
	QPushButton* btnStats;

	QWidget* fbT;
	QHBoxLayout* fbTLay;
	QFormLayout* fbTForm;
	QLineEdit* txtfbT;
	QPushButton* btnFilterbyTitle;

	QWidget* fbY;
	QHBoxLayout* fbYLay;
	QFormLayout* fbYForm;
	QLineEdit* txtfbY;
	QPushButton* btnFilterbyYear;

	//text editor
	QLabel* currentSelectedFilm;
	QLineEdit* txtTitle;
	QLineEdit* txtGenre;
	QLineEdit* txtYear;
	QLineEdit* txtActor;

	//repo buttons
	QPushButton* btnAdd;
	QPushButton* btnDelete;
	QPushButton* btnEdit;
	QPushButton* btnFind;

	QPushButton* btnUndo;
	QPushButton* btnOpenCart;

	QVBoxLayout* btnsgenL;

	void initGUI();
	void loadList(QListWidget*, vector<Film> films);
	void connectSignals();
	void add_buttons(vector<Film> films);
	void clearLayout(QLayout* layout);

public:
	GUI(Service& srv, ServiceCart& srvc) : srv{ srv }, srvc{ srvc } {
		initGUI();
		connectSignals();
		loadList(qlst, srv.getAllSRV());
		loadList(qlst2, srv.getAllSRV());
		add_buttons(srv.getAllSRV());
	}
	void addGUI();
	void removeGUI();
	void editGUI();
	void findGUI();
	void filterByTitleGUI();
	void filterByYearGUI();
	void sortByGUI(bool(*compare)(const Film&, const Film&));
	void statsGUI();
	void undoGUI();
};




#pragma once
#include <qwidget.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qformlayout.h>
#include <qlistwidget.h>
#include <qlabel.h>
#include <QMessageBox>
#include "srv.h"
#include "srvc.h"
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

	QPushButton* btnSortbyTitle;
	QPushButton* btnSortbyActor;
	QPushButton* btnSortbyYearAndGenre;
	QPushButton* btnFilterbyTitle;
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

	void initGUI();
	void loadList(QListWidget*, vector<Film> films);
	void connectSignals();

public:
	GUI(Service& srv, ServiceCart& srvc) : srv{ srv }, srvc{ srvc } {
		initGUI();
		connectSignals();
		loadList(qlst, srv.getAllSRV());
		loadList(qlst2, srv.getAllSRV());
	}
	void addGUI();
	void removeGUI();
	void editGUI();
	void sortByGUI(bool(*compare)(const Film&, const Film&));
};




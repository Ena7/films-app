#include "gui.h"

void GUI::initGUI() {

	selectedFilmTitle = "";
	selectedFilmYear = "";

	MainLayout = new QHBoxLayout;
	setLayout(MainLayout);

	qtab = new QTabWidget;

	//tab1
	q1 = new QWidget;
	qlst = new QListWidget;
	qtabgrid1 = new QGridLayout;
	q1->setLayout(qtabgrid1);
	qtabgrid1->addWidget(qlst);
	btnFind = new QPushButton{ "&Find" };
	qtabgrid1->addWidget(btnFind);

	//tab2
	q2 = new QWidget;
	qlst2 = new QListWidget;
	qtabgrid2 = new QGridLayout;
	q2->setLayout(qtabgrid2);
	qtabgrid2->addWidget(qlst2);

	//buttons for tab2
	sTY = new QWidget;
	sTYLay = new QHBoxLayout;
	sTY->setLayout(sTYLay);
	btnSortbyTitle = new QPushButton{ "&Sort by title" };
	sTYLay->addWidget(btnSortbyTitle);
	btnSortbyActor = new QPushButton{ "&Sort by actor" };
	sTYLay->addWidget(btnSortbyActor);
	qtabgrid2->addWidget(sTY);
	
	btnSortbyYearAndGenre = new QPushButton{ "&Sort by year and genre" };
	qtabgrid2->addWidget(btnSortbyYearAndGenre);
	btnStats = new QPushButton{ "&Genre stats" };
	qtabgrid2->addWidget(btnStats);

	fbT = new QWidget;
	fbTLay = new QHBoxLayout;
	fbTForm = new QFormLayout;
	txtfbT = new QLineEdit;
	fbT->setLayout(fbTLay);
	btnFilterbyTitle = new QPushButton{ "&Filter by title" };
	fbTForm->addRow("Letter", txtfbT);
	fbTLay->addWidget(btnFilterbyTitle);
	fbTLay->addLayout(fbTForm);
	qtabgrid2->addWidget(fbT);

	fbY = new QWidget;
	fbYLay = new QHBoxLayout;
	fbYForm = new QFormLayout;
	txtfbY = new QLineEdit;
	fbY->setLayout(fbYLay);
	btnFilterbyYear = new QPushButton{ "&Filter by year" };
	fbYForm->addRow("Year  ", txtfbY);
	fbYLay->addWidget(btnFilterbyYear);
	fbYLay->addLayout(fbYForm);
	qtabgrid2->addWidget(fbY);

	qtab->addTab(q1, "Films");
	qtab->addTab(q2, "Sort / Filter");

	MainLayout->addWidget(qtab);

	//layout1
	Layout1 = new QVBoxLayout;

	//text editors
	formLayout = new QFormLayout;
	currentSelectedFilm = new QLabel{ "Not selected" };
	formLayout->addRow("Selected film:", currentSelectedFilm);
	txtTitle = new QLineEdit;
	formLayout->addRow("Title", txtTitle);
	txtGenre = new QLineEdit;
	formLayout->addRow("Genre", txtGenre);
	txtYear = new QLineEdit;
	formLayout->addRow("Year", txtYear);
	txtActor = new QLineEdit;
	formLayout->addRow("Actor", txtActor);
	Layout1->addLayout(formLayout);

	//repo buttons
	ButtonLayout = new QHBoxLayout;
	btnAdd = new QPushButton{ "&Add" };
	ButtonLayout->addWidget(btnAdd);
	btnDelete = new QPushButton{ "&Delete" };
	ButtonLayout->addWidget(btnDelete);
	btnEdit = new QPushButton{ "&Edit" };
	ButtonLayout->addWidget(btnEdit);
	Layout1->addLayout(ButtonLayout);

	Button2Layout = new QHBoxLayout;
	btnUndo = new QPushButton{ "&Undo" };
	Button2Layout->addWidget(btnUndo);
	btnOpenCart = new QPushButton{ "&OPEN CART" };
	Button2Layout->addWidget(btnOpenCart);
	Layout1->addLayout(Button2Layout);

	MainLayout->addLayout(Layout1);

	btnsgenL = new QVBoxLayout;
	MainLayout->addLayout(btnsgenL);

}

void GUI::loadList(QListWidget* lst, vector<Film> films) {
	lst->clear();
	for (const auto& film : films) {
		auto item = new QListWidgetItem(QString::fromStdString(film.getTitle()), lst);
		item->setData(Qt::UserRole, film.getYear());
	}
}

void GUI::connectSignals() {
	QObject::connect(qlst, &QListWidget::itemSelectionChanged, [&]() {
		if (qlst->selectedItems().isEmpty()) {
			txtTitle->setText("");
			txtGenre->setText("");
			txtYear->setText("");
			txtActor->setText("");
			return;
		}
		QListWidgetItem* selectedItem = qlst->selectedItems().at(0);
		auto title = selectedItem->text();
		auto year = selectedItem->data(Qt::UserRole).toString();
		selectedFilmTitle = title;
		selectedFilmYear = year;
		currentSelectedFilm->setText(title + " - " + year);
		txtTitle->setText(title);
		txtYear->setText(year);
		auto film = srv.findSRV(title.toStdString(), year.toInt());
		txtGenre->setText(QString::fromStdString(film.getGenre()));
		txtActor->setText(QString::fromStdString(film.getActor()));
	});

	QObject::connect(qlst2, &QListWidget::itemSelectionChanged, [&]() {
		if (qlst2->selectedItems().isEmpty()) {
			txtTitle->setText("");
			txtGenre->setText("");
			txtYear->setText("");
			txtActor->setText("");
			return;
		}
		QListWidgetItem* selectedItem = qlst2->selectedItems().at(0);
		auto title = selectedItem->text();
		auto year = selectedItem->data(Qt::UserRole).toString();
		if (year == 0) { return; }
		selectedFilmTitle = title;
		selectedFilmYear = year;
		currentSelectedFilm->setText(title + " - " + year);
		txtTitle->setText(title);
		txtYear->setText(year);
		auto film = srv.findSRV(title.toStdString(), year.toInt());
		txtGenre->setText(QString::fromStdString(film.getGenre()));
		txtActor->setText(QString::fromStdString(film.getActor()));
	});

	QObject::connect(btnAdd, &QPushButton::clicked, [&]() { addGUI(); });
	QObject::connect(btnDelete, &QPushButton::clicked, [&]() { removeGUI(); });
	QObject::connect(btnEdit, &QPushButton::clicked, [&]() { editGUI(); });
	QObject::connect(btnFind, &QPushButton::clicked, [&]() { findGUI(); });

	QObject::connect(btnSortbyTitle, &QPushButton::clicked, [&]() { sortByGUI([](const Film& f1, const Film& f2) { return f1.getTitle() < f2.getTitle(); }); });
	QObject::connect(btnSortbyActor, &QPushButton::clicked, [&]() { sortByGUI([](const Film& f1, const Film& f2) { return f1.getActor() < f2.getActor(); }); });
	QObject::connect(btnSortbyYearAndGenre, &QPushButton::clicked, [&]() { sortByGUI(cmpYearAndGenre); });
	QObject::connect(btnStats, &QPushButton::clicked, [&]() { statsGUI(); });

	QObject::connect(btnFilterbyTitle, &QPushButton::clicked, [&]() { filterByTitleGUI(); });
	QObject::connect(btnFilterbyYear, &QPushButton::clicked, [&]() { filterByYearGUI(); });
	
	QObject::connect(btnUndo, &QPushButton::clicked, [&]() { undoGUI(); });
	QObject::connect(btnOpenCart, &QPushButton::clicked, [&]() { 
		auto cartGUI = new CartGUI{ srvc };
		cartGUI->show();
	});
}

void GUI::clearLayout(QLayout* layout) {
	QLayoutItem* item;
	while (item = layout->takeAt(0)) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}
}

void GUI::add_buttons(vector<Film> films) {
	clearLayout(btnsgenL);
	for (const auto& film : films) {
		auto btn = new QPushButton{ QString::fromStdString(film.getTitle()) };
		btnsgenL->addWidget(btn);
		QObject::connect(btn, &QPushButton::clicked, [this, btn, film]() {
			txtTitle->setText(QString::fromStdString(film.getTitle()));
			txtYear->setText(QString::number(film.getYear()));
			removeGUI();
			txtTitle->setText("");
			txtGenre->setText("");
			txtYear->setText("");
			txtActor->setText("");
		});
	}
}

void GUI::addGUI() {
	try {
		srv.addSRV(txtTitle->text().toStdString(), txtGenre->text().toStdString(), txtYear->text().toInt(), txtActor->text().toStdString());
		loadList(qlst, srv.getAllSRV());
		loadList(qlst2, srv.getAllSRV());
		add_buttons(srv.getAllSRV());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Exception!", QString::fromStdString(ex.getEx()));
	}
	catch (ValidException& ex) {
		string allerr;
		for (const auto& msg : ex.getEx()) {
			allerr += msg + "\n";
		}
		QMessageBox::warning(this, "Exception!", QString::fromStdString(allerr));
	}
}

void GUI::removeGUI() {
	try {
		srv.removeSRV(txtTitle->text().toStdString(), txtYear->text().toInt());
		loadList(qlst, srv.getAllSRV());
		loadList(qlst2, srv.getAllSRV());
		add_buttons(srv.getAllSRV());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Exception!", QString::fromStdString(ex.getEx()));
	}
}

void GUI::editGUI() {
	try {
		srv.editSRV(selectedFilmTitle.toStdString(), selectedFilmYear.toInt(), txtTitle->text().toStdString(), txtGenre->text().toStdString(), txtYear->text().toInt(), txtActor->text().toStdString());
		loadList(qlst, srv.getAllSRV());
		loadList(qlst2, srv.getAllSRV());
		add_buttons(srv.getAllSRV());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Exception!", QString::fromStdString(ex.getEx()));
	}
	catch (ValidException& ex) {
		string allerr;
		for (const auto& msg : ex.getEx()) {
			allerr += msg + "\n";
		}
		QMessageBox::warning(this, "Exception!", QString::fromStdString(allerr));
	}
}

void GUI::findGUI() {
	try {
		auto foundFilm = srv.findSRV(txtTitle->text().toStdString(), txtYear->text().toInt());
		qlst->clear();
		for (const auto& film : srv.getAllSRV()) {
			auto item = new QListWidgetItem(QString::fromStdString(film.getTitle()), qlst);
			item->setData(Qt::UserRole, film.getYear());
			if (foundFilm.getTitle() == film.getTitle() && foundFilm.getYear() == film.getYear()) {
				item->setBackground(QBrush{ Qt::green, Qt::Dense5Pattern });
			}
		}
		loadList(qlst2, srv.getAllSRV());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Exception!", QString::fromStdString(ex.getEx()));
	}
}

void GUI::filterByTitleGUI() {
	try {
		if (txtfbT->text().toStdString().size() != 1) {
			throw RepoException("Input must be a letter!");
		}
		vector<Film> filtered;
		srv.filterByTitleSRV(txtfbT->text().toStdString(), filtered);
		loadList(qlst2, filtered);
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Exception!", QString::fromStdString(ex.getEx()));
	}
}

void GUI::filterByYearGUI() {
	try {
		if (txtfbY->text().toInt() == 0) {
			throw RepoException("Invalid year!");
		}
		vector<Film> filtered;
		srv.filterByYearSRV(txtfbY->text().toInt(), filtered);
		loadList(qlst2, filtered);
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Exception!", QString::fromStdString(ex.getEx()));
	}
}

void GUI::sortByGUI(bool(*compare)(const Film&, const Film&)) {
	try {
		if (srv.getAllSRV().size() == 0) {
			throw RepoException("\nThere are no films in the database!");
		}
		auto sorted = srv.getAllSRV();
		srv.sortBySRV(compare, sorted);
		loadList(qlst2, sorted);
		add_buttons(sorted);
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Exception!", QString::fromStdString(ex.getEx()));
	}
}

void GUI::statsGUI() {
	try {
		if (srv.getAllSRV().size() == 0) {
			throw RepoException("\nThere are no films in the database!");
		}
		qlst2->clear();
		for (const auto& dto : srv.statistics()) {
			qlst2->addItem(new QListWidgetItem(QString::fromStdString(dto.getGenre()) + " - " + QString::number(dto.getCount())));
		}
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Exception!", QString::fromStdString(ex.getEx()));
	}
}

void GUI::undoGUI() {
	try {
		srv.undo();
		loadList(qlst, srv.getAllSRV());
		loadList(qlst2, srv.getAllSRV());
		add_buttons(srv.getAllSRV());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Exception!", QString::fromStdString(ex.getEx()));
	}
}
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

	//tab2
	q2 = new QWidget;
	qlst2 = new QListWidget;
	qtabgrid2 = new QGridLayout;
	q2->setLayout(qtabgrid2);
	qtabgrid2->addWidget(qlst2);

	//buttons for tab2
	btnSortbyTitle = new QPushButton{ "&Sort by title" };
	qtabgrid2->addWidget(btnSortbyTitle);
	btnSortbyActor = new QPushButton{ "&Sort by actor" };
	qtabgrid2->addWidget(btnSortbyActor);
	btnSortbyYearAndGenre = new QPushButton{ "&Sort by year and genre" };
	qtabgrid2->addWidget(btnSortbyYearAndGenre);
	btnFilterbyTitle = new QPushButton{ "&Filter by title" };
	qtabgrid2->addWidget(btnFilterbyTitle);
	btnFilterbyYear = new QPushButton{ "&Filter by year" };
	qtabgrid2->addWidget(btnFilterbyYear);

	qtab->addTab(q1, "Films");
	qtab->addTab(q2, "Sort / Filter");

	MainLayout->addWidget(qtab);

	//layout1
	Layout1 = new QVBoxLayout;

	currentSelectedFilm = new QLabel{ "Not selected" };

	//text editors
	formLayout = new QFormLayout;
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
	btnFind = new QPushButton{ "&Find" };
	ButtonLayout->addWidget(btnFind);
	Layout1->addLayout(ButtonLayout);

	MainLayout->addLayout(Layout1);

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

	QObject::connect(btnAdd, &QPushButton::clicked, [&]() { addGUI(); });
	QObject::connect(btnDelete, &QPushButton::clicked, [&]() { removeGUI(); });
	QObject::connect(btnEdit, &QPushButton::clicked, [&]() { editGUI(); });
	QObject::connect(btnSortbyTitle, &QPushButton::clicked, [&]() { sortByGUI([](const Film& f1, const Film& f2) { return f1.getTitle() < f2.getTitle(); }); });
	QObject::connect(btnSortbyActor, &QPushButton::clicked, [&]() { sortByGUI([](const Film& f1, const Film& f2) { return f1.getActor() < f2.getActor(); }); });
	QObject::connect(btnSortbyYearAndGenre, &QPushButton::clicked, [&]() { sortByGUI(cmpYearAndGenre); });
}

void GUI::addGUI() {
	try {
		srv.addSRV(txtTitle->text().toStdString(), txtGenre->text().toStdString(), txtYear->text().toInt(), txtActor->text().toStdString());
		loadList(qlst, srv.getAllSRV());
		loadList(qlst2, srv.getAllSRV());
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

void GUI::editGUI() {
	try {
		srv.editSRV(selectedFilmTitle.toStdString(), selectedFilmYear.toInt(), txtTitle->text().toStdString(), txtGenre->text().toStdString(), txtYear->text().toInt(), txtActor->text().toStdString());
		loadList(qlst, srv.getAllSRV());
		loadList(qlst2, srv.getAllSRV());
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

void GUI::sortByGUI(bool(*compare)(const Film&, const Film&)) {
	try {
		if (srv.getAllSRV().size() == 0) {
			throw RepoException("\nThere are no films in the database!");
		}
		auto sorted = srv.getAllSRV();
		srv.sortBySRV(compare, sorted);
		loadList(qlst2, sorted);
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Exception!", QString::fromStdString(ex.getEx()));
	}
}
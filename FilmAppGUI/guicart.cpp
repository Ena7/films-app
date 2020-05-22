#include "guicart.h"

void CartGUI::initGUI() {
	qlstcart = new QListWidget;

	mainL = new QVBoxLayout;
	fLtT = new QFormLayout;
	currentSelectedFilm = new QLabel{ "Not selected" };
	txtTitle = new QLineEdit;
	setLayout(mainL);
	fLtT->addRow("Selected film:", currentSelectedFilm);
	fLtT->addRow("Title", txtTitle);
	mainL->addLayout(fLtT);
	mainL->addWidget(qlstcart);

	btnAddCart = new QPushButton{ "&Add to cart" };
	mainL->addWidget(btnAddCart);	
	btnClear = new QPushButton{ "&Clear cart" };
	mainL->addWidget(btnClear);
	btnUndoCart = new QPushButton{ "&Undo clear" };
	mainL->addWidget(btnUndoCart);

	generateL = new QHBoxLayout;
	generateF = new QFormLayout;
	txtGenerate = new QLineEdit;
	btnGenerate = new QPushButton{ "&Generate" };
	generateL->addLayout(generateF);
	generateF->addRow("Number:", txtGenerate);
	generateL->addWidget(btnGenerate);
	generateL->addLayout(generateF);
	mainL->addLayout(generateL);

	exportL = new QHBoxLayout;
	exportF = new QFormLayout;
	txtExport = new QLineEdit;
	btnExport = new QPushButton{ "&Export to .csv" };
	exportL->addLayout(exportF);
	exportF->addRow("Only filename:", txtExport);
	exportL->addWidget(btnExport);
	exportL->addLayout(exportF);
	mainL->addLayout(exportL);
}

void CartGUI::loadList(QListWidget* lst, vector<Film> films) {
	lst->clear();
	for (const auto& film : films) {
		auto item = new QListWidgetItem(QString::fromStdString(film.getTitle()), lst);
		item->setData(Qt::UserRole, film.getYear());
	}
}

void CartGUI::connectSignals() {
	QObject::connect(qlstcart, &QListWidget::itemSelectionChanged, [&]() {
		if (qlstcart->selectedItems().isEmpty()) {
			txtTitle->setText("");
			return;
		}
		QListWidgetItem* selectedItem = qlstcart->selectedItems().at(0);
		auto title = selectedItem->text();
		auto year = selectedItem->data(Qt::UserRole).toString();
		currentSelectedFilm->setText(title + " - " + year);
	});

	QObject::connect(btnAddCart, &QPushButton::clicked, [&]() { addCartGUI(); });
	QObject::connect(btnClear, &QPushButton::clicked, [&]() { clearGUI(); });
	QObject::connect(btnGenerate, &QPushButton::clicked, [&]() { generateGUI(); });
	QObject::connect(btnExport, &QPushButton::clicked, [&]() { exportGUI(); });
	QObject::connect(btnUndoCart, &QPushButton::clicked, [&]() { undoCartGUI(); });
}

void CartGUI::addCartGUI() {
	try {
		srvc.addToCartSV(txtTitle->text().toStdString());
		loadList(qlstcart, srvc.getCart());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Exception!", QString::fromStdString(ex.getEx()));
	}
}

void CartGUI::clearGUI() {
	try {
		if (srvc.getCart().size() == 0) {
			throw RepoException("There is nothing to clear!\n");
		}
		srvc.clearCartSV();
		loadList(qlstcart, srvc.getCart());
		currentSelectedFilm->setText("Not selected");
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Exception!", QString::fromStdString(ex.getEx()));
	}
}

void CartGUI::generateGUI() {
	try {
		if (txtGenerate->text().toInt() == 0) {
			throw RepoException("Invalid number!");
		}
		srvc.generate(txtGenerate->text().toInt());
		loadList(qlstcart, srvc.getCart());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Exception!", QString::fromStdString(ex.getEx()));
	}
}

void CartGUI::exportGUI() {
	try {
		if (txtExport->text().toStdString().size() == 0) {
			throw RepoException("Invalid filename!");
		}
		srvc.exportSV(txtExport->text().toStdString() + ".csv");
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Exception!", QString::fromStdString(ex.getEx()));
	}
}

void CartGUI::undoCartGUI() {
	try {
		srvc.undoCart();
		loadList(qlstcart, srvc.getCart());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Exception!", QString::fromStdString(ex.getEx()));
	}
}

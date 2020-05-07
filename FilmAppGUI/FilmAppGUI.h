#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_FilmAppGUI.h"

class FilmAppGUI : public QMainWindow
{
	Q_OBJECT

public:
	FilmAppGUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::FilmAppGUIClass ui;
};

#pragma once
#include <qwidget.h>
#include <qpainter.h>
#include <cstdlib>
#include <vector>
#include "observer.h"

using std::vector;

class ROCartGUI: public QWidget, public Observer {
private:
	ServiceCart& srvc;

public:
	ROCartGUI(ServiceCart& srvc) : srvc{ srvc } {
		srvc.addObserver(this);
	}

	void update() override {
		repaint();
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		for (auto i = 0; i < srvc.getCart().size(); i++) {
			int random_nr = rand() % 2;
			switch (random_nr) {
			case 0:
				p.drawRect(rand() % 400, rand() % 400, rand() % 50 + 20, rand() % 50 + 20);
				break;
			case 1:
				p.drawEllipse(rand() % 400, rand() % 400, rand() % 50 + 20, rand() % 50 + 20);
				break;
			}
		}
	}
};
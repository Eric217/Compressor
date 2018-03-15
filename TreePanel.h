#pragma once
#include "LinkedSet.hpp"

class TreePanel : public QWidget {
	Q_OBJECT
		
	LinkedSet<QLine> legs;
public:
	TreePanel(QWidget * parent);
	~TreePanel();
	void setLegs(LinkedSet<QLine> & set);
	void paintEvent(QPaintEvent *event);

};



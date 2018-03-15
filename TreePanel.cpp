#include "stdafx.h"
#include "TreePanel.h"


TreePanel::TreePanel(QWidget * parent) {
	setParent(parent);
}

void TreePanel::setLegs(LinkedSet<QLine> & lineSet) {
	legs.deinit();
	legs = lineSet;
}

void TreePanel::paintEvent(QPaintEvent * event)
{
	Q_UNUSED(event);
	QPainter painter(this);
	Node<QLine> * temp = legs.front;
	while (temp) {
		painter.drawLine(temp->data);
		temp = temp->link;
	}

}

TreePanel::~TreePanel()
{
}

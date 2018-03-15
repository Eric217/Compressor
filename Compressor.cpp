#include "stdafx.h"
#include "Compressor.h"
#include "Decode.h"
#include "Encode.h"
#include "TreePanel.h"
#include "LinkedSet.hpp"

Compressor::Compressor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setFixedSize(1300, 900);

	connect(ui.encoder, SIGNAL(clicked()), this, SLOT(selectFileToEncode()));
	connect(ui.decoder, SIGNAL(clicked()), this, SLOT(selectFileToDecode()));
	connect(ui.showTree, SIGNAL(clicked()), this, SLOT(drawTree()));
	scroll = new QScrollArea(this);
	scroll->setGeometry(140, 15, 1130, 830);
	//panel = new TreePanel(this);
	//scroll->setWidget(panel);
}


void Compressor::selectFileToEncode() {
	QString path = QFileDialog::getOpenFileName(this, "ѡ���ļ����б���", ".");
	string p = path.toStdString();
	if (encode(p)) {
		ui.decoder->setEnabled(1);
		ui.showTree->setEnabled(1);
	}
}

void Compressor::selectFileToDecode() {
	//QString path = QFileDialog::getOpenFileName(this, "choose");
	//string p = path.toStdString();
	decode(final_dir);
}

///˼·���߶�ΪN�Ķ������������п��ܽڵ��λ�ô浽���顣
///���ֵ��еĻ��������������Ѵ��ڵĽڵ���������λ�������ʼ�������浽�����С�
///�������ϣ���ʾ��ͼ��
void Compressor::drawTree() {
	QPoint *locations = getLocations();
	int contentH = locations[0].y() + UnitSize + 55;
	int unitNum = (int)pow(2, treeHeight - 1);
	int contentW = UnitSize * unitNum + SepaWidth * (unitNum + 1);
	TreePanel *panel = new TreePanel(this);
	panel->resize(contentW, contentH);
	//panel->setBackgroundRole(); //����ɫ231
	//scroll->setAlignment(Qt::AlignCenter);

	//ָ������ģʽ�ȵ�ûѧ�ᣬ�Ȳ���lambda�ˡ�������
	//ֱ��ȫŪpublic��������ƻ��˷�װ�ԡ�����ѧ��lambda���
	LinkedSet<int> buttonSet;//װ�����ڲ��ڵ��� locations�е�λ��
	LinkedSet<QLine> legSet; //QLine������==��������ֱ����

	///֮ǰ�������½���ԭ��д�ģ�����ԭ�������Ͻǣ���Ҫ����ϵת��
	int delta = contentH - UnitSize;

	//MARK: - �����ֵ����
	for (int i = 0; i < dict.curSize; i++) {
		char key[2]; key[0] = dict.words[i].key; key[1] = '\0';
		const string & str = dict.words[i].value;
		int len = str.length(), result = 0;
		const char * strp = str.c_str();
		for (int j = 0; j < len; j++) {
			buttonSet.push(result);
			QPoint st = QPoint(locations[result].x() + UnitSize / 2, contentH - locations[result].y());
			if (strp[j] == HFMLEFT) {
				result = result * 2 + 1;
				QPoint en = QPoint(locations[result].x() + UnitSize, delta - locations[result].y());
				QLine _line = QLine(st, en);
				legSet.push(_line);
			} else {
				result = result * 2 + 2;
				QPoint en = QPoint(locations[result].x(), delta - locations[result].y());
				QLine _line = QLine(st, en);
				legSet.push(_line);
			}
		}
		QPoint &pt = locations[result];
		QPushButton *but = getRegularButton(panel, pt.x(), delta - pt.y(), string(key));
	}
	//MARK: - ����λ���ռ���ϣ��߽���paint���ڵ������ͼ
	panel->setLegs(legSet);
	legSet.front = 0; //����ת�ƣ���ֹ��������
	Node<int> * tempN = buttonSet.front;
	while (tempN) {
		QPoint &pt = locations[tempN->data];
		QPushButton *but = getRegularButton(panel, pt.x(), delta - pt.y(), string(Zero_Sign));
		tempN = tempN->link;
	}
	free(locations);
	scroll->setWidget(panel);
	repaint();
}

QPoint * Compressor::getLocations() {
	int c = pow(2, treeHeight) - 1;
	QPoint *points = (QPoint *)malloc(c * sizeof(QPoint));
	//��ײ㵥��ȷ��λ��
	int s = pow(2, treeHeight - 1) - 1;
	int bottom = 15;
	for (int i = s; i <= 2 * s; i++)
		points[i] = QPoint((i - s + 1)*SepaWidth + (i - s)*UnitSize, bottom);

	//����㿿����ȷ��λ��
	for (int i = treeHeight - 2; i >= 0; i--) {
		s = pow(2, i) - 1;
		for (int j = s; j <= 2 * s; j++) {
			int point1Idx = 2 * j + 1;
			int x1 = points[point1Idx].x() + UnitSize;
			float bian = points[point1Idx + 1].x() - x1;
			float x2 = x1 + bian / 2 - UnitSize / 2;
			float y2;
			if (j == s) 
				y2 = points[point1Idx].y() + UnitSize + bian * cos(HeightAngle);
			else
				y2 = points[j - 1].y();
			points[j] = QPoint(x2, y2);
		}

	}
	return points;
}

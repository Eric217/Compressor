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
	QString path = QFileDialog::getOpenFileName(this, "选择文件进行编码", ".");
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

///思路：高度为N的二叉树，其所有可能节点的位置存到数组。
///对字典中的霍夫曼树遍历，把存在的节点和树杈利用位置数组初始化并保存到集合中。
///遍历集合，显示视图。
void Compressor::drawTree() {
	QPoint *locations = getLocations();
	int contentH = locations[0].y() + UnitSize + 55;
	int unitNum = (int)pow(2, treeHeight - 1);
	int contentW = UnitSize * unitNum + SepaWidth * (unitNum + 1);
	TreePanel *panel = new TreePanel(this);
	panel->resize(contentW, contentH);
	//panel->setBackgroundRole(); //背景色231
	//scroll->setAlignment(Qt::AlignCenter);

	//指定捕获模式等等没学会，先不用lambda了。。。。
	//直接全弄public。。大大破坏了封装性。。。学了lambda后改
	LinkedSet<int> buttonSet;//装的是内部节点在 locations中的位置
	LinkedSet<QLine> legSet; //QLine重载了==，所以能直接用

	///之前按照左下角是原点写的，现在原点在左上角，需要坐标系转换
	int delta = contentH - UnitSize;

	//MARK: - 对树字典遍历
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
	//MARK: - 所有位置收集完毕，边交给paint，节点加子视图
	panel->setLegs(legSet);
	legSet.front = 0; //引用转移，防止析构两次
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
	//最底层单独确定位置
	int s = pow(2, treeHeight - 1) - 1;
	int bottom = 15;
	for (int i = s; i <= 2 * s; i++)
		points[i] = QPoint((i - s + 1)*SepaWidth + (i - s)*UnitSize, bottom);

	//其余层靠子树确定位置
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

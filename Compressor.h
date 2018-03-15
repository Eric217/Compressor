#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Compressor.h"


class Compressor : public QMainWindow
{
	Q_OBJECT

public:
	Compressor(QWidget *parent = Q_NULLPTR);
	QScrollArea * scroll;
	//TreePanel * panel;

public slots:
	void selectFileToEncode();
	void selectFileToDecode();
	void drawTree();

private:
	Ui::CompressorClass ui;
	QPoint * getLocations();

};

 
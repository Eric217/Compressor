#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Compressor.h"

class Compressor : public QMainWindow
{
	Q_OBJECT

public:
	Compressor(QWidget *parent = Q_NULLPTR);

private:
	Ui::CompressorClass ui;
};

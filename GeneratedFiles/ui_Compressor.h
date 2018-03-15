/********************************************************************************
** Form generated from reading UI file 'Compressor.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPRESSOR_H
#define UI_COMPRESSOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CompressorClass
{
public:
    QWidget *centralWidget;
    QPushButton *encoder;
    QPushButton *decoder;
    QPushButton *showTree;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CompressorClass)
    {
        if (CompressorClass->objectName().isEmpty())
            CompressorClass->setObjectName(QStringLiteral("CompressorClass"));
        CompressorClass->resize(1300, 900);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CompressorClass->sizePolicy().hasHeightForWidth());
        CompressorClass->setSizePolicy(sizePolicy);
        CompressorClass->setMinimumSize(QSize(0, 0));
        CompressorClass->setMaximumSize(QSize(100000, 100000));
        centralWidget = new QWidget(CompressorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        encoder = new QPushButton(centralWidget);
        encoder->setObjectName(QStringLiteral("encoder"));
        encoder->setGeometry(QRect(10, 15, 111, 51));
        decoder = new QPushButton(centralWidget);
        decoder->setObjectName(QStringLiteral("decoder"));
        decoder->setEnabled(false);
        decoder->setGeometry(QRect(10, 95, 111, 51));
        showTree = new QPushButton(centralWidget);
        showTree->setObjectName(QStringLiteral("showTree"));
        showTree->setEnabled(false);
        showTree->setGeometry(QRect(10, 170, 111, 51));
        CompressorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CompressorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1300, 23));
        CompressorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CompressorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CompressorClass->addToolBar(Qt::BottomToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CompressorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CompressorClass->setStatusBar(statusBar);

        retranslateUi(CompressorClass);

        QMetaObject::connectSlotsByName(CompressorClass);
    } // setupUi

    void retranslateUi(QMainWindow *CompressorClass)
    {
        CompressorClass->setWindowTitle(QApplication::translate("CompressorClass", "Compressor", nullptr));
        encoder->setText(QApplication::translate("CompressorClass", "\351\200\211\346\213\251\346\226\207\344\273\266\345\274\200\345\247\213\347\274\226\347\240\201", nullptr));
        decoder->setText(QApplication::translate("CompressorClass", "\350\247\243\347\240\201", nullptr));
        showTree->setText(QApplication::translate("CompressorClass", "\346\230\276\347\244\272\346\240\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CompressorClass: public Ui_CompressorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPRESSOR_H

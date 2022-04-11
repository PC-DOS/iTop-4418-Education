/********************************************************************************
** Form generated from reading UI file 'helloworld.ui'
**
** Created: Thu Aug 4 01:32:41 2016
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELLOWORLD_H
#define UI_HELLOWORLD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_helloworld
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *helloworld)
    {
        if (helloworld->objectName().isEmpty())
            helloworld->setObjectName(QString::fromUtf8("helloworld"));
        helloworld->resize(400, 300);
        centralWidget = new QWidget(helloworld);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 40, 361, 101));
        helloworld->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(helloworld);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 25));
        helloworld->setMenuBar(menuBar);
        mainToolBar = new QToolBar(helloworld);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        helloworld->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(helloworld);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        helloworld->setStatusBar(statusBar);

        retranslateUi(helloworld);

        QMetaObject::connectSlotsByName(helloworld);
    } // setupUi

    void retranslateUi(QMainWindow *helloworld)
    {
        helloworld->setWindowTitle(QApplication::translate("helloworld", "helloworld", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("helloworld", "                                     helloworld", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class helloworld: public Ui_helloworld {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELLOWORLD_H

/********************************************************************************
** Form generated from reading UI file 'ledtest.ui'
**
** Created: Thu Mar 9 23:30:42 2017
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEDTEST_H
#define UI_LEDTEST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ledtest
{
public:
    QWidget *centralWidget;
    QCheckBox *checkBox_LED;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ledtest)
    {
        if (ledtest->objectName().isEmpty())
            ledtest->setObjectName(QString::fromUtf8("ledtest"));
        ledtest->resize(400, 300);
        centralWidget = new QWidget(ledtest);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        checkBox_LED = new QCheckBox(centralWidget);
        checkBox_LED->setObjectName(QString::fromUtf8("checkBox_LED"));
        checkBox_LED->setGeometry(QRect(60, 20, 98, 22));
        ledtest->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ledtest);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 25));
        ledtest->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ledtest);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ledtest->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ledtest);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ledtest->setStatusBar(statusBar);

        retranslateUi(ledtest);

        QMetaObject::connectSlotsByName(ledtest);
    } // setupUi

    void retranslateUi(QMainWindow *ledtest)
    {
        ledtest->setWindowTitle(QApplication::translate("ledtest", "ledtest", 0, QApplication::UnicodeUTF8));
        checkBox_LED->setText(QApplication::translate("ledtest", "LED", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ledtest: public Ui_ledtest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEDTEST_H

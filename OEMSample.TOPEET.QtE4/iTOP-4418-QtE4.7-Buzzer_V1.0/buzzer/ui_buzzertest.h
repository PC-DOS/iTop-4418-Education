/********************************************************************************
** Form generated from reading UI file 'buzzertest.ui'
**
** Created: Tue Jul 26 18:46:48 2016
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUZZERTEST_H
#define UI_BUZZERTEST_H

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

class Ui_buzzertest
{
public:
    QWidget *centralWidget;
    QCheckBox *checkBox_Buzzer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *buzzertest)
    {
        if (buzzertest->objectName().isEmpty())
            buzzertest->setObjectName(QString::fromUtf8("buzzertest"));
        buzzertest->resize(400, 300);
        centralWidget = new QWidget(buzzertest);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        checkBox_Buzzer = new QCheckBox(centralWidget);
        checkBox_Buzzer->setObjectName(QString::fromUtf8("checkBox_Buzzer"));
        checkBox_Buzzer->setGeometry(QRect(90, 40, 98, 22));
        buzzertest->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(buzzertest);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 25));
        buzzertest->setMenuBar(menuBar);
        mainToolBar = new QToolBar(buzzertest);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        buzzertest->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(buzzertest);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        buzzertest->setStatusBar(statusBar);

        retranslateUi(buzzertest);

        QMetaObject::connectSlotsByName(buzzertest);
    } // setupUi

    void retranslateUi(QMainWindow *buzzertest)
    {
        buzzertest->setWindowTitle(QApplication::translate("buzzertest", "buzzertest", 0, QApplication::UnicodeUTF8));
        checkBox_Buzzer->setText(QApplication::translate("buzzertest", "BUZZER", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class buzzertest: public Ui_buzzertest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUZZERTEST_H

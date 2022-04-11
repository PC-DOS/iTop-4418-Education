/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Aug 14 22:19:14 2018
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QSpinBox *month;
    QSpinBox *day;
    QSpinBox *second;
    QSpinBox *hour;
    QPushButton *set;
    QSpinBox *minute;
    QSpinBox *year;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(607, 274);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 7, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 3, 1, 1);

        month = new QSpinBox(centralWidget);
        month->setObjectName(QString::fromUtf8("month"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(month->sizePolicy().hasHeightForWidth());
        month->setSizePolicy(sizePolicy);
        month->setMaximum(3000);

        gridLayout->addWidget(month, 0, 1, 1, 1);

        day = new QSpinBox(centralWidget);
        day->setObjectName(QString::fromUtf8("day"));
        sizePolicy.setHeightForWidth(day->sizePolicy().hasHeightForWidth());
        day->setSizePolicy(sizePolicy);
        day->setMaximum(3000);

        gridLayout->addWidget(day, 0, 2, 1, 1);

        second = new QSpinBox(centralWidget);
        second->setObjectName(QString::fromUtf8("second"));
        sizePolicy.setHeightForWidth(second->sizePolicy().hasHeightForWidth());
        second->setSizePolicy(sizePolicy);
        second->setMaximum(3000);

        gridLayout->addWidget(second, 0, 5, 1, 1);

        hour = new QSpinBox(centralWidget);
        hour->setObjectName(QString::fromUtf8("hour"));
        sizePolicy.setHeightForWidth(hour->sizePolicy().hasHeightForWidth());
        hour->setSizePolicy(sizePolicy);
        hour->setMaximum(3000);

        gridLayout->addWidget(hour, 0, 3, 1, 1);

        set = new QPushButton(centralWidget);
        set->setObjectName(QString::fromUtf8("set"));

        gridLayout->addWidget(set, 0, 6, 1, 1);

        minute = new QSpinBox(centralWidget);
        minute->setObjectName(QString::fromUtf8("minute"));
        sizePolicy.setHeightForWidth(minute->sizePolicy().hasHeightForWidth());
        minute->setSizePolicy(sizePolicy);
        minute->setMaximum(3000);

        gridLayout->addWidget(minute, 0, 4, 1, 1);

        year = new QSpinBox(centralWidget);
        year->setObjectName(QString::fromUtf8("year"));
        sizePolicy.setHeightForWidth(year->sizePolicy().hasHeightForWidth());
        year->setSizePolicy(sizePolicy);
        year->setMouseTracking(true);
        year->setMaximum(3000);

        gridLayout->addWidget(year, 0, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 607, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        set->setText(QApplication::translate("MainWindow", "set", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

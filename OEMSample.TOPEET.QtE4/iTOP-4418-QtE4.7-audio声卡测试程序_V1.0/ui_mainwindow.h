/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Aug 14 22:13:15 2018
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
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout;
    QPushButton *pause;
    QPushButton *add;
    QRadioButton *radioLINEIN;
    QLabel *pos;
    QPushButton *del;
    QPushButton *play;
    QPushButton *record;
    QSlider *slider;
    QListWidget *list;
    QLabel *length;
    QLabel *label;
    QPushButton *stop;
    QRadioButton *radioMIC;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(750, 564);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setEnabled(true);
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pause = new QPushButton(centralWidget);
        pause->setObjectName(QString::fromUtf8("pause"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pause->sizePolicy().hasHeightForWidth());
        pause->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pause, 2, 1, 1, 1);

        add = new QPushButton(centralWidget);
        add->setObjectName(QString::fromUtf8("add"));
        sizePolicy.setHeightForWidth(add->sizePolicy().hasHeightForWidth());
        add->setSizePolicy(sizePolicy);

        gridLayout->addWidget(add, 2, 3, 1, 1);

        radioLINEIN = new QRadioButton(centralWidget);
        radioLINEIN->setObjectName(QString::fromUtf8("radioLINEIN"));
        sizePolicy.setHeightForWidth(radioLINEIN->sizePolicy().hasHeightForWidth());
        radioLINEIN->setSizePolicy(sizePolicy);

        gridLayout->addWidget(radioLINEIN, 1, 10, 1, 1);

        pos = new QLabel(centralWidget);
        pos->setObjectName(QString::fromUtf8("pos"));
        sizePolicy.setHeightForWidth(pos->sizePolicy().hasHeightForWidth());
        pos->setSizePolicy(sizePolicy);
        pos->setAutoFillBackground(false);

        gridLayout->addWidget(pos, 1, 6, 1, 1);

        del = new QPushButton(centralWidget);
        del->setObjectName(QString::fromUtf8("del"));
        del->setEnabled(true);
        sizePolicy.setHeightForWidth(del->sizePolicy().hasHeightForWidth());
        del->setSizePolicy(sizePolicy);

        gridLayout->addWidget(del, 2, 4, 1, 5);

        play = new QPushButton(centralWidget);
        play->setObjectName(QString::fromUtf8("play"));
        sizePolicy.setHeightForWidth(play->sizePolicy().hasHeightForWidth());
        play->setSizePolicy(sizePolicy);

        gridLayout->addWidget(play, 2, 0, 1, 1);

        record = new QPushButton(centralWidget);
        record->setObjectName(QString::fromUtf8("record"));
        sizePolicy.setHeightForWidth(record->sizePolicy().hasHeightForWidth());
        record->setSizePolicy(sizePolicy);

        gridLayout->addWidget(record, 2, 9, 1, 2);

        slider = new QSlider(centralWidget);
        slider->setObjectName(QString::fromUtf8("slider"));
        sizePolicy.setHeightForWidth(slider->sizePolicy().hasHeightForWidth());
        slider->setSizePolicy(sizePolicy);
        slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slider, 1, 0, 1, 4);

        list = new QListWidget(centralWidget);
        list->setObjectName(QString::fromUtf8("list"));
        list->setEnabled(true);

        gridLayout->addWidget(list, 0, 0, 1, 11);

        length = new QLabel(centralWidget);
        length->setObjectName(QString::fromUtf8("length"));
        sizePolicy.setHeightForWidth(length->sizePolicy().hasHeightForWidth());
        length->setSizePolicy(sizePolicy);

        gridLayout->addWidget(length, 1, 8, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 1, 7, 1, 1);

        stop = new QPushButton(centralWidget);
        stop->setObjectName(QString::fromUtf8("stop"));
        sizePolicy.setHeightForWidth(stop->sizePolicy().hasHeightForWidth());
        stop->setSizePolicy(sizePolicy);

        gridLayout->addWidget(stop, 2, 2, 1, 1);

        radioMIC = new QRadioButton(centralWidget);
        radioMIC->setObjectName(QString::fromUtf8("radioMIC"));
        sizePolicy.setHeightForWidth(radioMIC->sizePolicy().hasHeightForWidth());
        radioMIC->setSizePolicy(sizePolicy);
        radioMIC->setChecked(true);

        gridLayout->addWidget(radioMIC, 1, 9, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 750, 25));
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
        pause->setText(QApplication::translate("MainWindow", "pause", 0, QApplication::UnicodeUTF8));
        add->setText(QApplication::translate("MainWindow", "add", 0, QApplication::UnicodeUTF8));
        radioLINEIN->setText(QApplication::translate("MainWindow", "LINEIN", 0, QApplication::UnicodeUTF8));
        pos->setText(QApplication::translate("MainWindow", "00:00", 0, QApplication::UnicodeUTF8));
        del->setText(QApplication::translate("MainWindow", "del", 0, QApplication::UnicodeUTF8));
        play->setText(QApplication::translate("MainWindow", "play", 0, QApplication::UnicodeUTF8));
        record->setText(QApplication::translate("MainWindow", "record", 0, QApplication::UnicodeUTF8));
        length->setText(QApplication::translate("MainWindow", "00:00", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "  |", 0, QApplication::UnicodeUTF8));
        stop->setText(QApplication::translate("MainWindow", "stop", 0, QApplication::UnicodeUTF8));
        radioMIC->setText(QApplication::translate("MainWindow", "MIC", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

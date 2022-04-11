/********************************************************************************
** Form generated from reading UI file 'qtwatchdog.ui'
**
** Created: Thu Oct 13 02:33:46 2016
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWATCHDOG_H
#define UI_QTWATCHDOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qtwatchdog
{
public:
    QPushButton *start_pushButton;
    QPushButton *feed_pushButton;
    QLabel *label;

    void setupUi(QWidget *qtwatchdog)
    {
        if (qtwatchdog->objectName().isEmpty())
            qtwatchdog->setObjectName(QString::fromUtf8("qtwatchdog"));
        qtwatchdog->resize(400, 300);
        start_pushButton = new QPushButton(qtwatchdog);
        start_pushButton->setObjectName(QString::fromUtf8("start_pushButton"));
        start_pushButton->setGeometry(QRect(20, 50, 181, 31));
        feed_pushButton = new QPushButton(qtwatchdog);
        feed_pushButton->setObjectName(QString::fromUtf8("feed_pushButton"));
        feed_pushButton->setGeometry(QRect(20, 110, 181, 31));
        label = new QLabel(qtwatchdog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 200, 361, 41));

        retranslateUi(qtwatchdog);

        QMetaObject::connectSlotsByName(qtwatchdog);
    } // setupUi

    void retranslateUi(QWidget *qtwatchdog)
    {
        qtwatchdog->setWindowTitle(QApplication::translate("qtwatchdog", "qtwatchdog", 0, QApplication::UnicodeUTF8));
        start_pushButton->setText(QApplication::translate("qtwatchdog", "start watchdog", 0, QApplication::UnicodeUTF8));
        feed_pushButton->setText(QApplication::translate("qtwatchdog", "feed fog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("qtwatchdog", "System will restart in 10 seconds without feed dog!", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class qtwatchdog: public Ui_qtwatchdog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWATCHDOG_H

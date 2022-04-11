/********************************************************************************
** Form generated from reading UI file 'adtest.ui'
**
** Created: Tue Jul 26 20:13:50 2016
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADTEST_H
#define UI_ADTEST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_adtest
{
public:
    QLabel *Text;

    void setupUi(QWidget *adtest)
    {
        if (adtest->objectName().isEmpty())
            adtest->setObjectName(QString::fromUtf8("adtest"));
        adtest->resize(400, 300);
        Text = new QLabel(adtest);
        Text->setObjectName(QString::fromUtf8("Text"));
        Text->setGeometry(QRect(130, 120, 67, 17));

        retranslateUi(adtest);

        QMetaObject::connectSlotsByName(adtest);
    } // setupUi

    void retranslateUi(QWidget *adtest)
    {
        adtest->setWindowTitle(QApplication::translate("adtest", "adtest", 0, QApplication::UnicodeUTF8));
        Text->setText(QApplication::translate("adtest", "adc", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class adtest: public Ui_adtest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADTEST_H

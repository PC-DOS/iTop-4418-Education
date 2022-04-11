/********************************************************************************
** Form generated from reading UI file 'rs485.ui'
**
** Created: Tue Sep 27 03:18:44 2016
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RS485_H
#define UI_RS485_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_rs485
{
public:
    QLabel *label_2;
    QTextEdit *m_receive;
    QTextEdit *m_send;
    QLabel *label;
    QPushButton *m_sendButton;

    void setupUi(QWidget *rs485)
    {
        if (rs485->objectName().isEmpty())
            rs485->setObjectName(QString::fromUtf8("rs485"));
        rs485->resize(452, 527);
        label_2 = new QLabel(rs485);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 0, 81, 20));
        m_receive = new QTextEdit(rs485);
        m_receive->setObjectName(QString::fromUtf8("m_receive"));
        m_receive->setGeometry(QRect(10, 30, 441, 201));
        m_send = new QTextEdit(rs485);
        m_send->setObjectName(QString::fromUtf8("m_send"));
        m_send->setGeometry(QRect(10, 280, 441, 191));
        label = new QLabel(rs485);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 250, 81, 20));
        m_sendButton = new QPushButton(rs485);
        m_sendButton->setObjectName(QString::fromUtf8("m_sendButton"));
        m_sendButton->setGeometry(QRect(160, 490, 131, 31));

        retranslateUi(rs485);

        QMetaObject::connectSlotsByName(rs485);
    } // setupUi

    void retranslateUi(QWidget *rs485)
    {
        rs485->setWindowTitle(QApplication::translate("rs485", "rs485", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("rs485", "ReceiveEdit", 0, QApplication::UnicodeUTF8));
        m_receive->setHtml(QApplication::translate("rs485", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0, QApplication::UnicodeUTF8));
        m_send->setHtml(QApplication::translate("rs485", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">123</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("rs485", "SendEdit", 0, QApplication::UnicodeUTF8));
        m_sendButton->setText(QApplication::translate("rs485", "Send", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class rs485: public Ui_rs485 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RS485_H

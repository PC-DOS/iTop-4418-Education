/********************************************************************************
** Form generated from reading UI file 'networktcp.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWORKTCP_H
#define UI_NETWORKTCP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NetworkTcp
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit_IP;
    QLineEdit *lineEdit_NetPort;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_ConnectServer;
    QPushButton *pushButton_StartServer;
    QPushButton *pushButton_Send;
    QLineEdit *lineEdit_sendmsg;
    QTextEdit *textEdit_Info;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *NetworkTcp)
    {
        if (NetworkTcp->objectName().isEmpty())
            NetworkTcp->setObjectName(QStringLiteral("NetworkTcp"));
        NetworkTcp->resize(580, 501);
        centralWidget = new QWidget(NetworkTcp);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lineEdit_IP = new QLineEdit(centralWidget);
        lineEdit_IP->setObjectName(QStringLiteral("lineEdit_IP"));
        lineEdit_IP->setGeometry(QRect(430, 40, 121, 27));
        lineEdit_NetPort = new QLineEdit(centralWidget);
        lineEdit_NetPort->setObjectName(QStringLiteral("lineEdit_NetPort"));
        lineEdit_NetPort->setGeometry(QRect(430, 80, 121, 27));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(390, 40, 31, 31));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(390, 80, 41, 20));
        pushButton_ConnectServer = new QPushButton(centralWidget);
        pushButton_ConnectServer->setObjectName(QStringLiteral("pushButton_ConnectServer"));
        pushButton_ConnectServer->setGeometry(QRect(430, 220, 99, 27));
        pushButton_StartServer = new QPushButton(centralWidget);
        pushButton_StartServer->setObjectName(QStringLiteral("pushButton_StartServer"));
        pushButton_StartServer->setGeometry(QRect(430, 280, 99, 27));
        pushButton_Send = new QPushButton(centralWidget);
        pushButton_Send->setObjectName(QStringLiteral("pushButton_Send"));
        pushButton_Send->setGeometry(QRect(120, 400, 99, 27));
        lineEdit_sendmsg = new QLineEdit(centralWidget);
        lineEdit_sendmsg->setObjectName(QStringLiteral("lineEdit_sendmsg"));
        lineEdit_sendmsg->setGeometry(QRect(20, 350, 331, 41));
        textEdit_Info = new QTextEdit(centralWidget);
        textEdit_Info->setObjectName(QStringLiteral("textEdit_Info"));
        textEdit_Info->setGeometry(QRect(0, 20, 381, 311));
        NetworkTcp->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(NetworkTcp);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 580, 25));
        NetworkTcp->setMenuBar(menuBar);
        mainToolBar = new QToolBar(NetworkTcp);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        NetworkTcp->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(NetworkTcp);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        NetworkTcp->setStatusBar(statusBar);

        retranslateUi(NetworkTcp);

        QMetaObject::connectSlotsByName(NetworkTcp);
    } // setupUi

    void retranslateUi(QMainWindow *NetworkTcp)
    {
        NetworkTcp->setWindowTitle(QApplication::translate("NetworkTcp", "NetworkTcp", 0));
        lineEdit_IP->setText(QApplication::translate("NetworkTcp", "192.168.0.31", 0));
        lineEdit_NetPort->setText(QApplication::translate("NetworkTcp", "19999", 0));
        label->setText(QApplication::translate("NetworkTcp", "IP:", 0));
        label_2->setText(QApplication::translate("NetworkTcp", "\347\253\257\345\217\243:", 0));
        pushButton_ConnectServer->setText(QApplication::translate("NetworkTcp", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", 0));
        pushButton_StartServer->setText(QApplication::translate("NetworkTcp", "\345\220\257\345\212\250\346\234\215\345\212\241\345\231\250", 0));
        pushButton_Send->setText(QApplication::translate("NetworkTcp", "\345\217\221\351\200\201", 0));
        lineEdit_sendmsg->setText(QApplication::translate("NetworkTcp", "hello!", 0));
    } // retranslateUi

};

namespace Ui {
    class NetworkTcp: public Ui_NetworkTcp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORKTCP_H

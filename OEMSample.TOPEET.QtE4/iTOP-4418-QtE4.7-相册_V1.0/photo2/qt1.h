#ifndef QT1_H
#define QT1_H

#include <QDialog>
#include <QWidget>
#include <QString>
#include <QPushButton>
#include <QProcess>
#include <QTimer>


#include "ui_qt1.h"
//#include "dlinklist.h"

class Qt1: public QDialog,public Ui_Qt1
{
	Q_OBJECT
public:
	Qt1(QWidget *parent = 0);
	~Qt1();

	void strip(char *s);
	int judge(char *s);
//	void insert_dlinklist(DLIST *d,char *s);

signals:
//	mysig();
	
public slots:
	void fun_time();
	void fun_pic();
	void fun_cntl();
	void display_pic();
	void fun_prev();
	void fun_delete();
	void fun_open();
	
private:
	QTimer t1;	//¶¨Ê±Æ÷
	QTimer t2;
	int len;
};


#endif 

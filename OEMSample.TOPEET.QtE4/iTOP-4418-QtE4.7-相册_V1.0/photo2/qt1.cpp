#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <QPainter>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QLineEdit>
#include <QTimer>
#include <pthread.h>
#include <QProcess>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>

#include <QDateTime>

#include "qt1.h"
#include "dlinklist.c"		//包含dlinklist.h老是提示undefined reference

static int i=0;
//DLIST* Qt1:: p=NULL;
DLIST *p;
DLIST *q;
DLIST head;
void insert_dlinklist(DLIST *d,char *s);


Qt1::Qt1(QWidget *parent):QDialog(parent)
{
  	setupUi(this);
//  rb_manual->setChecked(true);

	rb_manual->setDisabled(true);
	rb_auto->setDisabled(true);
	pb_prev->setDisabled(true);
	pb_next->setDisabled(true);
	pb_del->setDisabled(true);
	
	connect(rb_auto,SIGNAL(clicked()),this,SLOT(fun_cntl())); 
	connect(rb_manual,SIGNAL(clicked()),this,SLOT(fun_cntl())); 
	connect(pb_prev,SIGNAL(clicked()),this,SLOT(fun_prev())); 
	connect(pb_next,SIGNAL(clicked()),this,SLOT(fun_pic())); 
	connect(pb_del,SIGNAL(clicked()),this,SLOT(fun_delete())); 	
	connect(pb_open,SIGNAL(clicked()),this,SLOT(fun_open())); 	
  	connect(&t1,SIGNAL(timeout()),this,SLOT(fun_time()));
 	connect(&t2,SIGNAL(timeout()),this,SLOT(fun_pic())); 

  	t1.start(1000);						//启动定时器，间隔1s，每过1s会发送一次信号这样实现了走表
	init_dlinklist(&head);
}

void Qt1::fun_time()
{
	QDateTime d=QDateTime::currentDateTime();	//获取当前时间,currentDateTime()是一个静态函数
    lb_time->setText(d.toString("yyyy-MM-dd-ddd hh:mm:ss"));	//设置时间格式	
}

void Qt1::fun_cntl()
{
	if(rb_manual->isChecked ())
	{
		t2.stop();
		pb_prev->setEnabled(true);	
		pb_next->setEnabled(true);	
	}
	else if(rb_auto->isChecked ())
	{
		t2.start(1000);
		pb_prev->setEnabled(false);	
		pb_next->setEnabled(false);	
	}
}

void Qt1::fun_pic()		
{
	i++;
	if(i==(len+1))i=1;

	p=p->next;
	display_pic();
}


void Qt1::fun_prev()	//fun_next()与fun_pic()一致
{
	i--;
	if(i==0)i=len;

	p=p->prev;
	display_pic();
}

void Qt1::display_pic()
{
	QString buf(p->path);
	QPixmap p(buf);
	lb_pic->setPixmap(p);
	lb_pic->setScaledContents(1);
	lb_num->setText(QString::number(i));
	lb_sum->setText(QString::number(len));
}

void Qt1::fun_delete()
{
	int ret;
	ret=QMessageBox::warning(this, tr("image browser"),
					   tr("Are you sure to delete it?"),
					   QMessageBox::Yes | QMessageBox::No,
					   QMessageBox::No);
	if(ret==QMessageBox::Yes)
	{
		remove(p->path);
		DLIST *r=(&head)->next;
		int n=1;
		while(r!=p)		//找到当前 p的位置
		{
			n++;
			r=r->next;
		}
		p=p->next;
		del_dlinklist(&head,n);
		if(i==len)i--;
		len=legnth_dlinklist(&head);
		display_pic();
	}
//	dlinkilist_tofile(&head);
}

void Qt1::fun_open()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                 "/mnt/hgfs/share",
                                                 tr("Images (*.png *.xpm *.jpg)"));
	if(fileName!=NULL)
	{
		init_dlinklist(&head);	//为打开另一个目录做准备
		char *str;
		char filename[100]={0};
		DIR *dp;					//指向目录
		struct dirent *dirp;		//指向目录项(可以是子目录或普通文件)
		
		int m=strlen(fileName.toAscii().data());
		str=(char*)malloc(m);
		strcpy(str,fileName.toAscii().data());
		strcpy(filename,str);

		QString buf(fileName.toAscii().data());
		QPixmap first(buf);
		lb_pic->setPixmap(first);
		lb_pic->setScaledContents(1);
		
		strip(filename);
		dp=opendir(filename);
		while(dirp=readdir(dp))
		{
			if(judge(dirp->d_name)==1)
			{
				strcat(filename,"/");
				strcat(filename,dirp->d_name);	//文件所在的目录+文件名=绝对路径
				printf("%s\n",filename);
				insert_dlinklist(&head,filename);
				filename[strlen(filename)-strlen(dirp->d_name)-1]='\0';
			}	
		}
		q->next=(&head)->next;
		(&head)->next->prev=q;
		
		len=legnth_dlinklist(&head);
		int pos=1;
		DLIST *r=(&head)->next;
		while(strcmp(r->path,str)!=0)
		{
			r=r->next;
			pos++;
		}
		p=r;
		i=pos;
		lb_num->setText(QString::number(i));
		lb_sum->setText(QString::number(len));
		
		rb_manual->setDisabled(false);
		rb_auto->setDisabled(false);
		pb_prev->setDisabled(false);
		pb_next->setDisabled(false);
		pb_del->setDisabled(false);
		rb_manual->setChecked(true);
//		display_pic();
	}
//	dlinkilist_tofile(&head);
}

void Qt1::strip(char *s)
{
	char *p=s;
	int n=0;
	while(*p)
	{
		if(*p=='/')
		{
			n++;
		}
		p++;
	}
	if(n==1)
	{
		s[1]='\0';
	}
	else
	{
		p--;
		while(*p)
		{
			if(*p=='/')
			{
				*p='\0';
				break;
			}
			p--;
		}
	}
}

int Qt1::judge(char * s)	
{
	int i,len=strlen(s);
	char *p=s;
	if(len<5)
	{
		return 0;
	}
	else 
	{
		while(*p)
		{
			p++;
		}
		for(i=0;i<4;i++)p--;
		if((strncmp(p,".jpg",4)==0)||(strncmp(p,".png",4)==0)||(strncmp(p,".xpm",4)==0))
		{
			return 1;
		}
		else 
			return 0;
	}
}

void insert_dlinklist(DLIST *d,char *s)	//这里是末尾添加,之所以把这个函数搬到这里，是因为我想使用全局变量DLIST *q
{
	DLIST *r=d;
//	DLIST *q;
	q=(DLIST*)malloc(sizeof(DLIST));	//这里的q不能是局部的，否则无法形成双向循环链表
	memset(q,0,sizeof(q));
	strcpy(q->path,s);

	if(r->next==NULL)
	{
		r->next=q;
		q->next=NULL;
	}
	else
	{
		while(r->next!=NULL)
		{
			r=r->next;
		}
		r->next=q;
		q->prev=r;
		q->next=NULL;
	}
	printf("insert success\n");
}


Qt1::~Qt1()
{
 
}

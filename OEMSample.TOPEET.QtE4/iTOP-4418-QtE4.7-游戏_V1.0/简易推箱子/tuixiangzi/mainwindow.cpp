#include <QDebug>
#include "mainwindow.h"
//#include "mainpaint.h"

int LEVELNUM=3;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{    
  	///////////////////建立菜单栏/////////////////   
  	//createAction();    
  	//createMenu();    
  	/////////////////////布局////////////////////////
  	widget=new QWidget;    
  	setCentralWidget(widget);    
	
  	mainmap=new mapPaint;   
	
  	levelLabel=new QLabel(tr("current check point:"));   
	
  	levelLCD=new QLCDNumber;    
	
  	stepLabel=new QLabel(tr("current step:")); 
	
  	stepLCD=new QLCDNumber;  
	
  	restartButton=new QPushButton(tr("restart game:"));    
  	connect(restartButton,SIGNAL(clicked()),this,SLOT(restartGameSlot()));    
  	restartButton->setEnabled(false);   

	
	beginButton=new QPushButton(tr("begin game:"));    
  	connect(beginButton,SIGNAL(clicked()),this,SLOT(beginGameSlot())); 
	
  	QVBoxLayout *rightLayout=new QVBoxLayout;    
  	rightLayout->addWidget(levelLabel);    
  	rightLayout->addWidget(levelLCD);    
  	rightLayout->addWidget(stepLabel);    
  	rightLayout->addWidget(stepLCD);    
  	rightLayout->addWidget(restartButton);   
	rightLayout->addWidget(beginButton);   
  	rightLayout->addSpacing(MAPV*30-150); 
	
  	QHBoxLayout *mainLayout=new QHBoxLayout;    
  	mainLayout->addWidget(mainmap);    
  	mainLayout->addLayout(rightLayout);    
  	widget->setLayout(mainLayout);    
	
  	//////////////////////////数据初始化//////////////////////
  	//timer=new QTimer(this);    
  	//connect(timer,SIGNAL(timeout()),this,SLOT(soundSlot()));    
	  
  	mainmap->levelNow=0;    
  	mainmap->stepNow=0;    
  	mainmap->man_h=0;    
  	mainmap->man_v=0;    
  	mainmap->BeginOrEnd=-1;    
  	mainmap->update();    
  	boxNum=0;    
  	levelLCD->display(mainmap->levelNow);    
  	stepLCD->display(mainmap->stepNow);    
  	createMap();    
  	/////////////////程序整体设定///////////////////////
  	setWindowTitle(tr("tuixiangzi game"));    
  	widget->setFocus();    
  	statusBar()->showMessage(tr("welcome!"));

	beginGameSlot();
	
}
void MainWindow::createAction()
{    
    qDebug()<<"createAction";
	beginGameAction=new QAction(tr("start game"),this);    
	beginGameAction->setShortcut(QKeySequence("Ctrl+B"));    
	beginGameAction->setStatusTip(tr("new game"));    
	connect(beginGameAction,SIGNAL(triggered()),this,SLOT(beginGameSlot()));    
	
	chooseGameAction=new QAction(tr("chose point"),this);    
	chooseGameAction->setShortcut(QKeySequence("Ctrl+C"));    
	chooseGameAction->setStatusTip(tr("check point"));    
	connect(chooseGameAction,SIGNAL(triggered()),this,SLOT(chooseGameSlot()));   
	
	restartGameAction=new QAction(tr("restart game"),this);    
	restartGameAction->setShortcut(QKeySequence("Ctrl+R"));    
	restartGameAction->setStatusTip(tr("restart current game"));    
	restartGameAction->setEnabled(false);    
	connect(restartGameAction,SIGNAL(triggered()),this,SLOT(restartGameSlot()));    
	
	endGameAction=new QAction(tr("game over"),this);    
	endGameAction->setShortcut(QKeySequence("Ctrl+E"));    
	endGameAction->setStatusTip(tr("game over current"));    
	endGameAction->setEnabled(false);    
	connect(endGameAction,SIGNAL(triggered()),this,SLOT(endGameSlot()));    
	
	openMusicAction=new QAction(tr("play music"),this);    
	openMusicAction->setShortcut(QKeySequence(tr("Ctrl+O")));    
	openMusicAction->setStatusTip(tr("play music"));    
	connect(openMusicAction,SIGNAL(triggered()),this,SLOT(openMusicSlot()));   
	
	closeMusicAction=new QAction(tr("stop music"),this);    
	closeMusicAction->setShortcut(QKeySequence("Ctrl+P"));    
	closeMusicAction->setStatusTip(tr("stop music"));    
	closeMusicAction->setEnabled(false);    
	connect(closeMusicAction,SIGNAL(triggered()),this,SLOT(closeMusicSlot()));   
		
	aboutAction=new QAction(tr("aoubt"),this);    
	aboutAction->setShortcut(QKeySequence("Ctrl+A"));    
	aboutAction->setStatusTip(tr("Info"));    
	connect(aboutAction,SIGNAL(triggered()),this,SLOT(aboutSlot()));
}
void MainWindow::createMenu()
{    
	qDebug()<<"createMenu";
	gameMenu=menuBar()->addMenu(tr("game"));    
	gameMenu->addAction(beginGameAction);    
	gameMenu->addAction(chooseGameAction);    
	gameMenu->addAction(restartGameAction);    
	gameMenu->addSeparator();    
	gameMenu->addAction(endGameAction);    
	musicMenu=menuBar()->addMenu(tr("music"));    
	musicMenu->addAction(openMusicAction);    
	musicMenu->addAction(closeMusicAction);    
	helpMenu=menuBar()->addMenu(tr("help"));    
	helpMenu->addAction(aboutAction);
}
void MainWindow::beginGameSlot()
{    
	qDebug()<<"beginGameSlot";
	//mainmap->levelNow=1;
	startGame(1);
}
void MainWindow::chooseGameSlot()
{    
	//chooseDlg l;    
	//l.exec();    
	//chooseNum=l.chooseNum;    
	//startGame(chooseNum);
}
void MainWindow::startGame(int x)
{    
	qDebug()<<"startGame";
	widget->setFocus();    
	//endGameAction->setEnabled(true);    
	//restartGameAction->setEnabled(true);    
	restartButton->setEnabled(true);    
	mainmap->man_h=man[x][0];    
	mainmap->man_v=man[x][1];    
	boxNum=0;   
	for(int i=0;i<MAPH;i++)        
		for(int j=0;j<MAPV;j++)            
			mainmap->mapNow[i][j]=map[x][i][j];    
		
	mainmap->mapNow[mainmap->man_h][mainmap->man_v]=MAN;    
	mainmap->levelNow=x;    
	mainmap->stepNow=0;    
	stepLCDShow();    
	levelLCDShow();   
	mainmap->update();    
	levelLCDShow();
}
void MainWindow::restartGameSlot()
{    
	qDebug()<<"restartGameSlot";
	startGame(mainmap->levelNow);
}
void MainWindow::endGameSlot()
{    
	qDebug()<<"endGameSlot";
	endGameAction->setEnabled(false);    
	restartGameAction->setEnabled(false);    
	restartButton->setEnabled(false);    
	mainmap->levelNow=0;    
	mainmap->stepNow=0;    
	boxNum=0;    
	mainmap->BeginOrEnd=1;    
	mainmap->update();    
	QMessageBox::information(this,tr("game over"),tr("game over"),QMessageBox::Ok);
}
void MainWindow::openMusicSlot()
{    
	qDebug()<<"openMusicSlot";
	openMusicAction->setEnabled(false);    
	closeMusicAction->setEnabled(true);    
	bells->play();    
	timer->start(300000);
}
void MainWindow::soundSlot()
{    
	qDebug()<<"soundSlot";
	openMusicSlot();
}
void MainWindow::closeMusicSlot()
{    
	timer->stop();    
	bells->stop();    
	closeMusicAction->setEnabled(false);    
	openMusicAction->setEnabled(true);
}
void MainWindow::aboutSlot()
{    
	QMessageBox::information(this,tr("关于我们"),tr("散云轩出品001号，感谢使用！\n联系方式：QQ 575626476"),QMessageBox::Ok);
}
void MainWindow::createMap()
{    
	
	int i,j;   
	qDebug()<<"createMap";
	//***********第一关*****************    
	man[1][0]=8;
	man[1][1]=7;//人初始位置    
	box[1]=4;    
	for(i=0;i<MAPH;i++)        
	for(j=0;j<MAPV;j++)            
		map[1][i][j]=0; 
	map[1][4][6]=Q0100; 
	map[1][4][7]=Q0101; 
	map[1][4][8]=Q0001;    
	map[1][5][6]=Q1100;
	map[1][5][7]=GOAL;
	map[1][5][8]=Q0011;    
	map[1][6][6]=Q1100; 
	map[1][6][7]=GROUND; 
	map[1][6][8]=Q0111;    
	map[1][6][9]=Q0101; 
	map[1][6][10]=Q0101;
	map[1][6][11]=Q0001;    
	map[1][7][4]=Q0100; 
	map[1][7][5]=Q0101; 
	map[1][7][6]=Q1101;    
	map[1][7][7]=BOX; 
	map[1][7][8]=BOX; 
	map[1][7][9]=GROUND;    
	map[1][7][10]=GOAL;
	map[1][7][11]=Q0011;    
	map[1][8][4]=Q1100;
	map[1][8][5]=GOAL;
	map[1][8][6]=BOX;    
	map[1][8][7]=GROUND;
	map[1][8][8]=GROUND;
	map[1][8][9]=Q1011;    
	map[1][8][10]=Q1010;
	map[1][8][11]=Q0010;    
	map[1][9][4]=Q1000;
	map[1][9][5]=Q1010;
	map[1][9][6]=Q1010;    
	map[1][9][7]=Q1110;
	map[1][9][8]=BOX;
	map[1][9][9]=Q0011;    
	map[1][10][7]=Q1100;
	map[1][10][8]=GOAL;
	map[1][10][9]=Q0011;   
	map[1][11][7]=Q1000;
	map[1][11][8]=Q1010;
	map[1][11][9]=Q0010;   

	//***************第二关***************    
	man[2][0]=6;
	man[2][1]=9;   
	box[2]=3;    
	for(i=0;i<MAPH;i++)        
	for(j=0;j<MAPV;j++)            
		map[2][i][j]=0;    
	map[2][3][8]=Q0100;
	map[2][3][12]=Q0001;    
	map[2][3][9]=Q0101;
	map[2][3][10]=Q0101;
	map[2][3][11]=Q0101;    
	map[2][4][4]=Q0100;
	map[2][4][8]=Q1101;    
	map[2][4][5]=Q0101;
	map[2][4][6]=Q0101;
	map[2][4][7]=Q0101;    
	map[2][4][9]=GROUND;
	map[2][4][10]=GROUND;
	map[2][4][11]=GROUND;    
	map[2][4][12]=Q0011;    
	map[2][5][4]=Q1100;
	map[2][5][5]=GROUND;
	map[2][5][6]=GROUND;    
	map[2][5][7]=Q1111;
	map[2][5][8]=Q1111;
	map[2][5][9]=BOX;    
	map[2][5][10]=BOX;
	map[2][5][11]=GROUND;
	map[2][5][12]=Q0011;    
	map[2][6][4]=Q1100;
	map[2][6][12]=Q0011;    
	map[2][6][5]=GROUND;
	map[2][6][6]=GROUND;
	map[2][6][7]=GROUND;
	map[2][6][8]=BOX;    
	map[2][6][9]=GROUND;
	map[2][6][10]=GROUND;
	map[2][6][11]=GROUND;    
	map[2][7][4]=Q1100;
	map[2][7][8]=Q1011;
	map[2][7][12]=Q0010;    
	map[2][7][5]=GROUND;
	map[2][7][6]=GROUND;
	map[2][7][7]=GROUND;    
	map[2][7][9]=Q1010;
	map[2][7][10]=Q1010;
	map[2][7][11]=Q1010;    
	map[2][8][4]=Q1000;
	map[2][8][5]=Q1110;
	map[2][8][6]=Q1111;    
	map[2][8][7]=GROUND;
	map[2][8][8]=Q0011;   
	map[2][9][5]=Q1100;
	map[2][9][6]=GROUND;
	map[2][9][7]=GROUND;    
	map[2][9][8]=Q0111;
	map[2][9][9]=Q0101;
	map[2][9][10]=Q0001;    
	map[2][10][5]=Q1100;
	map[2][10][6]=GROUND;
	map[2][10][7]=GOAL;    
	map[2][10][8]=GOAL;
	map[2][10][9]=GOAL;
	map[2][10][10]=Q0011;    
	map[2][11][5]=Q1000;
	map[2][11][10]=Q0010;    
	map[2][11][6]=Q1010;
	map[2][11][7]=Q1010;
	map[2][11][8]=Q1010;
	map[2][11][9]=Q1010;    
	
	//********************第三关*********************************    
	man[3][0]=5;
	man[3][1]=8;    
	box[3]=4;    
	for(i=0;i<MAPH;i++)        
	for(j=0;j<MAPV;j++)            
	map[3][i][j]=0;    
	map[3][3][6]=Q0100;
	map[3][3][9]=Q0001;
	map[3][3][7]=Q0101;
	map[3][3][8]=Q0101;    
	map[3][4][5]=Q0100;
	map[3][4][6]=Q1101;
	map[3][4][7]=GROUND;
	map[3][4][8]=GROUND;    
	map[3][4][9]=Q0111;
	map[3][4][10]=Q0101;
	map[3][4][11]=Q0001;    
	map[3][5][5]=Q1100;
	map[3][5][6]=GOAL;
	map[3][5][7]=GOAL;
	map[3][5][8]=GROUND;    
	map[3][5][9]=BOX;
	map[3][5][10]=GROUND;
	map[3][5][11]=Q0011;    
	map[3][6][5]=Q1100;
	map[3][6][6]=GOAL;
	map[3][6][7]=GOAL;
	map[3][6][8]=GROUND;    
	map[3][6][9]=Q1111;
	map[3][6][10]=GROUND;
	map[3][6][11]=Q0011;    
	map[3][7][5]=Q1100;
	map[3][7][6]=Q1111;
	map[3][7][7]=Q1111;
	map[3][7][8]=BOX;    
	map[3][7][9]=Q1111;
	map[3][7][10]=GROUND;
	map[3][7][11]=Q0011;    
	map[3][8][5]=Q1100;
	map[3][8][6]=GROUND;
	map[3][8][7]=GROUND;
	map[3][8][8]=GROUND;    
	map[3][8][9]=Q1111;
	map[3][8][10]=GROUND;
	map[3][8][11]=Q0011;    
	map[3][9][5]=Q1100;
	map[3][9][6]=GROUND;
	map[3][9][7]=BOX;
	map[3][9][8]=GROUND;    
	map[3][9][9]=GROUND;
	map[3][9][10]=GROUND;
	map[3][9][11]=Q0011;    
	map[3][10][5]=Q1100;
	map[3][10][6]=GROUND;
	map[3][10][7]=GROUND;
	map[3][10][8]=BOX;    
	map[3][10][9]=GROUND;
	map[3][10][10]=Q1011;
	map[3][10][11]=Q0010;    
	map[3][11][5]=Q1000;
	map[3][11][6]=Q1010;
	map[3][11][7]=Q1110;
	map[3][11][8]=GROUND;    
	map[3][11][9]=GROUND;
	map[3][11][10]=Q0011;    
	map[3][12][7]=Q1000;
	map[3][12][8]=Q1010;
	map[3][12][9]=Q1010;
	map[3][12][10]=Q0010;
}
void MainWindow::levelLCDShow()
{    
	qDebug()<<"levelLCDShow";
	levelLCD->display(mainmap->levelNow);
}
void MainWindow::stepLCDShow()
{    
	qDebug()<<"stepLCDShow";
	stepLCD->display(mainmap->stepNow);
}
void MainWindow::keyPressEvent(QKeyEvent *e)
{    
	if(!(mainmap->levelNow==0))    
	{        
		switch (e->key())        
		{        
			case Qt::Key_Up:
				keyUp();
				break;        
			case Qt::Key_Left:
				keyLeft();
				break;        
			case Qt::Key_Right:
				keyRight();
				break;        
			case Qt::Key_Down:
				keyDown();
				break;        
			case Qt::Key_W:
				keyUp();
				break;        
			case Qt::Key_A:
				keyLeft();
				break;        
			case Qt::Key_D:
				keyRight();
				break;        
			case Qt::Key_S:
				keyDown();
				break;        
			default:
				break;        
		}    
	}
}
void MainWindow::keyUp()
{    
	int manx=mainmap->man_h;    
	int many=mainmap->man_v;    
	if((mainmap->mapNow[manx][many+1]==BOX)||(mainmap->mapNow[manx][many+1]==GET))    
	{        
		if(mainmap->mapNow[manx][many+2]==GOAL)        
		{            
			bool t=false;            
			if(mainmap->mapNow[manx][many+1]==BOX)            
			{                
				boxNum++;
				t=true;            
			}            
			if (map[mainmap->levelNow][manx][many]==BOX)               
				mainmap->mapNow[manx][many]=GROUND;            
			else                
				mainmap->mapNow[manx][many]=map[mainmap->levelNow][manx][many];   
			
			mainmap->mapNow[manx][many+1]=MAN;            
			mainmap->mapNow[manx][many+2]=GET;            
			mainmap->man_v++;           
			mainmap->stepNow++;            
			stepLCDShow();            
			mainmap->update();            
			if(t)                
				boxNumCheck();        
		}        
		else if(mainmap->mapNow[manx][many+2]==GROUND)        
		{            
			if(mainmap->mapNow[manx][many+1]==GET)                
				boxNum--;           
			if (map[mainmap->levelNow][manx][many]==BOX)                
				mainmap->mapNow[manx][many]=GROUND;            
			else                
				mainmap->mapNow[manx][many]=map[mainmap->levelNow][manx][many];         
			
			mainmap->mapNow[manx][many+1]=MAN;            
			mainmap->mapNow[manx][many+2]=BOX;            
			mainmap->man_v++;            
			mainmap->stepNow++;            
			stepLCDShow();            
			mainmap->update();        
		}    
	}    
	else if((mainmap->mapNow[manx][many+1]==GOAL)||(mainmap->mapNow[manx][many+1]==GROUND))    
	{        
		if (map[mainmap->levelNow][manx][many]==BOX)            
			mainmap->mapNow[manx][many]=GROUND;        
		else            
			mainmap->mapNow[manx][many]=map[mainmap->levelNow][manx][many];     
		
		mainmap->mapNow[manx][many+1]=MAN;        
		mainmap->man_v++;        
		mainmap->stepNow++;        
		stepLCDShow();        
		mainmap->update();    
	}
}
void MainWindow::keyLeft()
{    
	int manx=mainmap->man_h;    
	int many=mainmap->man_v;    
	if((mainmap->mapNow[manx-1][many]==BOX)||(mainmap->mapNow[manx-1][many]==GET))    
	{        
		if(mainmap->mapNow[manx-2][many]==GOAL)        
		{            
			bool t=false;            
			if(mainmap->mapNow[manx-1][many]==BOX)            
			{                
				boxNum++;
				t=true;            
			}            
			if (map[mainmap->levelNow][manx][many]==BOX)                
				mainmap->mapNow[manx][many]=GROUND;            
			else                
				mainmap->mapNow[manx][many]=map[mainmap->levelNow][manx][many];  
			
			mainmap->mapNow[manx-1][many]=MAN;            
			mainmap->mapNow[manx-2][many]=GET;            
			mainmap->man_h--;            
			mainmap->stepNow++;            
			stepLCDShow();            
			mainmap->update();            
			if(t)                
				boxNumCheck();        
		}        
		else if(mainmap->mapNow[manx-2][many]==GROUND)        
		{            
			if(mainmap->mapNow[manx-1][many]==GET)                
				boxNum--;            
			if (map[mainmap->levelNow][manx][many]==BOX)                
				mainmap->mapNow[manx][many]=GROUND;            
			else                
				mainmap->mapNow[manx][many]=map[mainmap->levelNow][manx][many];  
			
			mainmap->mapNow[manx-1][many]=MAN;            
			mainmap->mapNow[manx-2][many]=BOX;            
			mainmap->man_h--;            
			mainmap->stepNow++;            
			stepLCDShow();            
			mainmap->update();        
		}    
	}    
	else if((mainmap->mapNow[manx-1][many]==GOAL)||(mainmap->mapNow[manx-1][many]==GROUND))    
	{        
		if (map[mainmap->levelNow][manx][many]==BOX)            
			mainmap->mapNow[manx][many]=GROUND;        
		else            
			mainmap->mapNow[manx][many]=map[mainmap->levelNow][manx][many];        
		
		mainmap->mapNow[manx-1][many]=MAN;        
		mainmap->man_h--;        
		mainmap->stepNow++;        
		stepLCDShow();        
		mainmap->update();    
	}
}
void MainWindow::keyRight()
{    
	int manx=mainmap->man_h;    
	int many=mainmap->man_v;    
	if((mainmap->mapNow[manx+1][many]==BOX)||(mainmap->mapNow[manx+1][many]==GET))    
	{        
		if(mainmap->mapNow[manx+2][many]==GOAL)        
		{           
			bool t=false;            
			if(mainmap->mapNow[manx+1][many]==BOX)            
			{                
				boxNum++;
				t=true;            
			}            
			if (map[mainmap->levelNow][manx][many]==BOX)                
				mainmap->mapNow[manx][many]=GROUND;            
			else                
				mainmap->mapNow[manx][many]=map[mainmap->levelNow][manx][many];    
			
			mainmap->mapNow[manx+1][many]=MAN;            
			mainmap->mapNow[manx+2][many]=GET;            
			mainmap->man_h++;           
			mainmap->stepNow++;            
			stepLCDShow();            
			mainmap->update();            
		if(t)                
			boxNumCheck();        
		}        
		else if(mainmap->mapNow[manx+2][many]==GROUND)        
		{            
			if(mainmap->mapNow[manx+1][many]==GET)                
				boxNum--;            
			if (map[mainmap->levelNow][manx][many]==BOX)                
				mainmap->mapNow[manx][many]=GROUND;            
			else                
				mainmap->mapNow[manx][many]=map[mainmap->levelNow][manx][many];    
			
			mainmap->mapNow[manx+1][many]=MAN;            
			mainmap->mapNow[manx+2][many]=BOX;            
			mainmap->man_h++;           
			mainmap->stepNow++;            
			stepLCDShow();           
			mainmap->update();        
		}    
	}    
	else if((mainmap->mapNow[manx+1][many]==GOAL)||(mainmap->mapNow[manx+1][many]==GROUND))    
	{       
		if (map[mainmap->levelNow][manx][many]==BOX)            
		mainmap->mapNow[manx][many]=GROUND;        
		else            
		mainmap->mapNow[manx][many]=map[mainmap->levelNow][manx][many];        
		mainmap->mapNow[manx+1][many]=MAN;        
		mainmap->man_h++;        
		mainmap->stepNow++;        
		stepLCDShow();        
		mainmap->update();    
	}
}	
void MainWindow::keyDown()
{    

	int manx=mainmap->man_h;    
	int many=mainmap->man_v;    
	if((mainmap->mapNow[manx][many-1]==BOX)||(mainmap->mapNow[manx][many-1]==GET))    
	{        
		if(mainmap->mapNow[manx][many-2]==GOAL)        
		{            
			bool t=false;            
		if(mainmap->mapNow[manx][many-1]==BOX)            
		{                
			boxNum++;
			t=true;            
		}           
		if (map[mainmap->levelNow][manx][many]==BOX)               
			mainmap->mapNow[manx][many]=GROUND;            
		else               
			mainmap->mapNow[manx][many]=map[mainmap->levelNow][manx][many];            
		mainmap->mapNow[manx][many-1]=MAN;           
		mainmap->mapNow[manx][many-2]=GET;            
		mainmap->man_v--;            
		mainmap->stepNow++;            
		stepLCDShow();            
		mainmap->update();            
		if(t)                
			boxNumCheck();        
		}        
		else if(mainmap->mapNow[manx][many-2]==GROUND)        
		{            
			if(mainmap->mapNow[manx][many-1]==GET)                
				boxNum--;            
			if (map[mainmap->levelNow][manx][many]==BOX)                
				mainmap->mapNow[manx][many]=GROUND;            
			else                
				mainmap->mapNow[manx][many]=map[mainmap->levelNow][manx][many];            
			mainmap->mapNow[manx][many-1]=MAN;            
			mainmap->mapNow[manx][many-2]=BOX;            
			mainmap->man_v--;            
			mainmap->stepNow++;            
			stepLCDShow();            
			mainmap->update();        
		}    
	}    
	else if((mainmap->mapNow[manx][many-1]==GOAL)||(mainmap->mapNow[manx][many-1]==GROUND))    
	{        
		if (map[mainmap->levelNow][manx][many]==BOX)            
			mainmap->mapNow[manx][many]=GROUND;       
		else            
			mainmap->mapNow[manx][many]=map[mainmap->levelNow][manx][many];        
		mainmap->mapNow[manx][many-1]=MAN;        
		mainmap->man_v--;        
		mainmap->stepNow++;        
		stepLCDShow();        
		mainmap->update();    
	}
}
void MainWindow::boxNumCheck()
{    
	qDebug()<<"boxNumCheck"<<boxNum<<"box level "<<box[mainmap->levelNow];
	if(mainmap->levelNow==1)
		box[mainmap->levelNow]=4;
	else if(mainmap->levelNow == 2)
		box[mainmap->levelNow]=3;
	else if(mainmap->levelNow == 3)
		box[mainmap->levelNow]=4;
	
	if(boxNum==box[mainmap->levelNow])    
	{        
		//endGameAction->setEnabled(false);        
		//restartGameAction->setEnabled(false);        
		restartButton->setEnabled(false);  
		
		if(mainmap->levelNow == LEVELNUM)  
		{            
			QMessageBox::information(this,tr("Congratulations clearance"),tr("Congratulations, you have clearance!"),QMessageBox::Ok);            
			mainmap->levelNow=0;            
			mainmap->stepNow=0;            
			boxNum=0;            
			mainmap->BeginOrEnd=1;            
			mainmap->update();        
		}       
		else       
		{            
			QMessageBox::information(this,tr("Congratulations clearance"),tr("Congratulations, you have completed this Off! Proceed to the next level"),QMessageBox::Ok);            
			startGame(mainmap->levelNow+1);        
		}    
	}
} 
MainWindow::~MainWindow()
{
}
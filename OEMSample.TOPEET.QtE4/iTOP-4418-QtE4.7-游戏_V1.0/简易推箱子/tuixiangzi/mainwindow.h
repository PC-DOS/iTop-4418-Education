#ifndef MAINWINDOW_H 
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QSpacerItem>
#include <QMessageBox>
#include <QKeyEvent>
#include <QSound>
#include <QTimer>
#include <QPushButton>
#include "mainpaint.h"
//#include "define.h"
//#include "choosedlg.h"
//class mapPaint;


#define Q0000 	0
#define Q0001 	1
#define Q0010 	2
#define Q0011 	 3
#define Q0100 	4
#define Q0101 	5
#define  BOX    	6
#define Q0111 	7
#define Q1000 	8
#define GOAL 	 9
#define Q1010 	10
#define Q1011 	11
#define Q1100 	12
#define Q1101  	13
#define Q1110 	14
#define Q1111 	15
#define GROUND 	16
#define  GET 		17
#define  MAN 	18


#define MAPH 13
#define MAPV  14


class MainWindow : public QMainWindow
{    
	Q_OBJECT
public:    
	 MainWindow(QWidget *parent = 0);
	 ~MainWindow();
	//*******************菜单栏************************    
	QMenu *gameMenu;//游戏菜单    
	QMenu *musicMenu;//音乐菜单    
	QMenu *helpMenu;//帮助    
	QAction *beginGameAction;//开始游戏    
	QAction *chooseGameAction;//选择关卡    
	QAction *restartGameAction;//重新开始    
	QAction *endGameAction;//结束游戏    
	QAction *openMusicAction;//打开音乐    
	QAction *closeMusicAction;//关闭音乐    
	QAction *aboutAction;//关于我们    
	
	//******************数据设计*************************    
	//int map[LEVELNUM][MAPH][MAPV];    
	//int man[LEVELNUM][2];    
	//int box[LEVELNUM];  
	int map[4][MAPH][MAPV];
	int man[4][2];
	int box[4];
	int boxNum;    
	int chooseNum;    
	QSound *bells;    
	QTimer *timer;    
	
	//******************界面布局****************************    
	QWidget *widget;   
	 mapPaint *mainmap;   
	  QLabel *levelLabel;    
	  QLabel *stepLabel;    
	  QLCDNumber *levelLCD;    
	  QLCDNumber *stepLCD;    
	  QPushButton *restartButton;
	  QPushButton *beginButton;
	  
	void createMap();
	void createMenu();    
	void createAction();
	  //*************游戏控制**********************    
	  
	  void keyPressEvent(QKeyEvent *e);    
	  void keyUp();    
	  void keyLeft();    
	  void keyRight();    
	  void keyDown();   
	  void boxNumCheck();    
	  void startGame(int x);
public slots:
	//******************菜单栏——槽**********************    
		void beginGameSlot();    
		void chooseGameSlot();    
		void restartGameSlot();    
		void endGameSlot();    
		void openMusicSlot();    
		void closeMusicSlot();    
		void aboutSlot();    
		void levelLCDShow();//关卡显示    
		void stepLCDShow();//步数显示    
		void soundSlot();
};

#endif  // MAINWINDOW_H
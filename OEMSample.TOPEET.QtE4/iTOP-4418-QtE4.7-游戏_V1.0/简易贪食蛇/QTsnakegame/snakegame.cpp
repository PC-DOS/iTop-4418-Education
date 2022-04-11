#include "snakegame.h"
#include <QTimer>
#include <QLabel>
#include <QTime>
#include <QMessageBox>
//enum Direction{D_UP,D_DOWN,D_LEFT,D_RIGHT};
SnakeGame::SnakeGame(){
    qsrand(QTime::currentTime().msec());
    footlen=40;
    this->resize(700,600);
    snake.push_back(GetFood());
    food=GetFood();
    dire=D_RIGHT;
    pl=300;
    maxlen=5;
    timer=new QTimer();
    timer->setInterval(pl);
    timer->start();
    //连接定时器到槽函数
    connect(timer,SIGNAL(timeout()),this,SLOT(SnakeMove()));
}
//控制蛇移动函数 调用一次 根据方向移动一个步长
void SnakeGame::SnakeMove(){
     //获得蛇头的坐标
    int sx=snake[0]->x();
    int sy=snake[0]->y();
    //判断食物是否和蛇头重合
    if(sx==food->x() && sy==food->y()){
        snake.push_back(food);
        //产生新食物
        food=GetFood();
    }
    //元素从后往前移动 到前一个元素的位置
    for(int i=snake.size()-1;i>0;i--){
        snake[i]->move(snake[i-1]->x(),snake[i-1]->y());

    }
    if(maxlen<=snake.size()){
        QMessageBox msg;
        msg.setText("snake is equal maxlen,game over?");
        msg.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        if(msg.exec()==QMessageBox::Yes){
            this->close();
        }else{
            maxlen=maxlen*2+1;
            timer->setInterval(pl/2);
        }
    }
    //蛇是否撞墙
    if(sx<0||sy<0||sx>=this->width()|| sy>=this->height()){
        QMessageBox  msg;
        msg.setText("game over!");
        msg.exec();
        this->close();
    }

    // 根据方向获得蛇头新坐标
    switch(dire){
    case D_UP:
        sy-=footlen;break;
    case D_DOWN:
        sy+=footlen;break;
    case D_LEFT:
        sx-=footlen;break;
    case D_RIGHT:
        sx+=footlen;break;
    }
    //蛇头移动到新坐标
    snake[0]->move(sx,sy);

}

  //产生新食物的函数
QLabel* SnakeGame::GetFood(){
    food=new QLabel(this);
    food->resize(footlen,footlen);
    food->setAutoFillBackground(true);
    //设置颜色  颜色随即
    food->setPalette(QPalette(QColor(qrand()%256,qrand()%256,qrand()%256)));
    //位置随即  步长的整数倍 界面范围以内
    int w=(this->width())-footlen;
    int h=(this->height())-footlen;
    food->move((qrand()%w)/footlen*footlen,(qrand()%h)/footlen*footlen);
    food->show();
    return food;
}
//控制蛇的方向 键盘事件处理函数
void SnakeGame::keyPressEvent(QKeyEvent *e){
    switch(e->key()){
    case Qt::Key_Up:
        dire=D_UP;break;
    case Qt::Key_Down:
        dire=D_DOWN;break;
    case Qt::Key_Left:
        dire=D_LEFT;break;
    case Qt::Key_Right:
        dire=D_RIGHT;break;
    }
}

SnakeGame::~SnakeGame()
{

}

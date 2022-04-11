#ifndef SNAKEGAME_H
#define SNAKEGAME_H
#include <QList>
#include <QDialog>
#include <QKeyEvent>
#include <QLabel>
#include <QTimer>
enum Direction{D_UP,D_DOWN,D_LEFT,D_RIGHT};
class SnakeGame:public QDialog{
    Q_OBJECT
    //游戏中的蛇  push_back  [0]
    QList<QLabel*>  snake;
    //食物
    QLabel *food;
    //蛇的方向
    Direction dire;
    //蛇的步长
    int footlen;
    //控制频率 定时器
    QTimer *timer;
    //蛇的最大长度
    int maxlen;
    int pl;
public:
    SnakeGame();
    ~SnakeGame();
    //功能性函数
    //控制蛇移动函数 调用一次 根据方向移动一个步长
public slots:
    void SnakeMove();
    //产生新食物的函数
public:
    QLabel* GetFood();
    //控制蛇的方向 键盘事件处理函数
    void keyPressEvent(QKeyEvent *e);


};
#endif // SNAKEGAME_H

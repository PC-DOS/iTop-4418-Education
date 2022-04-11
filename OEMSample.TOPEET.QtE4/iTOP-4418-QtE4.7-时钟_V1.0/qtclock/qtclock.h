#ifndef QTCLOCK_H
#define QTCLOCK_H

#include <QWidget>

class qtclock : public QWidget
{
    Q_OBJECT

public:
    qtclock(QWidget *parent = 0);


protected:
//重绘用的事件处理函式
    void paintEvent(QPaintEvent *event);
};

#endif // QTCLOCK_H

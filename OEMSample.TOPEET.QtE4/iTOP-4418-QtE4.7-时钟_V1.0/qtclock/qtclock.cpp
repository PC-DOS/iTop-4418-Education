#include "qtclock.h"
#include <QtGui>

qtclock::qtclock(QWidget *parent) :QWidget(parent)
{
//声明一个定时器
    QTimer *timer = new QTimer(this);
//连接信号与槽
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
 //设置窗体名称与大小
    setWindowTitle(tr("qtclock"));
    resize(200, 200);
 }

 void qtclock::paintEvent(QPaintEvent *)
 {
 //下面三个数组用来定义表针的三个顶点，以便后面的填充
     static const QPoint hourHand[3] = {
         QPoint(3, 8),
         QPoint(-3, 8),
         QPoint(0, -40)
     };
    static const QPoint minuteHand[3] = {
         QPoint(3, 8),
         QPoint(-3, 8),
         QPoint(0, -70)
      };
     static const QPoint secondHand[3] = {
         QPoint(3, 8),
         QPoint(-3, 8),
         QPoint(0, -90)
     };
//填充表针的颜色
     QColor hourColor(127, 0, 127);
     QColor minuteColor(0, 127, 127, 191);
     QColor secondColor(127, 127,0,120);
//绘制的范围
     int side = qMin(width(), height());
//获取当前的时间
     QTime time = QTime::currentTime();
//声明用来绘图用的“画家”
     QPainter painter(this);
     painter.setRenderHint(QPainter::Antialiasing);
//重新定位坐标起始点点
     painter.translate(width() / 2, height() / 2);
//设定花布的边界
     painter.scale(side / 200.0, side / 200.0);
//填充时针，不需要边线所以NoPen
     painter.setPen(Qt::NoPen);
//画刷颜色设定
     painter.setBrush(hourColor);
//保存“画家”的状态
     painter.save();
//将“画家”（的”视角“）根据时间参数转移
     painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
//填充时针的区域
     painter.drawConvexPolygon(hourHand, 3);
//恢复填充前“画家”的状态
     painter.restore();
//下面画表示小时的刻度，此时要用到画笔（因为要划线）
     painter.setPen(hourColor);
//十二个刻度，循环下就好了
     for (int i = 0; i < 12; ++i) {
        //没次都是这样，先画跳线，再转个角
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }

//后面的跟前面的类似，分别绘制了分针和秒针，及相应的刻度，我就不废话了

     painter.setPen(Qt::NoPen);

     painter.setBrush(minuteColor);


     painter.save();
     painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
     painter.drawConvexPolygon(minuteHand, 3);
     painter.restore();

     painter.setPen(minuteColor);

     for (int j = 0; j < 60; ++j) {
         if ((j % 5) != 0)
             painter.drawLine(92, 0, 96, 0);
         painter.rotate(6.0);
     }
     painter.setPen(Qt::NoPen);
     painter.setBrush(secondColor);
     painter.save();
     painter.rotate(6.0*time.second());
     painter.drawConvexPolygon(secondHand,3);
     painter.restore();
}

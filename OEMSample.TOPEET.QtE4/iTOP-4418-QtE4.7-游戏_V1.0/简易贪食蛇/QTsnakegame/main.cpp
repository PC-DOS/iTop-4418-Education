#include "snakegame.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    QFont font;
    font.setPointSize(4);
    font.setBold(false);
    a.setFont(font);
    SnakeGame sg;
    sg.show();

    return a.exec();
}

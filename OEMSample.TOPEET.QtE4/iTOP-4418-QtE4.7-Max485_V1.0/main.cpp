#include "rs485.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    rs485 w;
    w.show();

    return a.exec();
}

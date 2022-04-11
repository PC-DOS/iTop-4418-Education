#include "qtclock.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFont font;
    font.setPointSize(4);
    font.setBold(false);
    app.setFont(font);
    qtclock qtclock;
    qtclock.show();

    return app.exec();
}

#include "networktcp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font;
    font.setPointSize(12);
    font.setFamily(("wenquanyi"));
    font.setBold(false);
    a.setFont(font);

    NetworkTcp w;
    w.show();

    return a.exec();
}

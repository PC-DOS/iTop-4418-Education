 #include <QApplication>
 #include <QLabel>
 #include "mainwindow.h"

 int main(int argc, char **argv)
 {
  QApplication app(argc, argv);

  QFont font;
  font.setPointSize(4);
  font.setBold(false);
  app.setFont(font);
  MainWindow* mygl = new MainWindow;
  mygl->show();
  return app.exec();
 }

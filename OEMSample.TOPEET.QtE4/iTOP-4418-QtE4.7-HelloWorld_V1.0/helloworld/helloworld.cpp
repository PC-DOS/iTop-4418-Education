#include "helloworld.h"
#include "ui_helloworld.h"

helloworld::helloworld(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::helloworld)
{
    ui->setupUi(this);
}

helloworld::~helloworld()
{
    delete ui;
}

#include "qtwatchdog.h"
#include "ui_qtwatchdog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/watchdog.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "qprocess.h"
#include <QProcess>

static int fd;
qtwatchdog::qtwatchdog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qtwatchdog)
{
    ui->setupUi(this);

    fd = open("/dev/watchdog", O_WRONLY);

    if(fd<0)
    {
    perror("open  watchdog failed!");
    exit(1);
    }
}
qtwatchdog::~qtwatchdog()
{
    delete ui;
}

void qtwatchdog::on_start_pushButton_clicked()
{
    ioctl(fd, WDIOC_SETTIMEOUT, 10);
}


void qtwatchdog::on_feed_pushButton_clicked()
{
    ioctl(fd, WDIOC_KEEPALIVE);
}

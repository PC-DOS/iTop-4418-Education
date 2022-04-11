#ifndef QTWATCHDOG_H
#define QTWATCHDOG_H

#include <QWidget>

namespace Ui {
class qtwatchdog;
}

class qtwatchdog : public QWidget
{
    Q_OBJECT

public:
    explicit qtwatchdog(QWidget *parent = 0);
    ~qtwatchdog();

private:
    Ui::qtwatchdog *ui;

public slots:
    void on_start_pushButton_clicked();
    void on_feed_pushButton_clicked();
};

#endif // QTWATCHDOG_H

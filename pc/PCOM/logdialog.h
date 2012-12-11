#ifndef LOGDIALOG_H
#define LOGDIALOG_H

#include <QDialog>
#include "uartdialog.h"
#include "netdialog.h"

namespace Ui {
class LogDialog;
}

class LogDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LogDialog(QWidget *parent = 0);
    ~LogDialog();
    
private slots:
    void LoginWindow(void);

    void on_uartbutton_clicked();

    void on_netbutton_clicked();

private:
    Ui::LogDialog *ui;

    /* 串口和网络对象*/
    UartDialog *u;
    NetDialog *n;
};

#endif // LOGDIALOG_H

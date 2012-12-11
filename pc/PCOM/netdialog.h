#ifndef NETDIALOG_H
#define NETDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class NetDialog;
}

class NetDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit NetDialog(QWidget *parent = 0);
    ~NetDialog();
    
private slots:
    void on_netexitbutton_clicked();

    void on_netlogbutton_clicked();

signals:
    void NetShowLogin(void);

private:
    Ui::NetDialog *ui;

    /* 主界面*/
    MainWindow *m;
};

#endif // NETDIALOG_H

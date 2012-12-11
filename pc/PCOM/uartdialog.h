#ifndef UARTDIALOG_H
#define UARTDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class UartDialog;
}

class UartDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit UartDialog(QWidget *parent = 0);
    ~UartDialog();
    
private slots:
    void on_uartreturnbutton_clicked();

    void on_uartlogbutton_clicked();

signals:
    void UartShowLogin(void);

private:
    Ui::UartDialog *ui;
    MainWindow *m;
};

#endif // UARTDIALOG_H

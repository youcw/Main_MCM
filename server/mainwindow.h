#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QDate>
#include <QDateTime>
#include <QTextCodec>
#include <QMessageBox>
#include <QPainter>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define TEMP_DEV                        "/dev/ds18b20"
#define IOCTL_DS18B20_S_RESET           0x10009
#define IOCTL_DS18B20_S_START           0x10010
#define IOCTL_DS18B20_S_BIT             0x10011

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void paintEvent(QPaintEvent *);

private slots:
    void buttonfunction(void);
    void printclock(void);
    void printtemp(void);
    void get_ds18b20_temperature(void);

private:
    Ui::MainWindow *ui;
    int init_device(int *);

private:
    int fd;
    double tempinfo;
};


#endif // MAINWINDOW_H

#include "uartdialog.h"
#include "ui_uartdialog.h"
#include "logdialog.h"
#include "msg.h"
#include "mainwindow.h"

UartDialog::UartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UartDialog)
{
    ui->setupUi(this);
}

UartDialog::~UartDialog()
{
    delete ui;
}

void UartDialog::on_uartreturnbutton_clicked()
{
    this->close();
    emit UartShowLogin();
}

void UartDialog::on_uartlogbutton_clicked()
{
    m=new MainWindow;
    char tmpbuf[20]="/dev/";
    strcat(tmpbuf,ui->UartComboBox->currentText().toLocal8Bit());
    strcpy(m->UartBuf,tmpbuf);
    m->TransFlag=TRANSFER_UART;
    this->close();
    m->init();
    m->show();
    printf("uart=%s\n",m->UartBuf);
}

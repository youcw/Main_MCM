#include "netdialog.h"
#include "ui_netdialog.h"
#include "mainwindow.h"
#include "logdialog.h"

NetDialog::NetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetDialog)
{
    ui->setupUi(this);
}

NetDialog::~NetDialog()
{
    delete ui;
}

void NetDialog::on_netexitbutton_clicked()
{
    this->close();
    emit NetShowLogin();
}

void NetDialog::on_netlogbutton_clicked()
{
    printf("123\n");
    m=new MainWindow;
    strcpy(m->IpBuf,ui->netlineEdit->displayText().toLocal8Bit());
    m->TransFlag=TRANSFER_NET;
    this->close();
    m->init();
    m->show();
    printf("ip=%s\n",m->IpBuf);
}

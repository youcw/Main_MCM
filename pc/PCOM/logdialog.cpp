#include "logdialog.h"
#include "ui_logdialog.h"
#include "uartdialog.h"

LogDialog::LogDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogDialog)
{
    ui->setupUi(this);

    u = new UartDialog(this);
    n = new NetDialog(this);

   connect(n, SIGNAL(NetShowLogin()), this, SLOT(LoginWindow()));
   connect(u, SIGNAL(UartShowLogin()), this, SLOT(LoginWindow()));
}

LogDialog::~LogDialog()
{
    delete ui;
}

void LogDialog::LoginWindow(void)
{
    this->show();
}

void LogDialog::on_uartbutton_clicked()
{

    this->hide();
    u->show();
}

void LogDialog::on_netbutton_clicked()
{
    this->hide();
    n->show();
}

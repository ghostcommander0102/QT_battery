#include "dialog.h"
#include "ui_dialog.h"
#include "batterychoosedialog.h"
Dialog::Dialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::centralWidget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    QApplication::quit();
}


void Dialog::on_loginButton_clicked()
{
    BatteryChooseDialog *dlg = new BatteryChooseDialog();
    dlg->show();
    this->close();
}


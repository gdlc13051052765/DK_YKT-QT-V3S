#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_emitBtn_clicked()
{
    QString str = ui->EmitLineEdit->text();
    emit getStr(str);
}

void Dialog::mainWidgetStr(QString &str)
{
    ui->ReceiveLineEdit->setText(str);
}

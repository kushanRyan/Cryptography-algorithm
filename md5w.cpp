#include "md5w.h"
#include"complete.h"
#include"CryptographicAlgorithmsH/MD5.h"
#include "ui_md5w.h"

md5w::md5w(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::md5w)
{
    ui->setupUi(this);
}

md5w::~md5w()
{
    delete ui;
}

void md5w::on_endExcute_clicked()
{
        this->close();
}

void md5w::on_excute_clicked()
{
    QString message =ui->message->text();
    string a="",b="";
    MD5Interface(message.toStdString(),a,b);
    ui->c16->setText(QString::fromStdString(a));
    ui->cipher32->setText(QString::fromStdString(b));
    complete* com=new complete();
    com->show();
}

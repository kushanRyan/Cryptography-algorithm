#include "sha1w.h"
#include"CryptographicAlgorithmsH/SHA1.h"
#include"complete.h"
#include "ui_sha1w.h"
#include<fstream>

sha1w::sha1w(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sha1w)
{
    ui->setupUi(this);
}

sha1w::~sha1w()
{
    delete ui;
}

void sha1w::on_endExcute_clicked()
{
    this->close();
}


void sha1w::on_excute_clicked()
{
    QString mes=ui->message->text();
    string result;
    SHA1Interface(mes.toStdString());
    ifstream in;in.open("D://tests//sha1//digesttext.txt", ios::binary);
    in>>result;
    ui->digest->setText(QString::fromStdString(result));
    complete* com=new complete();
    com->show();
}

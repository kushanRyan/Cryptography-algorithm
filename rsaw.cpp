#include "rsaw.h"
#include"complete.h"
#include"CryptographicAlgorithmsH/RSA.h"
#include "ui_rsaw.h"
#include <string>
#include "complete.h"
using namespace std;
rsaw::rsaw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rsaw)
{
    ui->setupUi(this);
}

rsaw::~rsaw()
{
    delete ui;
}

void rsaw::on_endExcute_clicked()
{
        this->close();
}

void rsaw::on_excute_clicked()
{
    QString message=ui->message->text();
    QString pub,pri;
    int e,d,n;
    RSAInterface(message,e,d,n);
    ui->e->setText(QString::number(e,'g',6));
    ui->d->setText(QString::number(d,'g',6));
    ui->n->setText(QString::number(n,'g',6));
    ui->n2->setText(QString::number(n,'g',6));
    complete* com=new complete();
    com->show();
}

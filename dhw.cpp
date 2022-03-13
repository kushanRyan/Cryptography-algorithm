#include "dhw.h"
#include "ui_dhw.h"
#include"complete.h"
#include"CryptographicAlgorithmsH/DH.h"
dhw::dhw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dhw)
{
    ui->setupUi(this);
}

dhw::~dhw()
{
    delete ui;
}

void dhw::on_endExcute_clicked()
{
        this->close();
}

void dhw::on_excute_clicked()
{
    int p,a,b,ya,yb,ka,kb;
    DHInterface(p,a,b,ya,yb,ka,kb);
    ui->p->setText(QString::number(p,'g',6));ui->a->setText(QString::number(a,'g',6));ui->b->setText(QString::number(b,'g',6));
    ui->ya->setText(QString::number(ya,'g',6));ui->yb->setText(QString::number(yb,'g',6));ui->ka->setText(QString::number(ka,'g',6));
    ui->kb->setText(QString::number(kb,'g',6));
    complete* com=new complete();
    com->show();
}

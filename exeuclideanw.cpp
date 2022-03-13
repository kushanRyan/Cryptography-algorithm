#include "exeuclideanw.h"
#include "ui_exeuclideanw.h"
#include "CryptographicAlgorithmsH/euclidean.h"
#include <qtextcodec.h>
#include <iostream>
using namespace std;
exeuclideanw::exeuclideanw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::exeuclideanw)
{
    ui->setupUi(this);
}

exeuclideanw::~exeuclideanw()
{
    delete ui;
}

void exeuclideanw::on_endExcute_clicked()
{
        this->close();
}

void exeuclideanw::on_excute_clicked()
{
    QString a=ui->numbera->text();
    QString b=ui->numberb->text();
    int a1,b1;
    exGcd(a.toInt(),b.toInt(),a1,b1);
    cout<<a1<<" "<<b1<<endl;
    QString z,j;
    z=QString::number(a1,'g',6);
    j=QString::number(b1,'g',6);
    ui->result->setText(z);
    ui->result2->setText(j);
}

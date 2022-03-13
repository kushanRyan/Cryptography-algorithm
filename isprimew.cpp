#include "isprimew.h"
#include "ui_isprimew.h"
#include"CryptographicAlgorithmsH/PrimalityTesting.h"
isprimew::isprimew(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::isprimew)
{
    ui->setupUi(this);
}

isprimew::~isprimew()
{
    delete ui;
}

void isprimew::on_endExcute_clicked()
{
        this->close();
}

void isprimew::on_excuter_clicked()
{
    QString number=ui->number->text();
    int results=PrimalityTestingInterface(number.toInt());
    QString bol="no";
    if(results){
        bol="yes";
    }
    ui->finresult->setText(bol);
}

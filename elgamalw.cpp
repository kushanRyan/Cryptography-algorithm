#include "elgamalw.h"
#include "ui_elgamalw.h"
#include "elgamalwarn.h"
#include"CryptographicAlgorithmsH/Elgamal.h"
elgamalw::elgamalw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::elgamalw)
{
    ui->setupUi(this);
}

elgamalw::~elgamalw()
{
    delete ui;
}

void elgamalw::on_endExcute_clicked()
{
        this->close();
}

void elgamalw::on_excute_clicked()
{
    int c1,c2,message,plain,privateKey,publicKey;
    if(ui->message->text().size()==1){
        ElgamalInterface(c1,c2,message,plain,privateKey,publicKey);
        ui->c1->setText(QString::number(c1,'g',6));ui->c2->setText(QString::number(c2,'g',6));
        ui->message->setText(QString::number(message,'g',6));
        ui->plain->setText(QString::number(message,'g',6));ui->privateKey->setText(QString::number(privateKey,'g',6));
        ui->publicKey->setText(QString::number(publicKey,'g',6));
    }else{
        elgamalwarn* warn=new elgamalwarn();
        warn->show();
    }
}

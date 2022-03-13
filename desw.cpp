#include "desw.h"
#include "ui_desw.h"
#include "deswarn.h"
#include "CryptographicAlgorithmsH/DES.h"
#include"complete.h"
desw::desw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::desw)
{
    ui->setupUi(this);
}

desw::~desw()
{
    delete ui;
}

void desw::on_endExcute_clicked()
{
        this->close();
}

void desw::on_excute_clicked()
{
    QString mes=ui->message->text();
    QString key=ui->key->text();
    if(key.size()!=8){
        deswarn* warn=new deswarn();
        warn->show();
    }else{
        DESInterface(mes.toStdString(),key.toStdString());
        complete* com=new complete();
        com->show();
    }
}

#include "aesw.h"
#include "ui_aesw.h"
#include "complete.h"
#include "aeswarn.h"
#include "CryptographicAlgorithmsH/AES.h"
aesw::aesw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::aesw)
{
    ui->setupUi(this);
}

aesw::~aesw()
{
    delete ui;
}

void aesw::on_endExcute_clicked()
{
    this->close();
}

void aesw::on_excute_clicked()
{
    QString a=ui->message->text();
    QString k=ui->key->text();
    if(k.size()==16){
        excuteAES(a.toStdString(),k.toStdString());
        complete* com=new complete();
        com->show();
    }else{
        aeswarn* warn=new aeswarn();
        warn->show();
    }
}

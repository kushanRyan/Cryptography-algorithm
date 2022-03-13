#include "euclideanw.h"
#include "ui_euclideanw.h"
#include "CryptographicAlgorithmsH/euclidean.h"
euclideanw::euclideanw(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::euclideanw)
{
    ui->setupUi(this);
}

euclideanw::~euclideanw()
{
    delete ui;
}

void euclideanw::on_endExcute_clicked()
{
        this->close();
}

void euclideanw::on_excute_clicked()
{
    QString n = ui->numberN->text();
    QString m = ui->numberM->text();
    int result = normalGcd(n.toInt(),m.toInt());
    ui->numberResult->setText(QString::number(result,'g',6));
}

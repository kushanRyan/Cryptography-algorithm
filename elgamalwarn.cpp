#include "elgamalwarn.h"
#include "ui_elgamalwarn.h"

elgamalwarn::elgamalwarn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::elgamalwarn)
{
    ui->setupUi(this);
}

elgamalwarn::~elgamalwarn()
{
    delete ui;
}

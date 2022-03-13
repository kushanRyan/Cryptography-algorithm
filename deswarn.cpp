#include "deswarn.h"
#include "ui_deswarn.h"

deswarn::deswarn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::deswarn)
{
    ui->setupUi(this);
}

deswarn::~deswarn()
{
    delete ui;
}

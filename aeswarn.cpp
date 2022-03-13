#include "aeswarn.h"
#include "ui_aeswarn.h"

aeswarn::aeswarn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::aeswarn)
{
    ui->setupUi(this);
}

aeswarn::~aeswarn()
{
    delete ui;
}

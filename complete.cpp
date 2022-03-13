#include "complete.h"
#include "ui_complete.h"

complete::complete(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::complete)
{
    ui->setupUi(this);
}

complete::~complete()
{
    delete ui;
}

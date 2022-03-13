#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "euclideanw.h"
#include "exeuclideanw.h"
#include "isprimew.h"
#include "desw.h"
#include "aesw.h"
#include "dhw.h"
#include "rsaw.h"
#include "elgamalw.h"
#include "md5w.h"
#include "sha1w.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_EuclideanInterface_clicked(){
    euclideanw* a =new euclideanw();
    a->show();
}

void MainWindow::on_exEuclideanInterface_clicked()
{
    exeuclideanw* a = new exeuclideanw();
    a->show();
}

void MainWindow::on_isprimeInterface_clicked()
{
    isprimew* a =new isprimew();
    a->show();
}

void MainWindow::on_DESInterface_clicked()
{
    desw* a = new desw();
    a->show();
}

void MainWindow::on_AESInterface_clicked()
{
    aesw* a = new aesw();
    a->show();
}

void MainWindow::on_DHInterface_clicked()
{
    dhw* a = new dhw();
    a->show();
}

void MainWindow::on_RSAInterface_clicked()
{
    rsaw* a = new rsaw();
    a->show();
}

void MainWindow::on_ElgamalInterface_clicked()
{
    elgamalw* a = new elgamalw();
    a->show();
}

void MainWindow::on_MD5Interface_clicked()
{
    md5w* a = new md5w();
    a->show();
}

void MainWindow::on_SHA1Interface_clicked()
{
    sha1w* a = new sha1w();
    a->show();
}

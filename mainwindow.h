#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_EuclideanInterface_clicked();

    void on_exEuclideanInterface_clicked();

    void on_isprimeInterface_clicked();

    void on_DESInterface_clicked();

    void on_AESInterface_clicked();

    void on_DHInterface_clicked();

    void on_RSAInterface_clicked();

    void on_ElgamalInterface_clicked();

    void on_MD5Interface_clicked();

    void on_SHA1Interface_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

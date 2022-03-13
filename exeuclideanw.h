#ifndef EXEUCLIDEANW_H
#define EXEUCLIDEANW_H

#include <QWidget>

namespace Ui {
class exeuclideanw;
}

class exeuclideanw : public QWidget
{
    Q_OBJECT

public:
    explicit exeuclideanw(QWidget *parent = 0);
    ~exeuclideanw();

private slots:
    void on_endExcute_clicked();

    void on_excute_clicked();

private:
    Ui::exeuclideanw *ui;
};

#endif // EXEUCLIDEANW_H

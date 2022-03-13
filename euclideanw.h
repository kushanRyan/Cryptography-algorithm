#ifndef EUCLIDEANW_H
#define EUCLIDEANW_H

#include <QWidget>

namespace Ui {
class euclideanw;
}

class euclideanw : public QWidget
{
    Q_OBJECT

public:
    explicit euclideanw(QWidget *parent = 0);
    ~euclideanw();

private slots:
    void on_endExcute_clicked();

    void on_excute_clicked();

private:
    Ui::euclideanw *ui;
};

#endif // EUCLIDEANW_H

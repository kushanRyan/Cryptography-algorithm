#ifndef DESW_H
#define DESW_H

#include <QWidget>

namespace Ui {
class desw;
}

class desw : public QWidget
{
    Q_OBJECT

public:
    explicit desw(QWidget *parent = 0);
    ~desw();

private slots:
    void on_endExcute_clicked();

    void on_excute_clicked();

private:
    Ui::desw *ui;
};

#endif // DESW_H

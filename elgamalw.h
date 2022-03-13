#ifndef ELGAMALW_H
#define ELGAMALW_H

#include <QWidget>

namespace Ui {
class elgamalw;
}

class elgamalw : public QWidget
{
    Q_OBJECT

public:
    explicit elgamalw(QWidget *parent = 0);
    ~elgamalw();

private slots:
    void on_endExcute_clicked();

    void on_excute_clicked();

private:
    Ui::elgamalw *ui;
};

#endif // ELGAMALW_H

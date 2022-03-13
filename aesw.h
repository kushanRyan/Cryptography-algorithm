#ifndef AESW_H
#define AESW_H

#include <QWidget>

namespace Ui {
class aesw;
}

class aesw : public QWidget
{
    Q_OBJECT

public:
    explicit aesw(QWidget *parent = 0);
    ~aesw();

private slots:
    void on_endExcute_clicked();

    void on_excute_clicked();

private:
    Ui::aesw *ui;
};

#endif // AESW_H

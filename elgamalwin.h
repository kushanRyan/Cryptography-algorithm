#ifndef ELGAMAL_H
#define ELGAMAL_H

#include <QWidget>

namespace Ui {
class Elgamal;
}

class Elgamal : public QWidget
{
    Q_OBJECT

public:
    explicit Elgamal(QWidget *parent = 0);
    ~Elgamal();

private:
    Ui::Elgamal *ui;
};

#endif // ELGAMAL_H

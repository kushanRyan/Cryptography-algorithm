#ifndef EUCLIDEAN_H
#define EUCLIDEAN_H

#include <QWidget>

namespace Ui {
class Euclidean;
}

class Euclidean : public QWidget
{
    Q_OBJECT

public:
    explicit Euclidean(QWidget *parent = 0);
    ~Euclidean();

private:
    Ui::Euclidean *ui;
};

#endif // EUCLIDEAN_H

#ifndef ISPRIMEW_H
#define ISPRIMEW_H

#include <QWidget>

namespace Ui {
class isprimew;
}

class isprimew : public QWidget
{
    Q_OBJECT

public:
    explicit isprimew(QWidget *parent = 0);
    ~isprimew();

private slots:
    void on_endExcute_clicked();

    void on_excuter_clicked();

private:
    Ui::isprimew *ui;
};

#endif // ISPRIMEW_H

#ifndef RSAW_H
#define RSAW_H

#include <QWidget>

namespace Ui {
class rsaw;
}

class rsaw : public QWidget
{
    Q_OBJECT

public:
    explicit rsaw(QWidget *parent = 0);
    ~rsaw();

private slots:
    void on_endExcute_clicked();

    void on_excute_clicked();

private:
    Ui::rsaw *ui;
};

#endif // RSAW_H

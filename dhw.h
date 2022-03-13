#ifndef DHW_H
#define DHW_H

#include <QWidget>

namespace Ui {
class dhw;
}

class dhw : public QWidget
{
    Q_OBJECT

public:
    explicit dhw(QWidget *parent = 0);
    ~dhw();

private slots:
    void on_endExcute_clicked();

    void on_excute_clicked();

private:
    Ui::dhw *ui;
};

#endif // DHW_H

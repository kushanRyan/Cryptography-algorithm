#ifndef DH_H
#define DH_H

#include <QWidget>

namespace Ui {
class DH;
}

class DH : public QWidget
{
    Q_OBJECT

public:
    explicit DH(QWidget *parent = 0);
    ~DH();

private:
    Ui::DH *ui;
};

#endif // DH_H

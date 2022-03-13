#ifndef ELGAMALWARN_H
#define ELGAMALWARN_H

#include <QWidget>

namespace Ui {
class elgamalwarn;
}

class elgamalwarn : public QWidget
{
    Q_OBJECT

public:
    explicit elgamalwarn(QWidget *parent = 0);
    ~elgamalwarn();

private:
    Ui::elgamalwarn *ui;
};

#endif // ELGAMALWARN_H

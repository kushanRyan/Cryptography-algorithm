#ifndef DESWARN_H
#define DESWARN_H

#include <QWidget>

namespace Ui {
class deswarn;
}

class deswarn : public QWidget
{
    Q_OBJECT

public:
    explicit deswarn(QWidget *parent = 0);
    ~deswarn();

private:
    Ui::deswarn *ui;
};

#endif // DESWARN_H

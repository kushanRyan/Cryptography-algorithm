#ifndef COMPLETE_H
#define COMPLETE_H

#include <QWidget>

namespace Ui {
class complete;
}

class complete : public QWidget
{
    Q_OBJECT

public:
    explicit complete(QWidget *parent = 0);
    ~complete();

private:
    Ui::complete *ui;
};

#endif // COMPLETE_H

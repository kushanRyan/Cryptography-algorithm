#ifndef AESWARN_H
#define AESWARN_H

#include <QWidget>

namespace Ui {
class aeswarn;
}

class aeswarn : public QWidget
{
    Q_OBJECT

public:
    explicit aeswarn(QWidget *parent = 0);
    ~aeswarn();

private:
    Ui::aeswarn *ui;
};

#endif // AESWARN_H

#ifndef MD5W_H
#define MD5W_H

#include <QWidget>

namespace Ui {
class md5w;
}

class md5w : public QWidget
{
    Q_OBJECT

public:
    explicit md5w(QWidget *parent = 0);
    ~md5w();

private slots:
    void on_endExcute_clicked();

    void on_excute_clicked();

private:
    Ui::md5w *ui;
};

#endif // MD5W_H

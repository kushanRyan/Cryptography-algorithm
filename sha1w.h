#ifndef SHA1W_H
#define SHA1W_H

#include <QWidget>

namespace Ui {
class sha1w;
}

class sha1w : public QWidget
{
    Q_OBJECT

public:
    explicit sha1w(QWidget *parent = 0);
    ~sha1w();

private slots:
    void on_endExcute_clicked();

    void on_excute_clicked();

private:
    Ui::sha1w *ui;
};

#endif // SHA1W_H

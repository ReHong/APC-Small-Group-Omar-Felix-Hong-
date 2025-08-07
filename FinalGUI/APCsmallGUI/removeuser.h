#ifndef REMOVEUSER_H
#define REMOVEUSER_H

#include <QMainWindow>

namespace Ui {
class removeuser;
}

class removeuser : public QMainWindow
{
    Q_OBJECT

public:
    explicit removeuser(QWidget *parent = nullptr);
    ~removeuser();

private:
    Ui::removeuser *ui;
};

#endif // REMOVEUSER_H

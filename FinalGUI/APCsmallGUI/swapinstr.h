#ifndef SWAPINSTR_H
#define SWAPINSTR_H

#include <QMainWindow>

namespace Ui {
class swapInstr;
}

class swapInstr : public QMainWindow
{
    Q_OBJECT

public:
    explicit swapInstr(QWidget *parent = nullptr);
    ~swapInstr();

private:
    Ui::swapInstr *ui;
};

#endif // SWAPINSTR_H

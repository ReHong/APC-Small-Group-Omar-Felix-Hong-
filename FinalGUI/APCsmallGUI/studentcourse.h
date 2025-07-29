#ifndef STUDENTCOURSE_H
#define STUDENTCOURSE_H

#include <QMainWindow>

namespace Ui {
class studentcourse;
}

class studentcourse : public QMainWindow
{
    Q_OBJECT

public:
    explicit studentcourse(QWidget *parent = nullptr);
    ~studentcourse();

private:
    Ui::studentcourse *ui;
};

#endif // STUDENTCOURSE_H

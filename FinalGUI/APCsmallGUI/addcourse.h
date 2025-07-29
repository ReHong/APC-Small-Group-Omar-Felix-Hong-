#ifndef ADDCOURSE_H
#define ADDCOURSE_H

#include <QMainWindow>

namespace Ui {
class AddCourse;
}

class AddCourse : public QMainWindow
{
    Q_OBJECT

public:
    explicit AddCourse(QWidget *parent = nullptr);
    ~AddCourse();

private:
    Ui::AddCourse *ui;
};

#endif // ADDCOURSE_H

#ifndef REMOVECOURSE_H
#define REMOVECOURSE_H

#include <QMainWindow>

namespace Ui {
class RemoveCourse;
}

class RemoveCourse : public QMainWindow
{
    Q_OBJECT

public:
    explicit RemoveCourse(QWidget *parent = nullptr);
    ~RemoveCourse();

private:
    Ui::RemoveCourse *ui;
};

#endif // REMOVECOURSE_H

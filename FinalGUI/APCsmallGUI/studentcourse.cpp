#include "studentcourse.h"
#include "ui_studentcourse.h"

studentcourse::studentcourse(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::studentcourse)
{
    ui->setupUi(this);
}

studentcourse::~studentcourse()
{
    delete ui;
}

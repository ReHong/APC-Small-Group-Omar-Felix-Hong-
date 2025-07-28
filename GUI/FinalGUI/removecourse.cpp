#include "removecourse.h"
#include "ui_removecourse.h"

RemoveCourse::RemoveCourse(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RemoveCourse)
{
    ui->setupUi(this);
}

RemoveCourse::~RemoveCourse()
{
    delete ui;
}

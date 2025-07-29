#include "addcourse.h"
#include "ui_addcourse.h"

AddCourse::AddCourse(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AddCourse)
{
    ui->setupUi(this);
}

AddCourse::~AddCourse()
{
    delete ui;
}

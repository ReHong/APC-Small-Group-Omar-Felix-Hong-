#include "adminwindow.h"
#include "ui_adminwindow.h"
#include "Admin.h"

adminwindow::adminwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::adminwindow)
{
    ui->setupUi(this);
    adminLogic = new Admin("admin", "Amdin", 1, "admin@wit.edu", "admin", "President");
}

adminwindow::~adminwindow()
{
    delete ui;
    delete adminLogic;
}

#include "adduser.h"
#include "ui_adduser.h"

AddUser::AddUser(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AddUser)
{
    ui->setupUi(this);
}

AddUser::~AddUser()
{
    delete ui;
}

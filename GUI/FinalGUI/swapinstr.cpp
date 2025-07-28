#include "swapinstr.h"
#include "ui_swapinstr.h"

swapInstr::swapInstr(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::swapInstr)
{
    ui->setupUi(this);
}

swapInstr::~swapInstr()
{
    delete ui;
}

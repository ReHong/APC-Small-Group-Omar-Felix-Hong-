#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>

#include "Admin.h"

namespace Ui {
class adminwindow;
}

class adminwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminwindow(QWidget *parent = nullptr);
    ~adminwindow();

    void setAdminLogic(Admin* adminLogic);

private slots:
    void on_addUserButton_clicked();
    void on_removeUserButton_clicked();
    void on_logoutButton_clicked();

private:
    Ui::adminwindow *ui;
    Admin* adminLogic;
};

#endif // ADMINWINDOW_H

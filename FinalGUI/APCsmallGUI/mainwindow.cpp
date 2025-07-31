#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adminwindow.h"


//#include "instructor.h"
//#include "studentwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int rc = sqlite3_open("assignment3.db", &db);
    if (rc) {
        QMessageBox::critical(this, "Database Error", "Failed to open database.");
        db = nullptr;
    }
}

MainWindow::~MainWindow() {
    if (db) sqlite3_close(db);
    delete ui;
}

void MainWindow::on_loginButton_clicked() {
    QString username = ui->TextUser->text();
    QString password = ui->TextPass->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter both username and password.");
        return;
    }

    sqlite3_stmt* stmt;
    const char* sql = "SELECT ROLE, USER_ID FROM LOGIN WHERE USERNAME=? AND PASSWORD=?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        QMessageBox::critical(this, "DB Error", "Failed to prepare query.");
        return;
    }

    sqlite3_bind_text(stmt, 1, username.toStdString().c_str(), -1, nullptr);
    sqlite3_bind_text(stmt, 2, password.toStdString().c_str(), -1, nullptr);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        QString role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        int userID = sqlite3_column_int(stmt, 1);
        sqlite3_finalize(stmt);

        if (role == "ADMIN") {
            adminwindow *adminWin = new adminwindow();
            adminWin->show();
        } else if (role == "INSTRUCTOR") {
            //InstructorWindow *instrWin = new InstructorWindow();
            //instrWin->show();
        } else if (role == "STUDENT") {
            //StudentWindow *studWin = new StudentWindow();
            //studWin->show();
        }

        this->close(); // Close login window
    } else {
        sqlite3_finalize(stmt);
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}

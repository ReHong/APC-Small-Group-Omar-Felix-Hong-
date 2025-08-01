#include "Student.h"
#include "User.h"
#include "Admin.h"
#include "Instructor.h"
#include "sqlite3.h"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

Student::Student(string first, string last, int ID, string e, int g, string m) : User(first, last, ID, e)
{
    gradYear = g;
    major = m;
}

//Method
string Student::add_remove_course(sqlite3* db, int ID) { //made by Felix (gave up on conflict)
    char* messageError;
    string CRN; 
    int choice = 0;
    int Student_ID;
    string Course_ID;
    string DofW;
    string start_time;
    string end_time;

    while ((choice != 1) && (choice != 2)) {

        cout << "What would you like to do: " << endl << "1. Add Course to Schedule" << endl << "2. Remove Course from schedule" << endl;
        cin >> choice;

        if ((choice != 1) && (choice != 2)) {
            cout << "This is not a valid option. Press 1 or 2 (or 0 to exit)! " << endl;
        }

    }

    cout << endl << "Insert CRN: ";
    cin >> Course_ID;


    switch (choice) {

    case 1: { //This will add the course to the student's schedule

        /* failed we are not including this
        bool insertCourseIfNoConflict(sqlite3 * db, int Student_ID,
            const std::string & Course_ID,
            const std::string & DofW,
            const std::string & start_time,
            const std::string & end_time);

        sqlite3_stmt* stmt;
        const char* sql = R"(
                INSERT INTO Schedule (Student_ID, Course_ID, DofW, STARTTIME, TIMEEND)
                SELECT ?, ?, ?, ?, ?
                WHERE NOT EXISTS (
                SELECT 1 FROM SCHEDULE
                WHERE Student_ID = ?
                AND DofW = ?
                AND ? < TIMEEND
                AND ? > TIMESTART
                );
            )";

        if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) != SQLITE_OK)
        {
            std::cerr << "Failed to prepare INSERT statement.\n";
            return false;
        }

        // Bind values to both INSERT and subqueries 
        sqlite3_bind_int(stmt, 1, Student_ID);
        sqlite3_bind_text(stmt, 2, Course_ID.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, DofW.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, start_time.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, end_time.c_str(), -1, SQLITE_STATIC);

        sqlite3_bind_int(stmt, 6, Student_ID);         // subquery student_id
        sqlite3_bind_text(stmt, 7, DofW.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 8, start_time.c_str(), -1, SQLITE_STATIC); // new_start < existing_end
        sqlite3_bind_text(stmt, 9, end_time.c_str(), -1, SQLITE_STATIC);   // new_end > existing_start

        bool inserted = (sqlite3_step(stmt) == SQLITE_DONE);
        sqlite3_finalize(stmt);

        if (inserted) {
            std::cout << "Course added successfully.\n";
        }
        else {
            std::cout << "Conflict detected. Course not added.\n";
        }
        */


        /*
        sql = R"(
		BEGIN TRANSACTION;
		INSERT INTO SCHEDULE(Course_ID, Student_ID) VALUES
		(50020, 10020);
		COMMIT;
	)";
    */
        

        return "INSERT INTO SCHEDULE(Course_ID, Student_ID) VALUES (" + Course_ID + "," + to_string(ID) + "); COMMIT;";

        break;
    }

    case 2: { //This will remove course from the schedule
        string query = "DELETE FROM SCHEDULE WHERE Course_ID = " + Course_ID + " AND Student_ID = " + to_string(ID) + ";";
        return query;
        break;

    }
    }

}
/*
string User::print_course()
{
    return "SELECT * FROM COURSE;";

}


string User::search_courseD()
{
    string UserChoice; //must be string to plug into SQLite
    cout << "Insert CRN (all numbers): ";
    cin >> UserChoice;
    cout << endl << endl << "** Matching CRN **" << endl << endl;
    return "SELECT * FROM COURSE WHERE CRN = '" + UserChoice + "';";
}
*/

string Student::print_schedule(int ID) 
{
    string id = std::to_string(ID);
    string sql = "SELECT COURSE.CRN, COURSE.Title, COURSE.Department, COURSE.DofW, COURSE.TIMES "
        "FROM SCHEDULE "
        "JOIN COURSE ON SCHEDULE.Course_ID = COURSE.CRN "
        "WHERE SCHEDULE.Student_ID = " + id + ";";
    cout << "This is your schedule: " << endl;
    return sql;
}

//Destructor
Student::~Student() {

}
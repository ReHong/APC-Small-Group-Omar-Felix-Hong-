#include "Student.h"
#include "User.h"
#include "Admin.h"
#include "Instructor.h"
#include "sqlite3.h"
#include <cstdlib>
#include <iostream>

Student::Student(string first, string last, int ID, string e, int g, string m) : User(first,last,ID,e) 
{
	gradYear = g;
	major = m;
}

//Method
string Student::add_remove_course() {
    const char* dir = "assignment3.db";

    sqlite3* DB;
    int exit = sqlite3_open("assignment3.db", &DB);		//open the database

    sqlite3_exec(DB, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);

    char* messageError;

	string CRN; //Course CRN Number
	string ID; //Student's ID

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
	cin >> CRN; 

	cout << endl << "Insert your ID: ";
	cin >> ID; 

    switch (choice) {

    case 1: { //This will add the course to the student's schedule



        bool insertCourseIfNoConflict(sqlite3 * db, int Student_ID,
            const std::string & Course_ID,
            const std::string & DofW,
            const std::string & start_time,
            const std::string & end_time);

        cout << "Enter Student ID: ";
        cin >> Student_ID;

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
            std::cerr << "Failed to prepare INSERT statement.\n" << sqlite3_errmsg(DB) << "\n";
            break;
        }

        // Bind values to both INSERT and subqueries 
        sqlite3_bind_int(stmt, 1, Student_ID);
        sqlite3_bind_text(stmt, 2, Course_ID.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, DofW.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, start_time.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 5, end_time.c_str(), -1, SQLITE_TRANSIENT);

        sqlite3_bind_int(stmt, 6, Student_ID);         // subquery student_id
        sqlite3_bind_text(stmt, 7, DofW.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 8, start_time.c_str(), -1, SQLITE_TRANSIENT); // new_start < existing_end
        sqlite3_bind_text(stmt, 9, end_time.c_str(), -1, SQLITE_TRANSIENT);   // new_end > existing_start

        bool inserted = (sqlite3_step(stmt) == SQLITE_DONE);
        sqlite3_finalize(stmt);

        if (inserted) {

            std::cout << "Course added successfully.\n";
            return "INSERT INTO SCHEDULE (Course_ID, Student_ID) VALUES (" + CRN + ", " + ID + ");";
        }
        else {
            std::cout << "Conflict detected. Course not added.\n";
            break;
        }

        break;

    }

    case 2: { //This will remove course from the schedule
        string query = "DELETE FROM SCHEDULE (Course_ID, Student_ID) VALUES (" + CRN + ", " + ID + ");";
        return query;
        break;

    }
	}

} 

string Student::print_course() { 
	const char* sql = R"(
        SELECT *
        FROM SCHEDULE 
        WHERE Student_ID = ?
    )";
	
	cout << "This is your schedule: " << endl;
	return sql;
}

//Destructor
Student::~Student() {

}

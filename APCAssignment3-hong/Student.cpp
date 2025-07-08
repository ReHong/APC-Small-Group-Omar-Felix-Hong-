#include "Student.h"
#include "User.h"
#include "Admin.h"
#include "Instructor.h"
#include "sqlite3.h"
#include <cstdlib>
#include <iostream>

Student::Student(string first, string last, int ID, string e, int g, string m) : User(first,last,ID,e) {
	gradYear = g;
	major = m;
}

//Method


string Student::add_remove_course() {

	string CRN; //Course CRN Number
	string ID; //Student's ID

	int choice = 0;

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

	case 1: //This will add the course to the student's schedule

       

        bool insertCourseIfNoConflict(sqlite3 * db, int Student_ID,
            const std::string & Course_ID,
            const std::string & DofW,
            const std::string & start_time,
            const std::string & end_time) {
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

            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
                std::cerr << "Failed to prepare INSERT statement.\n";
                return false;
            }

            // Bind values to both INSERT and subqueries 
            sqlite3_bind_int(stmt, 1, Student_ID);
            sqlite3_bind_text(stmt, 2, Course_ID.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 3, DofW.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 4, TIMESTART.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 5, TIMEEND.c_str(), -1, SQLITE_STATIC);

            sqlite3_bind_int(stmt, 6, Student_ID);         // subquery student_id
            sqlite3_bind_text(stmt, 7, DofW.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 8, TIMESTART.c_str(), -1, SQLITE_STATIC); // new_start < existing_end
            sqlite3_bind_text(stmt, 9, TIMEEND.c_str(), -1, SQLITE_STATIC);   // new_end > existing_start

            bool inserted = (sqlite3_step(stmt) == SQLITE_DONE);
            sqlite3_finalize(stmt);

            if (inserted) {
                std::cout << "Course added successfully.\n";
            }
            else {
                std::cout << "Conflict detected. Course not added.\n";
            }

            return inserted;
        }

      

		return "INSERT INTO SCHEDULE (Course_ID, Student_ID) VALUES (" + CRN + ", " + ID + ");"; 
		break;

    case 2: //This will remove course from the schedule

		return "DELETE FROM SCHEDULE (Course_ID, Student_ID) VALUES (" + CRN + ", " + ID + ");";

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

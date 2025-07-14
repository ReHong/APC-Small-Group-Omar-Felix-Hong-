#include "Student.h"
#include "User.h"
#include "Admin.h"
#include "Instructor.h"
#include "sqlite3.h"
#include <cstdlib>
#include <iostream>
#include <string>

Student::Student(string first, string last, int ID, string e, int g, string m) : User(first, last, ID, e)
{
    gradYear = g;
    major = m;
}

//Method
string Student::add_remove_course(sqlite3* db, int ID) {
    char* messageError;

    string CRN; //Course CRN Number
    //string ID; //Student's ID

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

        /*
        sql = R"(
		BEGIN TRANSACTION;
		INSERT INTO SCHEDULE(Course_ID, Student_ID) VALUES
		(50020, 10020);
		COMMIT;
	)";
    */
        
        return "INSERT INTO SCHEDULE(Course_ID, Student_ID) VALUES (" + Course_ID + "," + std::to_string(ID) + "); COMMIT;";

        break;
    }

    case 2: { //This will remove course from the schedule
        string query = "DELETE FROM SCHEDULE (Course_ID, Student_ID) VALUES (" + Course_ID + ", " + std::to_string(ID) + ");";
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
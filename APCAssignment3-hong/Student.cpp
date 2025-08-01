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
string Student::add_remove_course(sqlite3* db, int ID) 
{ //made by Felix (gave up on conflict) overide and helped by Hong
    char* messageError; //error message displau
    string CRN; 
    int choice = 0; //select between add or remove
    int Student_ID;
    string Course_ID; //ID of the course input
    string DofW;
    string start_time;
    string end_time;
    sqlite3_stmt* stmt;
    
    while ((choice != 1) && (choice != 2)) //ensure that theres only 2 choices otherwise loop back until user selects 1 or 2
    {

        cout << "What would you like to do: " << endl << "1. Add Course to Schedule" << endl << "2. Remove Course from schedule" << endl;
        cin >> choice;

        if ((choice != 1) && (choice != 2)) 
        {
            cout << "This is not a valid option. Press 1 or 2 (or 0 to exit)! " << endl;
        }

    }
    
    cout << endl << "Insert CRN: ";
    cin >> Course_ID;

    switch (choice) 
    {
    case 1: { //This will add the course to the student's schedule
        string NDofW; //next Days of the week to reference and compare
        int Ns = 0; //start time record
        int Ne = 0; //end time record

        //DofW to compare days of the week, 
        //need timestart and timeend to do logic comparison 
        // if time between 2 courses are in each other thereforce confliction
        string courseInfoQuery = "SELECT DofW, TIMESTART, TIMEEND FROM COURSE WHERE CRN = " + Course_ID + ";";

        if (sqlite3_prepare_v2(db, courseInfoQuery.c_str(), -1, &stmt, NULL) == SQLITE_OK &&
            sqlite3_step(stmt) == SQLITE_ROW) 
        {
            NDofW = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            Ns = sqlite3_column_int(stmt, 1);
            Ne = sqlite3_column_int(stmt, 2);
        }
        else {
            cout << "Course not found.\n";
            sqlite3_finalize(stmt);
            return "";
        }
        sqlite3_finalize(stmt); //save state

        string checkQuery = 
            "SELECT c.DofW, c.TIMESTART, c.TIMEEND "
            "FROM COURSE c "
            "JOIN SCHEDULE s ON c.CRN = s.Course_ID "
            "WHERE s.Student_ID = " + to_string(ID) + ";";

        if (sqlite3_prepare_v2(db, checkQuery.c_str(), -1, &stmt, NULL) == SQLITE_OK) 
        {
            while (sqlite3_step(stmt) == SQLITE_ROW) //when it goes through all the rows based on what it read from database
            {
                string currentDofW = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)); //existing course being analyze and added at that row
                int curstart = sqlite3_column_int(stmt, 1);//current time start
                int curend = sqlite3_column_int(stmt, 2); //current time end

                for (char day : NDofW) //goes through the string of DofW to to see if theres a certain day that may conflict
                {
                    if (currentDofW.find(day) != string::npos)
                    {
                        // Time conflict?
                        if (!(Ne <=curstart || Ns >= curend)) //when its not true 
                        {
                            cout << "Course conflict detected on day: " << day << ". Course not added.\n";
                            sqlite3_finalize(stmt);
                            return "";
                        }
                    }
                }
            }
        }
        sqlite3_finalize(stmt);
        string insertQuery = "INSERT INTO SCHEDULE(Course_ID, Student_ID) VALUES (" + Course_ID + ", " + to_string(ID) + ");";
        return insertQuery;
        break;
    }

    case 2: 
    { //This will remove course from the schedule
        string query = "DELETE FROM SCHEDULE WHERE Course_ID = " + Course_ID + " AND Student_ID = " + to_string(ID) + ";";
        return query;
        break;
    }
    }
}

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
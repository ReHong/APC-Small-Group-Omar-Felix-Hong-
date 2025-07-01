#include "Admin.h"
#include "User.h"
#include "Instructor.h"
#include "Student.h"
#include "sqlite3.h"
#include <iostream>
#include <string>

using namespace std; //thanks geeksforgeeks


static int callback(void* data, int argc, char** argv, char** azColName)
{
	int i;

	for (i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");

	return 0;
}


Admin::Admin(string first, string last, int ID, string e, string t, string o) : User(first, last, ID, e) {
	title = t;
	office = o;
}

//Method

string Admin::add_course() //work in progress
{
	string CRN; //CRN number
	string T; //title
	string D; //Department

	string t;
	string day;

	string tl1; //Times (Label)
	string tl2;

	string ti; //Time inital
	string te; //Time end

	int tii, tei; //int for the Time initial and end
	int h1, h2; //hold values

	string dw; //DofW
	string sem;//Semester
	string year;
	string cred;
	string instructID;
	bool loop = true;

	cout << "*** Adding NEW Course to Database ***" << endl << endl
		<< "Enter CRN: ";
	cin >> CRN;

	cout << endl << "Enter Course Name:";
	cin >> T;

	cout << endl << "Enter Department Section:";
	cin >> D;

	while (loop) //wont stop until the time has an actual start and end logically in military time
	{
		cout << endl << "Enter Time (Ex. 2:00-4:00 PM)";
		cout << endl << "Following must be in Military time for start and end";
		cout << endl << "Enter Initial Time:";
		cin >> tii;
		cout << endl << "Enter End Time:";
		cin >> tei;

		tl1 = to_string(tii);
		tl2 = to_string(tei);

		if (tei > 12) //check AM or PM
		{
			day = "PM";
		}
		else
		{
			day = "AM";
		}


		if (tei > tii)
		{
			ti = std::to_string(tii);
			te = std::to_string(tei);
			loop = false; //only ends when the end time is higher than the inital
		}
		else
		{
			cout << endl << "** ERROR: End Time is less than time start, Try again.**" << endl;
		}

	}

	t = tl1 + ":00 - " + tl2 + ":00 " + day;

	cout << endl << "Enter Days of the week (In order Ex. M W F): ";
	cin >> dw;

	cout << endl << "Enter Semester:";
	cin >> sem;

	cout << endl << "Enter Year:";
	cin >> year;

	cout << endl << "Enter Number of Credits:";
	cin >> cred;

	cout << endl << "Enter Instructor ID:";
	cin >> instructID;

	cout << "*Adding New Course*" << endl;

	//"INSERT INTO COURSE VALUES(50008, 'Engrish', 'BSEE', '8:00 - 10:00 AM', 8, 10, 'M W F', 'Fall', 2022, 4, NULL);
	return "INSERT INTO COURSE VALUES(" + CRN + ", '" + T + "', '" + D + "', '"
		+ t + "', " + ti + ", " + te + ", '" + dw + "', '" + sem + "', " + year
		+ ", " + instructID + ")"; //related insert to the previous comment
	//return "INSERT INTO COURSE VALUES(" + CRN + ", '" + T + "', '" + D + "', '" + t + "', '" + dw + "', '" + sem + "', " + year + ", " + instructID + ")";
}


/*
//test case for using the methods for sqlite

	//remove Instructor + Updating Admin
	//suppossed remove
	//string userInput2(test.remove_user(2));

	sqlite3_stmt* stmt; //an all purpose variable for finalization and update changes
	int id;
	const char* sqlD = "DELETE FROM INSTRUCTOR WHERE ID = ?;"; //a way to delete and remove
	cout << "Delete Instructor 1-6: ";
	cin >> id;
	id = id + 20000;

	sqlite3_prepare_v2(DB, sqlD, -1, &stmt, NULL); //preparing the update
	sqlite3_bind_int(stmt, 1, id); //change name of that row that matches with the ID number
	sqlite3_step(stmt); //run it
	sqlite3_finalize(stmt); //save
	exit = sqlite3_exec(DB, userInput.c_str(), callback, NULL, NULL); //permanant save

*/

int Admin::remove_course() //all process within a command
{

	sqlite3* DB;
	sqlite3_open("assignment3.db", &DB);
	sqlite3_exec(DB, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);

	const char* sqlD = "DELETE FROM COURSE WHERE CRN = ?;";
	sqlite3_stmt* stmt;

	int choice;
	cout << "** REMOVING COURSE PROTOCOL **" << endl;
	cout << "ENTER CRN for Deletion: ";
	cin >> choice;

	if (sqlite3_prepare_v2(DB, sqlD, -1, &stmt, NULL) == SQLITE_OK)
	{
		sqlite3_bind_int(stmt, 1, choice);
		if (sqlite3_step(stmt) == SQLITE_DONE)
		{
			cout << "** Course Deleted Successfully **" << endl;
		}
		else
		{
			cout << "** Error Deleting Course **" << endl;
		}
		sqlite3_finalize(stmt);
	}
	else
	{
		cout << "** Failed Erase **" << endl;
	}

	sqlite3_close(DB);
	return choice;
}

string Admin::add_user() 
{
	string firstN;
	string lastN;
	string ID;                                       //may revert back to int in the future
	string e; //email
	string t; //title 
	string m; //major and dept
	string o; //office
	string year; // "gradyear" or "Year of Hire"       //may revert back to int in the future
	
	int user;
	bool reg = true;
	while (reg)
	{
		cout << "** Process of Adding User **" << endl
			<< "1. Admin " << endl
			<< "2. Instructor " << endl
			<< "3. Student " << endl;
		cin >> user;
		if ((0 < user) && (user < 4))
		{
			cout << "** ERROR User Choice Try Again **" << endl;
			reg = false;
		}
	}

	cout << "Name: ";
	cin >> firstN;

	cout << "Surname: ";
	cin >> lastN;

	cout << "ID: ";
	cin >> ID;

	cout << "Major or Department: ";
	cin >> m;

	cout << "Email: ";
	cin >> e;

	cout << "Year of Graduation/Hire: ";
	cin >> year;

	if (user != 3) //3 = student
	{
		cout << "Title: ";
		cin >> t;

		cout << "Office: ";
		cin >> o;
	}

	//probably and most definetely will need to update and fix this for futureproofing

		//sample insert: "INSERT INTO ADMIN VALUES(30001, 'Margaret', 'Hamilton', 'President', 'Dobbs 1600', 'hamiltonm');"
					   //"INSERT INTO INSTRUCTOR VALUES(20001, 'Joseph', 'Fourier', 'Full Prof.', 1820, 'BSEE', 'fourierj');"
					   //"INSERT INTO STUDENT VALUES(10001, 'Isaac', 'Newton', 1668, 'BSAS', 'newtoni');"
	switch (user)
	{
	case 1: //admin
		return "INSERT INTO ADMIN VALUES(" + ID + ", '" + firstN + "', '" + lastN + "', '" + t + "', '" + o + "', '" + e + "');";
		break;

	case 2://instructor
		return "INSERT INTO INSTRUCTOR VALUES(" + ID + ", '" + firstN + "', '" + lastN + "', '" + t + "', " + year + ", '" + m + "', '" + e + "');";
		break;

	case 3://student
		return "INSERT INTO STUDENT VALUES(" + ID + ", '" + firstN + "', '" + lastN + "', " + year + ", '" + m + "', '" + e + "');";
		break;
	}

}

string Admin::remove_user()
{
	string ID; //identificaion of each data within the database
	int user;
	bool reg = true;
	while (reg)
	{
		cout << "** Process of Removing User **" << endl
			<< "1. Admin " << endl
			<< "2. Instructor " << endl
			<< "3. Student " << endl;
		cin >> user;
		if ((0 < user) && (user < 4))
		{
			reg = false;
		}
		else
		{
			cout << "** ERROR User Choice Try Again **" << endl;
		}
	}
	switch (user) //switch between adding or removing one of the 3 selected using User variable
	{
	case 1: //Admin
		cout << "**Process of Removing Admin**" << endl
			<< "ID: ";
		cin >> ID;

		cout << "** Removing User Completed **" << endl;

		return string("DELETE FROM ADMIN WHERE ID = ") + ID + ";";

		break;

	case 2: //Instructor
		cout << "**Process of Removing Instructor**" << endl
			<< "ID: ";
		cin >> ID;

		cout << "** Removing User Completed **" << endl;

		return string("DELETE FROM INSTRUCTOR WHERE ID = ") + ID + ";";


		break;

	case 3: //Student
		cout << "**Process of Removing Student**" << endl
			<< "ID: ";
		cin >> ID;

		cout << "** Removing User Completed **" << endl;

		return string("DELETE FROM STUDENT WHERE ID = ") + ID + ";";

		break;
	}

}


string Admin::print_class() 
{
	string print_class;
	cout << "This is the printed class" << endl;
	cin >> print_class;
	return print_class;
}

string Admin::link_instructor() //add or change instructor to the course
{
	string instructorID;
	string courseCRN;
	cout << "** INSTRUCTOR TO COURSE **" << endl;

	cout << endl << "Course ID:";
	cin >> courseCRN;

	cout << endl << "Instructor ID:";
	cin >> instructorID;

	return "UPDATE COURSE SET INSTRUCTOR_ID = " + instructorID + " WHERE CRN = " + courseCRN + ";";
}

string Admin::link_student() //add or remove
{
	string courseCRN; 
	string studentID;
	int choice = 0;

	cout << "** STUDENT TO COURSE **" << endl;
	while ((choice != 1) && (choice != 2)) //loops only when when the user does not pick the 2 options
	{
		cout << endl << "1. Linking Student to Course"
			<< endl << "2. Removing Student from Course"
			<< endl << "Choice: ";
		cin >> choice;

		if ((choice != 1) && (choice != 2))
		{
			cout << "** Not an option. Try Again **" << endl;
		}
	}

	cout << endl << "Course ID:";
	cin >> courseCRN;

	cout << endl << "Student ID:";
	cin >> studentID;

	switch (choice)
	{
	case 1: //adding student
		return "INSERT INTO SCHEDULE (Course_ID, Student_ID) VALUES(" + courseCRN + ", " + studentID + ");";
		break;

	case 2: //removing student
		return "DELETE FROM SCHEDULE WHERE Course_ID = " + courseCRN + " AND Student_ID = " + studentID + ";";
	}
}

//Destructor
Admin::~Admin() {

}

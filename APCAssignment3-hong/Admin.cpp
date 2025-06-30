#include "Admin.h"
#include "User.h"
#include "Admin.h"
#include "Instructor.h"
#include "Student.h"
#include "sqlite3.h"


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
	string t; //Times (Label)

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

	while (loop)
	{
		cout << endl << "Enter Time (Ex. 2:00-4:00 PM)";
		cout << endl << "Following must be in Military time for start and end";
		cout << endl << "Enter Initial Time:";
		cin >> tii;
		cout << endl << "Enter End Time:";
		cin >> tei;

		if (tei > tii)
		{
			ti = std::to_string(tii);
			te = std::to_string(tei);
			loop = false;
		}
		else
		{
			cout << endl << "** ERROR: End Time is less than time start, Try again.**" << endl;
		}

	}
	cout << endl << "Enter Days of the week (In order Ex. M W F):";
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
		+ ", " + instructID + ")";
	//return "INSERT INTO COURSE VALUES(" + CRN + ", '" + T + "', '" + D + "', '" + t + "', '" + dw + "', '" + sem + "', " + year + ", " + instructID + ")";
}

string Admin::remove_course() { //work in progress

	cout << "CRN Number for Deletion:";
	string choice;
	cout << "Enter course you want to add: " << endl;
	cin >> choice;
	return "DELETE FROM COURSE WHERE CRN = ?;";
}

string Admin::add_user(int User) {

	string firstN; 
	string lastN; 
	string ID;                                       //may revert back to int in the future
	string e; //email
	string t; //title 
	string m; //major and dept
	string o; //office
	string year; // "gradyear" or "Year of Hire"       //may revert back to int in the future

	cout << "Process of Adding User" << endl 
		<< "Name: ";
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

	if (User != 3) //3 = student
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
	switch (User)
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

string Admin::remove_user(int User)
{
	string ID; //identificaion of each data within the database

	switch (User)
	{
	case 1: //Admin
		cout << "**Process of Removing Admin**" << endl
			<< "ID: ";
		cin >> ID;

		cout << "** Removing User Completed **" << endl;

		return "DELETE FROM ADMIN WHERE ID = ?;";

		break;

	case 2: //Instructor
		cout << "**Process of Removing Instructor**" << endl
			<< "ID: ";
		cin >> ID;

		cout << "** Removing User Completed **" << endl;

		return "DELETE FROM INSTRUCTOR WHERE ID = ?;";

		break;

	case 3: //Student
		cout << "**Process of Removing Student**" << endl
			<< "ID: ";
		cin >> ID;

		cout << "** Removing User Completed **" << endl;

		return "DELETE FROM STUDENT WHERE ID = ?;";

		break;
	}

}

string Admin::add_student_course()
{
	return "None";
}

string Admin::remove_student_course()
{
	return "None";
}


string Admin::link_instructor()
{
	return "None";
}

string Admin::link_student()
{
	return "None";
}

//Destructor
Admin::~Admin() {

}

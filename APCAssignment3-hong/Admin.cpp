#include "Admin.h"
#include "User.h"
#include "Instructor.h"
#include "Student.h"
#include "sqlite3.h"
#include <iostream>
#include <string>

using namespace std; //thanks geeksforgeeks

//Everything here and modified by Hong

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

	cin.ignore();

	cout << endl << "Enter Course Name:";
	cin.ignore();
	getline(cin, T);

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


		if (tei > 12) //check and sets time accordingly
		{
			if (tii > 12) //when tii is greater than tei
			{
				tl1 = to_string(tii-12);
				tl2 = to_string(tei-12);
			}
			else //only tei greater than 12
			{
				tl1 = to_string(tii);
				tl2 = to_string(tei-12);
			}
			day = "PM";
		}
		else
		{
			tl1 = to_string(tii);
			tl2 = to_string(tei);
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

	int timechoice = 0;
	bool logic = true;

	while (logic) //declare time 
	{
		cout << endl << "Choose a time End" << endl
			<< "1. #:00" << endl
			<< "2. #:15" << endl
			<< "3. #:30" << endl
			<< "4. #:45" << endl
			<< "choice: ";

		cin >> timechoice;

		if ((timechoice > 4) || (timechoice <= 0)) //repeat
		{
			cout << endl << "**ERROR INPUT INVALID TRY AGAIN**" << endl;
		}
		else//end logic
		{
			logic = false;
		}
		
	}

	switch (timechoice)
	{
	case 1://0 min
		t = tl1 + ":00 - " + tl2 + ":00 " + day;
		break;
	case 2://15 min
		t = tl1 + ":15 - " + tl2 + ":15 " + day;
		break;
	case 3://30 min
		t = tl1 + ":30 - " + tl2 + ":30 " + day;
		break;
	case 4://45 min
		t = tl1 + ":45 - " + tl2 + ":45 " + day;
		break;

	default:
		t = tl1 + ":00 - " + tl2 + ":00 " + day;
		break;
	}

	

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
		+ ", " + cred + ", " + instructID + ");"; //related insert to the previous comment
	//return "INSERT INTO COURSE VALUES(" + CRN + ", '" + T + "', '" + D + "', '" + t + "', '" + dw + "', '" + sem + "', " + year + ", " + instructID + ")";
}

int Admin::remove_course(sqlite3* db)
{

	const char* sqlD = "DELETE FROM COURSE WHERE CRN = ?;";
	sqlite3_stmt* stmt;

	int choice;
	cout << "** REMOVING COURSE PROTOCOL **" << endl;
	cout << "ENTER CRN for Deletion: ";
	cin >> choice;

	if (sqlite3_prepare_v2(db, sqlD, -1, &stmt, NULL) == SQLITE_OK)
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

	return choice;
}

string Admin::add_user(sqlite3* db)
{
	sqlite3_stmt* stmt;
	string firstN;
	string lastN;
	string ID;                                       //may revert back to int in the future
	string e; //email
	string t; //title 
	string m; //major and dept
	string o; //office
	string year; // "gradyear" or "Year of Hire"       //may revert back to int in the future
	
	string hold; //to add user
	char* messageError;


	int user;
	bool reg = true;
	while (reg)
	{
		cout << "** Process of Adding User **" << endl
			<< "1. Admin " << endl
			<< "2. Instructor " << endl
			<< "3. Student " << endl;
		cin >> user;
		if ((user > 0) && (user < 4)) {
			reg = false; // Valid input, break loop
		}
		else {
			cout << "** ERROR User Choice Try Again **" << endl;
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

	switch (user)
	{
	case 1: //admin
		hold = "INSERT INTO ADMIN VALUES(" + ID + ", '" + firstN + "', '" + lastN + "', '" + t + "', '" + o + "', '" + e + "');";
		sqlite3_exec(db, hold.c_str(), callback, nullptr, &messageError);
		break;

	case 2://instructor
		hold = "INSERT INTO INSTRUCTOR VALUES(" + ID + ", '" + firstN + "', '" + lastN + "', '" + t + "', " + year + ", '" + m + "', '" + e + "');";
		sqlite3_exec(db, hold.c_str(), callback, nullptr, &messageError);
		break;

	case 3://student
		hold = "INSERT INTO STUDENT VALUES(" + ID + ", '" + firstN + "', '" + lastN + "', " + year + ", '" + m + "', '" + e + "');";
		sqlite3_exec(db, hold.c_str(), callback, nullptr, &messageError);
		break;
	}

	return "INSERT INTO LOGIN (USERNAME, PASSWORD, ROLE, USER_ID) VALUES ('" + e + "', 'MysoultoWIT2022', 'INSTRUCTOR', " + ID + ");"; //add to the login table

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
	switch (user)
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


string Admin::print_class() {
	string print_class;
	cout << "This is the printed class" << endl;
	cin >> print_class;
	return print_class;
}

string Admin::link_instructor()
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

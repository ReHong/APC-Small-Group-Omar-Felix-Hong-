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

string Admin::add_course() {

	string choice;
	cout << "Enter course you want to add: " << endl;
	cin >> choice;
	return choice;
}

string Admin::remove_course() {

	string choice;
	cout << "Enter course you want to remove: " << endl;
	cin >> choice;
	return choice; 
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

string Admin::remove_user(int User) {

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

string Admin::search_course() {

	string choice;
	cout << "Enter Course you want to search: " << endl;
	cin >> choice;
	return choice;
}

string Admin::print_course() {
	string print_course;
	cout << "This is the printed course" << endl;
	cin >> print_course;
	return print_course;
}

string Admin::search_class() {

	string choice;
	cout << "Enter class you want to search: " << endl;
	cin >> choice;
	return choice;
}

string Admin::print_class() { 
	string print_class;
	cout << "This is the printed class" << endl;
	cin >> print_class;
	return print_class; 
}

//Destructor
Admin::~Admin() {

}

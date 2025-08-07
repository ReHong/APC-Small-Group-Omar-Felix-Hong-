#include "Instructor.h"
#include "User.h"
#include "Student.h"
#include "Admin.h"

Instructor::Instructor(string first, string last, int ID, string e, string t, int y, string d) : User(first, last, ID, e) 
{
	title = t;
	YoH = y;
	department = d;
}

//Method

string Instructor::print_schedule() {
	string print_schedule;
	cout << "This will be the schedule printed" << endl;
	cin >> print_schedule;
	return print_schedule;
}

string Instructor::print_class() {
	string print_class;
	cout << "This will be the classes printed" << endl;
	cin >> print_class;
	return print_class;
}

string Instructor::search_course() {

	string course;
	cout << "Type in course name here: " << endl;
	cin >> course;
	return course;
}

//Destructor
Instructor::~Instructor() {
	
}

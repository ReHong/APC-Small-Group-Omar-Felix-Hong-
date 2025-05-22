#include "Student.h"
#include "User.h"
#include "Admin.h"
#include "Instructor.h" 

Student::Student(string first, string last, int ID) : User(first,last,ID) {

}

//Method

string Student::search_course() {

	string course;
	cout << "Enter course name: " << endl;
	cin >> course;
	return course;
}

string Student::add_course() {

	string course;
	cout << "Enter course name you want to add: " << endl;
	cin >> course;
	return course;
}

string Student::drop_course() {

	string course;
	cout << "Enter course name you want to drop: " << endl;
	cin >> course;
	return course;
}

string Student::print_course() {
	string print_course;
	cout << "This is the printed course" << endl;
	cin >> print_course;
	return print_course;
}

//Destructor
Student::~Student() {

}

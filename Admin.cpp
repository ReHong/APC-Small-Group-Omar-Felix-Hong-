#include "Admin.h"
#include "User.h"
#include "Admin.h"
#include "Instructor.h"
#include "Student.h"


Admin::Admin(string first, string last, int ID) : User(first, last, ID) {

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

string Admin::add_user() {

	string choice;
	cout << "Enter User you want to add: " << endl;
	cin >> choice;
	return choice;
}

string Admin::remove_user() {

	string choice;
	cout << "Enter User you want to remove: " << endl;
	cin >> choice;
	return choice;
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

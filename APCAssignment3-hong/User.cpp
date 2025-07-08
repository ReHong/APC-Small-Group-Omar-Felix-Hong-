#include "User.h"
#include <iostream>
#include <string>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;
using std::string;

User::User()
{
	first_name = "Tester";
	last_name = "Bot";
	ID_num = 9999;
	email = "bot@bot.com";
}

User::User(string first, string last, int ID, string E) {
	
	//Attributes
	first_name = first;
	last_name = last;
	ID_num = ID;
	email = E;

}

//Method
string User::show_first() {

	return first_name;

}

string User::show_last() {

	return last_name;

}

int User::show_ID() {

	return ID_num;

}

string User::show_email()
{
	return email;
}
void User::set_email(string e)
{
	email = e;
}

void User::set_ID(int ID) {
	ID_num = ID;
}

void User::set_first(string first) {
	first_name = first;
}

void User::set_last(string last) {
	last_name = last;
}

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
string User::search_courseP()
{
	int select;

	string UserChoice; //must be string to plug into SQLite

	string parameter;

	cout << "**** Search Bar Selection ****" << endl <<
		"Select One of the Many Option: " << endl <<
		"1. CRN" << endl <<
		"2. Title" << endl <<
		"3. Department" << endl <<
		"4. Times" << endl <<
		"5. Days of the Week" << endl <<
		"6. Semester" << endl <<
		"7. Credits" << endl <<
		"8. Instructor Taught" << endl <<
		"9-etc Default" << endl << endl <<
		"Choice: ";
	cin >> select;

	switch (select)
	{
	case 1: //CRN search
		cout << "Insert CRN: ";
		cin >> UserChoice;
		cout << endl << endl << "** Matching CRN **" << endl << endl;
		return "SELECT * FROM COURSE WHERE CRN = '" + UserChoice + "';";
		break;

	case 2: //Title Search
		cout << "Insert Title: ";
		cin >> UserChoice;
		cout << endl << endl << "** Matching Title **" << endl << endl;
		return "SELECT * FROM COURSE WHERE TITLE = '" + UserChoice + "';";
		break;

	case 3: //department search
		cout << "Insert Department: ";
		cin >> UserChoice;
		cout << endl << endl << "** Matching Department **" << endl << endl;
		return "SELECT * FROM COURSE WHERE DEPARTMENT = '" + UserChoice + "';";
		break;

	case 4: //times search
		cout << "Insert Times: ";
		cin >> UserChoice;
		cout << endl << endl << "** Matching Times **" << endl << endl;
		return "SELECT * FROM COURSE WHERE TIMES = '" + UserChoice + "';";
		break;

	case 5: //Days of the Week search
		cout << "(Must be exact Ex: 'M W F')" << endl << "Insert Day of the Week: ";
		cin >> UserChoice;
		cout << endl << endl << "** Matching Days of the Week **" << endl << endl;
		return "SELECT * FROM COURSE WHERE DofW = '" + UserChoice + "';";
		break;

	case 6: //Semester
		cout << "Insert Semester: ";
		cin >> UserChoice;
		cout << endl << endl << "** Matching Semester **" << endl << endl;
		return "SELECT * FROM COURSE WHERE SEMESTER = '" + UserChoice + "';";
		break;

	case 7:
		cout << "Insert Credits: ";
		cin >> UserChoice;
		cout << endl << endl << "** Matching CRN **" << endl << endl;
		return "SELECT * FROM COURSE WHERE CREDITS = '" + UserChoice + "';";
		break;

	case 8:
		cout << "Insert Teaching Instructor: ";
		cin >> UserChoice;
		cout << endl << endl << "** Matching Instructor to Course **" << endl << endl;
		return "SELECT * FROM COURSE WHERE INSTRUCTOR_ID = '" + UserChoice + "';";
		break;

	default:
		cout << "Insert Title: ";
		cin >> UserChoice;
		cout << endl << endl << "** Matching Title Choice **" << endl << endl;
		return "SELECT * FROM COURSE WHERE TITLE = '" + UserChoice + "';";
		break;
	}
}
//Destructor
User::~User() {

}

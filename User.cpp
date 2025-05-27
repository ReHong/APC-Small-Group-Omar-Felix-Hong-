#include <iostream>
#include <string>
#include <cstdlib>
#include "User.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

User::User(string first, string last, int ID) {
	

	//Attributes
	first_name = first;
	last_name = last;
	ID_num = ID;

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

void User::set_ID(int ID) {
	ID_num = ID;
}

void User::set_first(string first) {
	first_name = first;
}

void User::set_last(string last) {
	last_name = last;
}


//Destructor
User::~User() {

}


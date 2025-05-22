#include "User.h"
#include <iostream>
#include <string>
#include <cstdlib>

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

//Destructor
User::~User() {

}


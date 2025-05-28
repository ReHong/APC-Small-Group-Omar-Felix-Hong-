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


//Destructor
User::~User() {

}

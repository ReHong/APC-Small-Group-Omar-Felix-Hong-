#pragma once
#include <iostream>
#include <string>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class User
{

	//Attributes
protected:
	string first_name;
	string last_name;
	int ID_num;

	//added
	string email;

public:
	//Constructor
	User();
	User(string first, string last, int ID, string E);

	//Method
	string show_first();
	string show_last();
	int show_ID();
	string show_email();
	
	void set_ID(int ID);
	void set_first(string first);
	void set_last(string last);
	void set_email(string e);

	string print_course();
	string search_courseD();
	string search_courseP();
	//Destructors

	~User();

};
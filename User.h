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

public: 
	//Constructor
	User(); 
	User(string first, string last, int ID);

	//Method
	string show_first();
	string show_last();
	int show_ID();

	//Destructor

	~User();

};


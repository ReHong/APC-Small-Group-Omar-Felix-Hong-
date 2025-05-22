#pragma once
#include "User.h"
#include "Student.h"
#include "Instructor.h"

class Admin :
    public User
{
public:
	Admin(string first, string last, int ID);
	string add_course();
	string remove_course();
	string add_user();
	string remove_user();
	string search_course();
	string print_course();
	string search_class();
	string print_class(); 

	//Destructor

	~Admin(); 

};


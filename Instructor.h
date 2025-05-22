#pragma once
#include "User.h"
#include "Admin.h"
#include "Student.h"

class Instructor :
    public User
{
public:
	Instructor(string first, string last, int ID);
	string print_schedule();
	string print_class();
	string search_course();

	//Destructor
	~Instructor();

};


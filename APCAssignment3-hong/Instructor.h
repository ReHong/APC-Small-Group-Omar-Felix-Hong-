#pragma once
#include "User.h"
#include "Admin.h"
#include "Student.h"

class Instructor :
    public User
{
	string title;
	int YoH;
	string department;

public:
	Instructor(string first, string last, int ID, string e);
	string print_schedule();
	string print_class();
	string search_course();

	//Destructor
	~Instructor();

};


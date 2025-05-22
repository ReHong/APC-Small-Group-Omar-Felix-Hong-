#pragma once
#include "User.h"
#include "Admin.h"
#include "Instructor.h"

class Student :
    public User
{
public:
	Student(string first, string last, int ID);
	string search_course();
	string add_course();
	string drop_course();
	string print_course();

	//Destructor
	~Student();

};


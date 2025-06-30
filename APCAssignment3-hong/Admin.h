#pragma once
#include "User.h"
#include "Student.h"
#include "Instructor.h"
#include "sqlite3.h"

class Admin :
    public User
{
	string title;
	string office;

public:
	Admin(string first, string last, int ID, string e, string t, string o);
	string add_course();
	void remove_course();

	string add_user(int User);
	string remove_user(int User);

	string print_class();
	string link_instructor();
	string link_student();
	//Destructor

	~Admin(); 

};


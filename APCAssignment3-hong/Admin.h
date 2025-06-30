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
	string remove_course();

	string add_user(int User); 
	string remove_user(int User);

	string add_student_course(); //add student to the course
	string remove_student_course(); //remove student from the course

	string link_instructor();
	string link_student();
	//Destructor

	~Admin(); 

};


#pragma once
#include "User.h"
#include "Admin.h"
#include "Instructor.h"
#include "sqlite3.h"

class Student :
    public User
{
	int gradYear;
	string major;

public:
	Student(string first, string last, int ID, string e, int g, string m);
	string add_remove_course();
	string print_course();
	//string check_confliction();  Now within the add_remove_course function



	//Destructor
	~Student();

};


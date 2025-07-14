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
	int remove_course(sqlite3* db);

	string add_user(sqlite3* db);
	string remove_user();

	string print_class();
	string link_instructor();
	string link_student();
	//Destructor

	~Admin();

};


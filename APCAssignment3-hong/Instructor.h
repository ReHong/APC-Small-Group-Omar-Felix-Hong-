#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "User.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


class Instructor : public User
{
private:
    string title;
    int    hireYear;
    string dept;

public:
    Instructor(string first,
        string last,
        int    ID,
        string email,
        string _title,
        int    _hireYear,
        string _dept);

    string print_schedule() const;

    // roster – direct & prompt versions
    string print_course_roster(int crn) const;
    string print_course_roster() const;

    string search_course_roster_for_student() const;
};

#endif   // INSTRUCTOR_H

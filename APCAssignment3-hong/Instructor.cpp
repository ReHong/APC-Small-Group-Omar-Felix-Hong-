#include "Instructor.h"


Instructor::Instructor(string first,
    string last,
    int    ID,
    string email,
    string _title,
    int    _hireYear,
    string _dept)
    : User(first, last, ID, email),
    title(_title),
    hireYear(_hireYear),
    dept(_dept) {}


string Instructor::print_schedule() const
{
    stringstream ss;
    ss << "SELECT CRN, TITLE, TIMES, DofW, SEMESTER, YEAR, CREDITS "
        << "FROM COURSE WHERE INSTRUCTOR_ID = " << getID() << ";";
    return ss.str();
}


string Instructor::print_course_roster(int crn) const
{
    stringstream ss;
    ss << "SELECT s.ID, s.NAME, s.SURNAME, s.EMAIL "
        << "FROM STUDENT s "
        << "JOIN SCHEDULE sch ON s.ID = sch.Student_ID "
        << "WHERE sch.Course_ID = " << crn << " "
        << "ORDER BY s.SURNAME;";
    return ss.str();
}


string Instructor::print_course_roster() const
{
    int crn;
    cout << "\nEnter CRN whose roster you’d like to print: ";
    cin >> crn;
    return print_course_roster(crn);
}


string Instructor::search_course_roster_for_student() const
{
    string key;
    cout << "\nSearch student by ID or surname: ";
    cin >> key;

    stringstream ss;
    ss << "SELECT c.CRN, c.TITLE, s.ID, s.NAME, s.SURNAME "
        << "FROM COURSE c "
        << "JOIN SCHEDULE sch ON c.CRN = sch.Course_ID "
        << "JOIN STUDENT  s   ON sch.Student_ID = s.ID "
        << "WHERE c.INSTRUCTOR_ID = " << getID() << " "
        << "  AND (s.ID LIKE '%" << key << "%' "
        << "       OR s.SURNAME LIKE '%" << key << "%') "
        << "ORDER BY c.CRN;";
    return ss.str();
}

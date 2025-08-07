#include <QApplication>
#include "mainwindow.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "User.h"
#include "Student.h"
#include "Instructor.h"
#include "Admin.h"
#include "sqlite3.h"


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ofstream;  //Write to file
using std::ifstream;  //read data from a file

using namespace std;


/*************************************************************************************************
 The callback() function is invoked for each result row coming out of the evaluated SQL statement
 1st argument - the 4th argument provided by sqlite3_exec() and is typically not used
 2nd argument - number of columns in the result
 3rd argument - an array of strings containing the fields in that row
 4th argument - an array of strings containing the names of the columns
*************************************************************************************************/
static int callback(void* data, int argc, char** argv, char** azColName)
{
	int i;

	for (i = 0; i < argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");

	return 0;
}

//helper function made by Omar
bool authenticate(sqlite3* db,
	const std::string& user,
	const std::string& pass,
	std::string& roleOut,
	int& idOut)
{
	const char* sql =
		"SELECT ROLE, USER_ID "
		"FROM LOGIN "
		"WHERE USERNAME = ?1 AND PASSWORD = ?2;";

	sqlite3_stmt* stmt = nullptr;
	if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
		return false;

	sqlite3_bind_text(stmt, 1, user.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, pass.c_str(), -1, SQLITE_STATIC);

	bool ok = (sqlite3_step(stmt) == SQLITE_ROW);
	if (ok) {
		roleOut = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
		idOut = sqlite3_column_int(stmt, 1);
	}
	sqlite3_finalize(stmt);
	return ok;
}

// Instructor console menu would not work correctly in a cpp and header file - Omar 
static int print_cb(void*, int n, char** v, char**)
{
	for (int i = 0; i < n; ++i)
		std::cout << (v[i] ? v[i] : "NULL") << '\t';
	std::cout << '\n';
	return 0;
}

void instructor_ui(sqlite3* db, int myID)
{
	bool done = false;
	char* err = nullptr;
	int  rc;
	std::string sql;

	while (!done)
	{
		std::cout << "\nInstructor Menu\n"
			<< "1  View my schedule\n"
			<< "2  Print a course roster\n"
			<< "3  Search a student in my classes\n"
			<< "0  Log out\n"
			<< "Choice: ";
		int ch;  std::cin >> ch;

		switch (ch)
		{
		case 1:   // schedule
			sql = "SELECT CRN, TITLE, TIMES, DofW, "
				"SEMESTER||' '||YEAR "
				"FROM  COURSE "
				"WHERE INSTRUCTOR_ID = " + std::to_string(myID) + ';';
			std::cout << "\nCRN\tTitle\tTimes\tDays\tTerm\n";
			rc = sqlite3_exec(db, sql.c_str(), print_cb, nullptr, &err);
			if (rc) { std::cout << err << '\n'; sqlite3_free(err); }
			break;

		case 2: { // roster
			int crn;  std::cout << "CRN: ";  std::cin >> crn;
			sql = "SELECT s.Student_ID, st.NAME, st.SURNAME "
				"FROM   SCHEDULE s "
				"JOIN   STUDENT  st ON st.ID = s.Student_ID "
				"WHERE  s.Course_ID = " + std::to_string(crn) +
				" AND   EXISTS(SELECT 1 FROM COURSE c "
				"             WHERE c.CRN = s.Course_ID "
				"               AND c.INSTRUCTOR_ID = " + std::to_string(myID) + ");";
			std::cout << "\nID\tFirstName\tLastName\n";
			rc = sqlite3_exec(db, sql.c_str(), print_cb, nullptr, &err);
			if (rc) { std::cout << err << '\n'; sqlite3_free(err); }
			break;
		}

		case 3: { // student search
			int sid;  std::cout << "Student ID: ";  std::cin >> sid;
			sql = "SELECT c.CRN, c.TITLE "
				"FROM   COURSE  c "
				"JOIN   SCHEDULE s ON s.Course_ID = c.CRN "
				"WHERE  c.INSTRUCTOR_ID = " + std::to_string(myID) +
				" AND   s.Student_ID   = " + std::to_string(sid) + ';';
			std::cout << "\nCourses that student " << sid << " takes with you:\n"
				<< "CRN\tTitle\n";
			rc = sqlite3_exec(db, sql.c_str(), print_cb, nullptr, &err);
			if (rc) { std::cout << err << '\n'; sqlite3_free(err); }
			break;
		}

		case 0:
			done = true;                     // leave menu ? log out
			break;

		default:
			std::cout << "Invalid choice.\n";
		}
	}
}

void admin_ui(sqlite3* db, int myID) //made by Hong inspired by Omar
{

	char* messageError;

	int check;

	string sqlcommands;//used frequently for calling commands to cause changes especially calling methods to sql

	int choice; //user input choice

	bool loop = true;

	int exit;

	//open the database

	//Admin(string first, string last, int ID, string e, string t, string o) : User(first, last, ID, e)
	Admin adctrl("Admin", "Astrator", myID, "astratora", "trap", "reddit"); //control admin

	/*
	cout << "** ADMIN CONTROLS SELECT YOUR CONTROLS ** " << endl << endl
		<< "1. Search Course (Default)" << endl
		<< "2. Search Course (by Parameters)" << endl
		<< "3. Add Course" << endl
		<< "4. Remove Course" << endl
		<< "5. Add User" << endl
		<< "6. Remove User" << endl
		<< "7. Change Instructor to Course" << endl
		<< "8. Add/Remove student from Course" << endl << endl
		<< "Choice: " << endl;

	cin >> sqlcommands;
	*/

	while (loop)
	{
		cout << "** ADMIN CONTROLS SELECT YOUR CONTROLS ** " << endl << endl
			<< "1. Search Course (Default)" << endl
			<< "2. Search Course (by Parameters)" << endl
			<< "3. Add Course" << endl
			<< "4. Remove Course" << endl
			<< "5. Add User" << endl
			<< "6. Remove User" << endl
			<< "7. Change Instructor to Course" << endl
			<< "8. Add/Remove student from Course" << endl
			<< "0. Exit" << endl << endl
			<< "Choice: " << endl;

		cin >> choice;

		switch (choice)
		{
		case 1:
			//prints all courses
			sqlcommands = adctrl.print_course();
			sqlite3_exec(db, sqlcommands.c_str(), callback, nullptr, &messageError); //prints all courses
			break;

		case 2:
			//Does Search Default by CRN
			sqlcommands = adctrl.search_courseD();
			sqlite3_exec(db, sqlcommands.c_str(), callback, nullptr, &messageError);
			break;

		case 3:
			//ADD Course
			sqlcommands = adctrl.add_course();
			exit = sqlite3_exec(db, sqlcommands.c_str(), callback, nullptr, &messageError);
			if (exit != SQLITE_OK) {
				cerr << "Error creating LOGIN table: " << messageError << '\n';
				sqlite3_free(messageError);
			}
			else {
				cout << "** Course Added **\n";
			}
			break;

		case 4://issue
			//Remove Course 
			adctrl.remove_course(db);
			break;

		case 5:
			//add user
			sqlcommands = adctrl.add_user(db);
			exit = sqlite3_exec(db, sqlcommands.c_str(), callback, nullptr, &messageError);
			if (exit != SQLITE_OK) {
				cerr << "Error creating LOGIN table: " << messageError << '\n';
				sqlite3_free(messageError);
			}
			else {
				cout << "** User Added **\n";
			}

			break;

		case 6://issue
			//remove user
			sqlcommands = adctrl.remove_user();
			exit = sqlite3_exec(db, sqlcommands.c_str(), nullptr, nullptr, &messageError);
			if (exit != SQLITE_OK) {
				cerr << "Error creating LOGIN table: " << messageError << '\n';
				sqlite3_free(messageError);
			}
			else {
				cout << "** User Removed **\n";
			}
			break;

		case 7:
			//Change Instructor to Course
			sqlcommands = adctrl.link_instructor();
			exit = sqlite3_exec(db, sqlcommands.c_str(), callback, nullptr, &messageError);
			if (exit != SQLITE_OK) {
				cerr << "Error creating LOGIN table: " << messageError << '\n';
				sqlite3_free(messageError);
			}
			else {
				cout << "** Instructor Connected **\n";
			}
			break;

		case 8:
			//Add/Remove student from Course
			sqlcommands = adctrl.link_student();
			exit = sqlite3_exec(db, sqlcommands.c_str(), callback, nullptr, &messageError);
			if (exit != SQLITE_OK) {
				cerr << "Error creating LOGIN table: " << messageError << '\n';
				sqlite3_free(messageError);
			}
			else {
				cout << "** Altered Schedule **\n";
			}
			break;
		case 0:
			//exit
			loop = false;
			break;

		default:
			cout << "** Invalid Option **" << endl;
			break;
		}
	}

	sqlcommands.clear();

}

void student_ui(sqlite3* db, int myID) //made by Hong in prep for Felix
{

	char* messageError;

	int check;

	string sqlcommands;//used frequently for calling commands to cause changes especially calling methods to sql

	int choice; //user input choice

	bool loop = true;

	int exit;

	//open the database

	//Student(string first, string last, int ID, string e, int g, string m) : User(first, last, ID, e)
	Student stuctrl("Student", "Student", myID, "student@wit.edu", 4, "reddit"); //control admin

	/*
	cout << "** ADMIN CONTROLS SELECT YOUR CONTROLS ** " << endl << endl
		<< "1. Search Course (Default)" << endl
		<< "2. Search Course (by Parameters)" << endl
		<< "3. Add Course" << endl
		<< "4. Remove Course" << endl
		<< "5. Add User" << endl
		<< "6. Remove User" << endl
		<< "7. Change Instructor to Course" << endl
		<< "8. Add/Remove student from Course" << endl << endl
		<< "Choice: " << endl;

	cin >> sqlcommands;
	*/

	while (loop)
	{
		cout << "** WELCOME BACK SELECT YOUR CONTROLS ** " << endl << endl
			<< "1. Search Course (Default)" << endl
			<< "2. Search Course (by Parameters)" << endl
			<< "3. Add/Remove Course" << endl
			<< "4. Print Schedule" << endl
			<< "0. Exit" << endl
			<< "Choice: " << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			//prints all courses
			sqlcommands = stuctrl.print_course();
			sqlite3_exec(db, sqlcommands.c_str(), callback, nullptr, &messageError); //prints all courses
			break;

		case 2:
			//Does Search Default by CRN
			sqlcommands = stuctrl.search_courseD();
			sqlite3_exec(db, sqlcommands.c_str(), callback, nullptr, &messageError);
			break;

		case 3:
			//ADD/remove Course
			sqlcommands = stuctrl.add_remove_course(db, stuctrl.show_ID());
			sqlite3_exec(db, sqlcommands.c_str(), callback, nullptr, &messageError);
			break;

		case 4:
			//Print Schedule 
			sqlcommands = stuctrl.print_schedule(stuctrl.show_ID());
			sqlite3_exec(db, sqlcommands.c_str(), callback, nullptr, &messageError);
			break;
		case 0:
			//exit
			loop = false;
			break;

		default:
			cout << "** Invalid Option **" << endl;
			break;
		}
	}

	sqlcommands.clear();

}

//Omar's function for using database
void execute(sqlite3* DB, const char* sql) {
	char* err = nullptr;
	if (sqlite3_exec(DB, sql, nullptr, nullptr, &err) != SQLITE_OK) {
		std::cerr << "SQL error: " << err << '\n';
		sqlite3_free(err);
	}
}

// - Omar Code that will be transferred later 
void instructor_ui(sqlite3* db, int instructorID); // Instead of making a whole other file just for this

// I also did the same with admin -Hong
void admin_ui(sqlite3* db, int instructorID);


int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


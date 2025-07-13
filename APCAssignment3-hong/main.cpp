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

void admin_ui(sqlite3* db, int myID)
{
	char* messageError;

	string sqlcommands;//used frequently for calling commands to cause changes especially calling methods to sql

	int choice; //user input choice

	bool loop = true;

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
			sqlite3_exec(db, sqlcommands.c_str(), callback, nullptr, &messageError);
			break;

		case 4://issue
			//Remove Course 
			adctrl.remove_course();
			break;

		case 5:
			//add user
			sqlcommands = adctrl.add_user();
			sqlite3_exec(db, sqlcommands.c_str(), callback, nullptr, &messageError);
			break;

		case 6://issue
			//remove user
			adctrl.remove_user();
			sqlite3_exec(db, sqlcommands.c_str(), nullptr, nullptr, &messageError);
			break;

		case 7:
			//Change Instructor to Course
			sqlcommands = adctrl.link_instructor();
			sqlite3_exec(db, sqlcommands.c_str(), callback, nullptr, &messageError);
			break;

		case 8:
			//Add/Remove student from Course
			sqlcommands = adctrl.link_student();
			sqlite3_exec(db, sqlcommands.c_str(), callback, nullptr, &messageError);
			break;
		case 0:
			//exit
			loop = false;
			break;
		}
	}

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
	const char* dir = "assignment3.db";

	sqlite3* DB;

	string tableADMIN = "CREATE TABLE IF NOT EXISTS ADMIN(" //database Admin table
		"ID INTEGER PRIMARY KEY, "
		"NAME TEXT NOT NULL, "
		"SURNAME TEXT NOT NULL, "
		"TITLE TEXT NOT NULL,"
		"OFFICE TEXT NOT NULL,"
		"EMAIL TEXT NOT NULL); ";

	int exit = 0;

	exit = sqlite3_open("assignment3.db", &DB);		//open the database
	
	sqlite3_exec(DB, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);

	char* messageError;

	exit = sqlite3_exec(DB, tableADMIN.c_str(), nullptr, nullptr, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Create Table" << std::endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Table created Successfully" << std::endl;

	string tableInstructor = "CREATE TABLE IF NOT EXISTS INSTRUCTOR(" //database Instructor table
		"ID INTEGER PRIMARY KEY, "
		"NAME TEXT NOT NULL, "
		"SURNAME TEXT NOT NULL, "
		"TITLE TEXT NOT NULL,"
		"HIREYEAR INTEGER NOT NULL,"
		"DEPT TEXT NOT NULL,"
		"EMAIL TEXT NOT NULL); ";

	exit = sqlite3_exec(DB, tableInstructor.c_str(), nullptr, nullptr, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Create Table" << std::endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Table created Successfully" << std::endl;

	string tableStudent = "CREATE TABLE IF NOT EXISTS STUDENT("  //database Student table
		"ID INTEGER PRIMARY KEY, "
		"NAME TEXT NOT NULL, "
		"SURNAME TEXT NOT NULL, "
		"GRADYEAR INTEGER NOT NULL,"
		"MAJOR TEXT NOT NULL,"
		"EMAIL TEXT NOT NULL); ";

	exit = sqlite3_exec(DB, tableStudent.c_str(), nullptr, nullptr, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Create Table" << std::endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Table created Successfully" << std::endl;

	sqlite3_exec(DB, "DROP TABLE IF EXISTS COURSE;", nullptr, nullptr, &messageError);

	string tableCourse = "CREATE TABLE IF NOT EXISTS COURSE("
		"CRN INTEGER PRIMARY KEY, "
		"TITLE TEXT NOT NULL, "
		"DEPARTMENT TEXT NOT NULL, "
		"TIMES TEXT NOT NULL, "
		"TIMESTART INTEGER NOT NULL, "
		"TIMEEND INTEGER NOT NULL, "
		"DofW TEXT NOT NULL, "
		"SEMESTER TEXT NOT NULL, "
		"YEAR INTEGER NOT NULL, "
		"CREDITS INTEGER NOT NULL, "
		"INSTRUCTOR_ID INTEGER, "
		"FOREIGN KEY (INSTRUCTOR_ID) REFERENCES INSTRUCTOR(ID) ON DELETE CASCADE"
		");";

	exit = sqlite3_exec(DB, tableCourse.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Create Table" << std::endl;
		sqlite3_free(messageError);
	}
	else
	{
		cout << "Table created Successfully" << std::endl;
	}

	string tableSchedule = "CREATE TABLE IF NOT EXISTS SCHEDULE("
		"Course_ID INTEGER, "
		"Student_ID INTEGER, "
		"FOREIGN KEY (Course_ID) REFERENCES COURSE(CRN) ON DELETE CASCADE,"
		"FOREIGN KEY (Student_ID) REFERENCES STUDENT(ID) ON DELETE CASCADE,"
		"PRIMARY KEY(Course_ID, Student_ID)"
		");";

	exit = sqlite3_exec(DB, tableSchedule.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Create Table" << std::endl;
		sqlite3_free(messageError);
	}
	else
	{
		cout << "Table created Successfully" << std::endl;
	}

	//Omar's portion of the code with the logins (cleaned up in order by Hong)
	string tableLogin = R"(
    CREATE TABLE IF NOT EXISTS LOGIN (
        USERNAME TEXT PRIMARY KEY,
        PASSWORD TEXT NOT NULL,
        ROLE     TEXT NOT NULL CHECK (ROLE IN ('ADMIN','INSTRUCTOR','STUDENT')),
        USER_ID  INTEGER NOT NULL
		);
	)";

	exit = sqlite3_exec(DB, tableLogin.c_str(), nullptr, nullptr, &messageError);


	if (exit != SQLITE_OK) {
		cerr << "Error creating LOGIN table: " << messageError << '\n';
		sqlite3_free(messageError);
	}
	else {
		cout << "LOGIN table created successfully\n";
	}

	const char* seedLogin =
		"INSERT OR IGNORE INTO LOGIN VALUES "
		"('admin1','pass123','ADMIN',      30001),"
		"('fourierj', 'inst1', 'INSTRUCTOR', 20001),"
		"('stud1', 'ilovecpp','STUDENT',   10001);";


	exit = sqlite3_exec(DB, seedLogin, nullptr, nullptr, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Seeding LOGIN failed: " << messageError << '\n';
		sqlite3_free(messageError);
	}

	string queryClasses = R"(
		SELECT c.CRN, c.TITLE
		FROM COURSE c
		JOIN SCHEDULE s ON c.CRN = s.Course_ID
		WHERE s.Student_ID = 10001;
		)";

	sqlite3_exec(DB, queryClasses.c_str(), callback, NULL, &messageError);

	exit = sqlite3_exec(DB, queryClasses.c_str(), callback, nullptr, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error running query: " << messageError << endl;
		sqlite3_free(messageError);
	}
	else
	{
		cout << "Sucess Implementation" << std::endl;
	}

	//tables are all set from above
	/**********************************************************************************************************************************/

	/*
	sqlite3_prepare_v2(DB, sqlD, -1, &stmt, NULL); //preparing the update
	sqlite3_bind_int(stmt, 1, id); //change name of that row that matches with the ID number
	sqlite3_step(stmt); //run it
	sqlite3_finalize(stmt); //save
	exit = sqlite3_exec(DB, userInput.c_str(), callback, NULL, NULL); //permanant save
	*/

	sqlite3_stmt* stmt; //an all purpose variable for finalization and update changes

	const char* sqlC = "DELETE FROM COURSE WHERE ID = ?;";

	string sqlcommands;//used frequently for calling commands to cause changes especially calling methods to sql

	int choice; //user input choice

	bool loop = true;

	Admin adctrl("Admin", "Astrator", 1, "astratora", "trap", "reddit"); //control admin

	Instructor teactrl("Torn", "Tori", 2, "torii", "sensei", 2001, "TEAC"); //control instructor

	Student studctrl("Stu", "Dent", 3, "dents", 2022, "NONE"); //control student

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

	// Login/logout loop --> made by Omar
	while (true) {
		string username;
		cout << "Username (Q to quit): ";
		getline(std::cin, username);
		if (username == "Q") break;

		string password;
		cout << "Password: ";
		getline(std::cin, password);

		sqlite3_stmt* stmt;
		sqlite3_prepare_v2(DB,
			"SELECT ROLE, USER_ID FROM LOGIN WHERE USERNAME=? AND PASSWORD=?;",
			-1, &stmt, nullptr);
		sqlite3_bind_text(stmt, 1, username.c_str(), -1, nullptr);
		sqlite3_bind_text(stmt, 2, password.c_str(), -1, nullptr);

		if (sqlite3_step(stmt) == SQLITE_ROW) {
			std::string role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
			int userID = sqlite3_column_int(stmt, 1);
			sqlite3_finalize(stmt);

			if (role == "INSTRUCTOR") {
				instructor_ui(DB, userID);
			}
			else if (role == "ADMIN") //Hong's Addition
			{
				admin_ui(DB, userID);
			}
			/* student UI here
			else if (role == "STUDENT")
			{

			}
			*/
		}
		else {
			std::cout << "Invalid credentials.\n";
			sqlite3_finalize(stmt);
		}
	}
	sqlite3_close(DB);

	return 0;
}


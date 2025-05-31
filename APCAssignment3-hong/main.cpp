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

	exit = sqlite3_open("assignment3.db", &DB);			//open the database

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

	string tableCourse = "CREATE TABLE COURSE(" //database Course table
		"CRN INTEGER PRIMARY KEY, "
		"TITLE TEXT NOT NULL, "
		"DEPARTMENT TEXT NOT NULL, "
		"TIMES TEXT NOT NULL,"
		"DofW TEXT NOT NULL,"
		"SEMESTER TEXT NOT NULL,"
		"YEAR INTEGER NOT NULL,"
		"CREDITS INTEGER NOT NULL); ";

	exit = sqlite3_exec(DB, tableCourse.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Create Table" << std::endl;
		sqlite3_free(messageError);
	}
	else
		cout << "Table created Successfully" << std::endl;

	//Admin, Instructor, Student addition (as backup)
	//Create Course List (yes I stopped caring at this point)

	/*
	string sql("INSERT INTO ADMIN VALUES(30001, 'Margaret', 'Hamilton', 'President', 'Dobbs 1600', 'hamiltonm');"
		"INSERT INTO ADMIN VALUES(30002, 'Vera', 'Rubin', 'Registar', 'Wentworth 101', 'rubinv');"

		"INSERT INTO INSTRUCTOR VALUES(20001, 'Joseph', 'Fourier', 'Full Prof.', 1820, 'BSEE', 'fourierj');"
		"INSERT INTO INSTRUCTOR VALUES(20002, 'Nelson', 'Patrick', 'Full Prof.', 1994, 'HUSS', 'patrickn');"
		"INSERT INTO INSTRUCTOR VALUES(20003, 'Galileo', 'Galilei', 'Full Prof.', 1600, 'BSAS', 'galileig');"
		"INSERT INTO INSTRUCTOR VALUES(20004, 'Alan', 'Turing', 'Associate Prof.', 1940, 'BSCO', 'turinga');"
		"INSERT INTO INSTRUCTOR VALUES(20005, 'Katie', 'Bouman', 'Associate Prof.', 2019, 'BCOS', 'boumank');"
		"INSERT INTO INSTRUCTOR VALUES(20006, 'Daniel', 'Bernouli', 'Associate Prof.', 1760, 'BSME', 'bernoulid');"

		"INSERT INTO STUDENT VALUES(10001, 'Isaac', 'Newton', 1668, 'BSAS', 'newtoni');"
		"INSERT INTO STUDENT VALUES(10002, 'Marie', 'Curie', 1903, 'BSAS', 'curiem');"
		"INSERT INTO STUDENT VALUES(10003, 'Nikola', 'Tesla', 1878, 'BSEE', 'teslan');"
		"INSERT INTO STUDENT VALUES(10004, 'Thomas', 'Edison', 1879, 'BSEE', 'edisont');"
		"INSERT INTO STUDENT VALUES(10005, 'John', 'von Neumann', 1923, 'BSCO', 'vonneumanj');"
		"INSERT INTO STUDENT VALUES(10006, 'Grace', 'Hopper', 1928, 'BCOS', 'hopperg');"
		"INSERT INTO STUDENT VALUES(10007, 'Mae', 'Jemison', 1981, 'BSCH', 'jamisonm');"
		"INSERT INTO STUDENT VALUES(10008, 'Mark', 'Dean', 1979, 'BSCO', 'deanm');"
		"INSERT INTO STUDENT VALUES(10009, 'Michael', 'Faraday', 1812, 'BSAS', 'faradaym');"
		"INSERT INTO STUDENT VALUES(10010, 'Ada', 'Lovelace', 1832, 'BCOS', 'lovelacea');"

		//main issue is that this is not being used
		"INSERT INTO COURSE VALUES(50001, 'Engrish', 'BSEE', '8:00 AM', 'M W F', 'Fall', 2022, 4);"
		"INSERT INTO COURSE VALUES(50002, 'Matting', 'HUSS', '10:00 AM', 'M W F', 'Winter', 2022, 4);"
		"INSERT INTO COURSE VALUES(50003, 'Blow Ups', 'BSAS', '10:00 AM', 'M W F', 'Fall', 2022, 4);"
		"INSERT INTO COURSE VALUES(50004, 'Torture Rooms', 'BSCO', '8:00 AM', 'M W F', 'Winter', 2022, 3);"
		"INSERT INTO COURSE VALUES(50005, 'Femboyant Architypes', 'BCOS', '8:00 AM', 'M W F', 'Fall', 2022, 3);"
		"INSERT INTO COURSE VALUES(50006, 'Eric Femboy Crisis Hotline', 'BSME', '7:00 PM', 'M W F', 'Winter', 2022, 2);"
	);
	*/

	string sql(
		//main issue is that this is not being used
		"INSERT INTO COURSE VALUES(50001, 'Engrish', 'BSEE', '8:00 AM', 'M W F', 'Fall', 2022, 4);"
		"INSERT INTO COURSE VALUES(50002, 'Matting', 'HUSS', '10:00 AM', 'M W F', 'Winter', 2022, 4);"
		"INSERT INTO COURSE VALUES(50003, 'Blow Ups', 'BSAS', '10:00 AM', 'M W F', 'Fall', 2022, 4);"
		"INSERT INTO COURSE VALUES(50004, 'Torture Rooms', 'BSCO', '8:00 AM', 'M W F', 'Winter', 2022, 3);"
		"INSERT INTO COURSE VALUES(50005, 'Femboyant Architypes', 'BCOS', '8:00 AM', 'M W F', 'Fall', 2022, 3);"
		"INSERT INTO COURSE VALUES(50006, 'Eric Femboy Crisis Hotline', 'BSME', '7:00 PM', 'M W F', 'Winter', 2022, 2);"
	);

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Data Fail" << std::endl;
		sqlite3_free(messageError);
	}
	else
	{
		cout << "Data Successfully Inserted" << std::endl;
	}

	/***********************************************
	 print all data in the table with SELECT * FROM
	 create string with query then execute
	 **********************************************/
	string query = "SELECT * FROM PROGRAMMER;"; //used later

	cout << endl << query << endl;		//print the string to screen

	// you need the callback function this time since there could be multiple rows in the table
	sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);


	/*

	Big note : considering we have the database involved heavily for program
	i.e. storage, functionality, classes
	We should assume that the login portion or creating the User b4 the actual program
	involves pulling straight from the database from either Admin, Instructor, or Student
	then between the case statements, a new user will be created/pulled based on
	that class object through a class pointer storage. Otherwise loop back to login because incorrect
	information

	Admin(string first, string last, int ID, string e, string t, string o);

	*/

	//test case for using the methods for sqlite
	Admin test("Admin", "Astrator", 1, "astratora", "trap", "reddit");

	//add student 1
	string userInput(test.add_user(3));

	exit = sqlite3_exec(DB, userInput.c_str(), callback, NULL, NULL);

	//add student 2
	string userInput2(test.add_user(3));

	exit = sqlite3_exec(DB, userInput2.c_str(), callback, NULL, NULL);

	//remove Instructor + Updating Admin
	//suppossed remove
	//string userInput2(test.remove_user(2));

	sqlite3_stmt* stmt; //an all purpose variable for finalization and update changes
	int id;
	const char* sqlD = "DELETE FROM INSTRUCTOR WHERE ID = ?;"; //a way to delete and remove
	cout << "Delete Instructor 1-6: ";
	cin >> id;
	id = id + 20000;

	sqlite3_prepare_v2(DB, sqlD, -1, &stmt, NULL); //preparing the update
	sqlite3_bind_int(stmt, 1, id); //change name of that row that matches with the ID number
	sqlite3_step(stmt); //run it
	sqlite3_finalize(stmt); //save 
	exit = sqlite3_exec(DB, userInput.c_str(), callback, NULL, NULL); //permanant save

	//Update
	const char* sqlU = "UPDATE ADMIN SET TITLE = ? WHERE ID = ?;"; //a way to update one line

	string nameChange;

	getline(cin, nameChange);
	cout << "Change Admin Title: ";
	getline(cin, nameChange);

	cout << "Admin 1 or 2: ";
	cin >> id;
	id = id + 30000;

	sqlite3_prepare_v2(DB, sqlU, -1, &stmt, NULL); //preparing the update
	sqlite3_bind_text(stmt, 1, nameChange.c_str(), -1, SQLITE_STATIC); //change name 
	sqlite3_bind_int(stmt, 2, id); //change name of that row that matches with the ID number
	sqlite3_step(stmt); //run it
	sqlite3_finalize(stmt); //save 

	sqlite3_close(DB);

	return 0;
}


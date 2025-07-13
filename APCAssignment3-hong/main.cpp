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


void admin_ui(sqlite3* db, int myID)
{
	char* messageError;

	string sqlcommands;//used frequently for calling commands to cause changes especially calling methods to sql

	int choice; //user input choice

	bool loop = true;

	Admin adctrl("Admin", "Astrator", 1, "astratora", "trap", "reddit"); //control admin

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

	/*
	string sql(
		
		"INSERT INTO ADMIN VALUES(30001, 'Margaret', 'Hamilton', 'President', 'Dobbs 1600', 'hamiltonm');"
		"INSERT INTO ADMIN VALUES(30002, 'Vera', 'Rubin', 'Registar', 'Wentworth 101', 'rubinv');"

		"INSERT INTO INSTRUCTOR VALUES(20001, 'Joseph', 'Fourier', 'Full Prof.', 1820, 'BSEE', 'fourierj');"
		"INSERT INTO INSTRUCTOR VALUES(20002, 'Nelson', 'Patrick', 'Full Prof.', 1994, 'ENGL', 'patrickn');"
		"INSERT INTO INSTRUCTOR VALUES(20003, 'Galileo', 'Galilei', 'Full Prof.', 1600, 'SCIE', 'galileig');"
		"INSERT INTO INSTRUCTOR VALUES(20004, 'Alan', 'Turing', 'Associate Prof.', 1940, 'BSCO', 'turinga');"
		"INSERT INTO INSTRUCTOR VALUES(20005, 'Katie', 'Bouman', 'Associate Prof.', 2019, 'BCOS', 'boumank');"
		"INSERT INTO INSTRUCTOR VALUES(20006, 'Daniel', 'Bernouli', 'Associate Prof.', 1760, 'MECH', 'bernoulid');"
		"INSERT INTO INSTRUCTOR VALUES(20007, 'Joseph', 'Stalin', 'Full Prof.', 1940, 'ENGL', 'stalinj');"//
		"INSERT INTO INSTRUCTOR VALUES(20008, 'Keith', 'Zengel', 'Full Prof.', 1994, 'SCIE', 'zengelk');"
		"INSERT INTO INSTRUCTOR VALUES(20009, 'Estaban', 'Carlos', 'Full Prof.', 1989, 'ARCH', 'carlose');"
		"INSERT INTO INSTRUCTOR VALUES(20010, 'Alan', 'Fortner', 'Associate Prof.', 1982, 'BSCO', 'fortnera');"
		"INSERT INTO INSTRUCTOR VALUES(20011, 'Katie', 'Pernelli', 'Associate Prof.', 2009, 'MATH', 'pernellik');"
		"INSERT INTO INSTRUCTOR VALUES(20012, 'Daniel', 'Astray', 'Associate Prof.', 2001, 'COMP', 'astrayd');"
		"INSERT INTO INSTRUCTOR VALUES(20013, 'Hopner', 'Jones', 'Full Prof.', 2002, 'COMP', 'hopnerj');"
		"INSERT INTO INSTRUCTOR VALUES(20014, 'Nell', 'Gibs', 'Full Prof.', 1978, 'ENGL', 'gibsn');"
		"INSERT INTO INSTRUCTOR VALUES(20015, 'Eathon', 'Notner', 'Full Prof.', 1987, 'MATH', 'notnere');"

		"INSERT INTO STUDENT VALUES(10001, 'Isaac', 'Newton', 1668, 'SCIE', 'newtoni');"
		"INSERT INTO STUDENT VALUES(10002, 'Marie', 'Curie', 1903, 'ENGL', 'curiem');"
		"INSERT INTO STUDENT VALUES(10003, 'Nikola', 'Tesla', 1878, 'ELEC', 'teslan');"
		"INSERT INTO STUDENT VALUES(10004, 'Thomas', 'Edison', 1879, 'ELEC', 'edisont');"
		"INSERT INTO STUDENT VALUES(10005, 'John', 'von Neumann', 1923, 'MATH', 'vonneumanj');"
		"INSERT INTO STUDENT VALUES(10006, 'Grace', 'Hopper', 1928, 'SCIE', 'hopperg');"
		"INSERT INTO STUDENT VALUES(10007, 'Mae', 'Jemison', 1981, 'ENGL', 'jamisonm');"
		"INSERT INTO STUDENT VALUES(10008, 'Mark', 'Dean', 1979, 'MECH', 'deanm');"
		"INSERT INTO STUDENT VALUES(10009, 'Michael', 'Faraday', 1824, 'SCIE', 'faradaym');"
		"INSERT INTO STUDENT VALUES(10010, 'Ada', 'Lovelace', 1832, 'MECH', 'lovelacea');"
		"INSERT INTO STUDENT VALUES(10011, 'Angela', 'Smith', 1832, 'ELEC', 'smitha');"
		"INSERT INTO STUDENT VALUES(10012, 'David', 'Smith', 1832, 'ELEC', 'smithd');"
		"INSERT INTO STUDENT VALUES(10013, 'John', 'Hopper', 1832, 'BCOS', 'hopperj');"
		"INSERT INTO STUDENT VALUES(10014, 'Samuel', 'Jackson', 1832, 'BCOS', 'jacksons');"
		"INSERT INTO STUDENT VALUES(10015, 'Chris', 'Le', 2022, 'BSCO', 'lec');"
		"INSERT INTO STUDENT VALUES(10016, 'Johnathan', 'Kimbley', 2021, 'MATH', 'kimbleyj');"
		"INSERT INTO STUDENT VALUES(10017, 'William', 'Flores', 2020, 'MECH', 'floresw');"
		"INSERT INTO STUDENT VALUES(10018, 'Christian', 'Milord', 2022, 'COMP', 'milordc');"
		"INSERT INTO STUDENT VALUES(10019, 'Jeury', 'Gonzalez', 2023, 'ARCH', 'gonzalez');"
		"INSERT INTO STUDENT VALUES(10020, 'Hong', 'Luu', 2022, 'BSCO', 'luuh');"
		
		//main issue is that this is not being used
		"INSERT INTO COURSE VALUES(50001, 'English I', 'ENGL', '8:00 - 9:45 AM', 8, 10, 'TR', 'Fall', 2022, 4, 20002);"
		"INSERT INTO COURSE VALUES(50002, 'English II', 'ENGL', '10:00 - 11:45 AM', 10, 12, 'TR', 'Fall', 2022, 4, 20007);"
		"INSERT INTO COURSE VALUES(50003, 'English III', 'ENGL', '2:00 - 4:00 PM', 14, 16, 'MW', 'Fall', 2022, 4, 20014);"
		"INSERT INTO COURSE VALUES(50004, 'Calculus I', 'MATH', '8:00 - 9:45 AM', 8, 10, 'WF', 'Fall', 2022, 4, 20011);"
		"INSERT INTO COURSE VALUES(50005, 'Calculus II', 'MATH', '10:00 - 11:45 AM', 10, 12, 'MF', 'Fall', 2022, 4, 20015);"
		"INSERT INTO COURSE VALUES(50006, 'Calculus III', 'MATH', '2:00 - 4:00 PM', 14, 16, 'WF', 'Fall', 2022, 4, 20011);"
		"INSERT INTO COURSE VALUES(50007, 'Physics I', 'SCIE', '8:00 - 9:45 AM', 8, 10, 'MF', 'Fall', 2022, 4, 20008);"
		"INSERT INTO COURSE VALUES(50008, 'Physics II', 'SCIE', '10:00 - 11:45 AM', 10, 12, 'MF', 'Fall', 2022, 4, 20003);"
		"INSERT INTO COURSE VALUES(50009, 'Physics III', 'SCIE', '2:00 - 4:00 PM', 14, 16, 'WF', 'Fall', 2022, 4, 20008);"
		"INSERT INTO COURSE VALUES(50010, 'Computer Programming I', 'COMP', '8:00 - 10:00 AM', 8, 10, 'TF', 'Fall', 2022, 4, 20012);"
		"INSERT INTO COURSE VALUES(50011, 'Computer Programming II', 'COMP', '10:00 - 11:46 AM', 10, 12, 'TR', 'Fall', 2022, 4, 20013);"
		"INSERT INTO COURSE VALUES(50012, 'Computer Programming III', 'COMP', '2:00 - 4:00 PM', 14, 16, 'WR', 'Fall', 2022, 4, 20012);"
		"INSERT INTO COURSE VALUES(50013, 'Mechanics', 'MECH', '8:00 - 10:00 AM', 8, 10, 'MR', 'Spring', 2022, 4, 20006);"
		"INSERT INTO COURSE VALUES(50014, 'Mechanics', 'MECH', '1:00 - 3:00 PM', 13, 15, 'MW', 'Spring', 2022, 4, 20006);"
		"INSERT INTO COURSE VALUES(50015, 'Circuit Theory I', 'ELEC', '8:00 - 9:45 AM', 8, 10, 'TR', 'Spring', 2022, 4, 20001);"
		"INSERT INTO COURSE VALUES(50016, 'Circuit Theory II', 'ELEC', '10:00 - 11:45 AM', 10, 12, 'MW', 'Spring', 2022, 4, 20001);"
		"INSERT INTO COURSE VALUES(50017, 'Circuit Theory I Lab', 'ELEC', '8:00 - 10:00 AM', 8, 10, 'F', 'Spring', 2022, 4, 20001);"
		"INSERT INTO COURSE VALUES(50018, 'Circuit Theory II Lab', 'ELEC', '1:00 - 3:00 PM', 13, 15, 'R', 'Spring', 2022, 4, 20001);"
		"INSERT INTO COURSE VALUES(50019, 'Architecture Assembly', 'ARCH', '2:00 - 4:00 PM', 14, 16, 'TF', 'Spring', 2022, 4, 20009);"
		"INSERT INTO COURSE VALUES(50020, 'Visual Parameters', 'ARCH', '10:00 - 11:45 AM', 10, 12, 'TR', 'Spring', 2022, 4, 20009);"
		"INSERT INTO COURSE VALUES(50021, 'Visual Parameters', 'ARCH', '10:00 - 11:45 AM', 10, 12, 'TR', 'Spring', 2022, 4, 20009);"
	);

	exit = sqlite3_exec(DB, sql.c_str(), nullptr, nullptr, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Data Fail" << std::endl;
		sqlite3_free(messageError);
	}
	else
	{
		cout << "Data Successfully Inserted" << std::endl;
	}
	
	
	string queryLogin = R"(
		SELECT g.name AS disliked_game
		FROM Player p
		JOIN PlayerDislikes pd ON p.id = pd.player_id
		JOIN Game g ON pd.game_id = g.id
		WHERE p.username = 'ReHong';
		)";
	

	//database is not saved yet
	//main issue is that this is not being used
	//

	/*
	string reset = "DELETE FROM COURSE;";

	exit = sqlite3_exec(DB, reset.c_str(), nullptr, nullptr, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Data Fail" << std::endl;
		sqlite3_free(messageError);
	}
	else
	{
		cout << "Data Erased" << std::endl;
	}
	*/

	/*
	sql = R"(
		INSERT INTO COURSE VALUES(50001, 'English I', 'ENGL', '8:00 - 9:45 AM', 8, 10, 'TR', 'Fall', 2022, 4, 20002);
		INSERT INTO COURSE VALUES(50002, 'English II', 'ENGL', '10:00 - 11:45 AM', 10, 12, 'TR', 'Fall', 2022, 4, 20007);
		INSERT INTO COURSE VALUES(50003, 'English III', 'ENGL', '2:00 - 4:00 PM', 14, 16, 'MW', 'Fall', 2022, 4, 20014);
		INSERT INTO COURSE VALUES(50004, 'Calculus I', 'MATH', '8:00 - 9:45 AM', 8, 10, 'WF', 'Fall', 2022, 4, 20011);
		INSERT INTO COURSE VALUES(50005, 'Calculus II', 'MATH', '10:00 - 11:45 AM', 10, 12, 'MF', 'Fall', 2022, 4, 20015);
		INSERT INTO COURSE VALUES(50006, 'Calculus III', 'MATH', '2:00 - 4:00 PM', 14, 16, 'WF', 'Fall', 2022, 4, 20011);
		INSERT INTO COURSE VALUES(50007, 'Physics I', 'SCIE', '8:00 - 9:45 AM', 8, 10, 'MF', 'Fall', 2022, 4, 20008);
		INSERT INTO COURSE VALUES(50008, 'Physics II', 'SCIE', '10:00 - 11:45 AM', 10, 12, 'MF', 'Fall', 2022, 4, 20003);
		INSERT INTO COURSE VALUES(50009, 'Physics III', 'SCIE', '2:00 - 4:00 PM', 14, 16, 'WF', 'Fall', 2022, 4, 20008);
		INSERT INTO COURSE VALUES(50010, 'Computer Programming I', 'COMP', '8:00 - 10:00 AM', 8, 10, 'TF', 'Fall', 2022, 4, 20012);
		INSERT INTO COURSE VALUES(50011, 'Computer Programming II', 'COMP', '10:00 - 11:46 AM', 10, 12, 'TR', 'Fall', 2022, 4, 20013);
		INSERT INTO COURSE VALUES(50012, 'Computer Programming III', 'COMP', '2:00 - 4:00 PM', 14, 16, 'WR', 'Fall', 2022, 4, 20012);
		INSERT INTO COURSE VALUES(50013, 'Mechanics', 'MECH', '8:00 - 10:00 AM', 8, 10, 'MR', 'Spring', 2022, 4, 20006);
		INSERT INTO COURSE VALUES(50014, 'Mechanics', 'MECH', '1:00 - 3:00 PM', 13, 15, 'MW', 'Spring', 2022, 4, 20006);
		INSERT INTO COURSE VALUES(50015, 'Circuit Theory I', 'ELEC', '8:00 - 9:45 AM', 8, 10, 'TR', 'Spring', 2022, 4, 20001);
		INSERT INTO COURSE VALUES(50016, 'Circuit Theory II', 'ELEC', '10:00 - 11:45 AM', 10, 12, 'MW', 'Spring', 2022, 4, 20001);
		INSERT INTO COURSE VALUES(50017, 'Circuit Theory I Lab', 'ELEC', '8:00 - 10:00 AM', 8, 10, 'F', 'Spring', 2022, 4, 20001);
		INSERT INTO COURSE VALUES(50018, 'Circuit Theory II Lab', 'ELEC', '1:00 - 3:00 PM', 13, 15, 'R', 'Spring', 2022, 4, 20001);
		INSERT INTO COURSE VALUES(50019, 'Architecture Assembly', 'ARCH', '2:00 - 4:00 PM', 14, 16, 'TF', 'Spring', 2022, 4, 20009);
		INSERT INTO COURSE VALUES(50020, 'Visual Parameters', 'ARCH', '10:00 - 11:45 AM', 10, 12, 'TR', 'Spring', 2022, 4, 20009);
	)";

	exit = sqlite3_exec(DB, sql.c_str(), nullptr, nullptr, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Data Fail" << std::endl;
		sqlite3_free(messageError);
	}
	else
	{
		cout << "Data Successfully Inserted" << std::endl;
	}
	*/
/*
	string sql = R"(
		BEGIN TRANSACTION;
		INSERT INTO SCHEDULE(Course_ID, Student_ID) VALUES
		(50001, 10001),
		(50002, 10002),
		(50003, 10003),
		(50004, 10004),
		(50005, 10005),
		(50006, 10006),
		(50007, 10007),
		(50008, 10008),
		(50009, 10009),
		(50010, 10010),
		(50011, 10011),
		(50012, 10012),
		(50013, 10013),
		(50014, 10014),
		(50015, 10015),
		(50016, 10016),
		(50017, 10017),
		(50018, 10018),
		(50019, 10019),
		(50020, 10020);
		COMMIT;
	)";

	exit = sqlite3_exec(DB, sql.c_str(), nullptr, nullptr, &messageError);

	if (exit != SQLITE_OK)
	{
		std::cerr << "Error Data Fail" << std::endl;
		sqlite3_free(messageError);
	}
	else
	{
		cout << "Data Successfully Inserted" << std::endl;
	}
	
	*/
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
			sqlite3_exec(DB, sqlcommands.c_str(), callback, nullptr, &messageError); //prints all courses
			break;

		case 2:
			//Does Search Default by CRN
			sqlcommands = adctrl.search_courseD();
			sqlite3_exec(DB, sqlcommands.c_str(), callback, nullptr, &messageError);
			break;

		case 3:
			//ADD Course
			sqlcommands = adctrl.add_course();
			sqlite3_exec(DB, sqlcommands.c_str(), callback, nullptr, &messageError);
			break;

		case 4://issue
			//Remove Course 
			adctrl.remove_course();
			break;

		case 5:
			//add user
			sqlcommands = adctrl.add_user();
			sqlite3_exec(DB, sqlcommands.c_str(), callback, nullptr, &messageError);
			break;

		case 6://issue
			//remove user
			adctrl.remove_user();
			sqlite3_exec(DB, sqlcommands.c_str(), nullptr, nullptr, &messageError);
			break;

		case 7:
			//Change Instructor to Course
			sqlcommands = adctrl.link_instructor();
			sqlite3_exec(DB, sqlcommands.c_str(), callback, nullptr, &messageError);
			break;

		case 8:
			//Add/Remove student from Course
			sqlcommands = adctrl.link_student();
			sqlite3_exec(DB, sqlcommands.c_str(), callback, nullptr, &messageError);
			break;
		case 0:
			//exit
			loop = false;
			break;
		}
	}
	sqlite3_close(DB);

	return 0;
}


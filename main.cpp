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

int main() {
	
	User user = User("test", "test", 1);

	cout << user.show_first() << endl;
	cout << user.show_last() << endl;
	cout << user.show_ID() << endl;

	Student student = Student("First", "Last", 1);
	Admin admin = Admin("First", "last", 2);
	Instructor instructor = Instructor("First", "Last", 3);

	cout << admin.add_course() << endl;
	cout << admin.remove_course() << endl;
	cout << admin.add_user() << endl;
	cout << admin.remove_user() << endl;
	cout << admin.search_course() << endl; 
	cout << admin.print_course() << endl; 
	cout << admin.search_class() << endl; 
	cout << admin.print_class() << endl; 

	cout << instructor.print_schedule() << endl;
	cout << instructor.print_class() << endl;
	cout << instructor.search_course() << endl;

	cout << student.search_course() << endl;
	cout << student.add_course() << endl;
	cout << student.drop_course() << endl;
	cout << student.print_course() << endl;

	return 0;

}
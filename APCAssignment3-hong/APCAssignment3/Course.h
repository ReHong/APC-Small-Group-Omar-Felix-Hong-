#pragma once
#include <iostream>
#include <string>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ofstream;  //Write to file
using std::ifstream;  //read data from a file

class Course
{
	int CRN;
	string title;
	string department;
	string time;
	string DoW;
	string semester;
	int year;
	int credits;

public:
	Course(string first[], string last[], int ID[], string e[], string t[], string o[]);
};


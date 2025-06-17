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
	Course(int C[], string tit[], string dep[], string t[], string D[], string s[], int y, int c);
	int show_CRN();
	string show_title();
	string show_department();
	string show_time();
	string show_DoW();
	string show_semester();
	int show_year();
	int show_credits();

};


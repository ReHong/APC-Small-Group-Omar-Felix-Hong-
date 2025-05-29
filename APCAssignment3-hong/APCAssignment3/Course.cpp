#include "Course.h"

Course::Course(int C[], string tit[], string dep[], string t[], string D[], string s[], int y, int c)
{
	/*
	CRN = C;
	title = tit;
	department;
	time;
	DoW;
	semester;
	year;
	credits;
	*/
}

int Course::show_CRN()
{
	return CRN;
}

string Course::show_title()
{
	return title;
}

string Course::show_department()
{
	return department;
}

string Course::show_time()
{
	return time;
}

string Course::show_DoW()
{
	return DoW;
}

string Course::show_semester()
{
	return semester;
}

int Course::show_year()
{
	return year;
}

int Course::show_credits()
{
	return credits;
}
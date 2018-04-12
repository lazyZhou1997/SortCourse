#ifndef Course_CPP
#define Course_CPP

#include"Course.h"
Course::Course()
{
}

Course::Course(string mcode, string mname, short mstudyTime, short mterm)
{
	isLimit = false;
	code = mcode;
	name = mname;
	studyTime = mstudyTime;
	term = mterm;
}

Course::~Course()
{
}

void Course::setCode(string mcode)
{
	code = mcode;
}

string Course::getCode()
{
	return code;
}

void Course::setName(string mname)
{
	name = mname;
}

string Course::getName()
{
	return name;
}

void Course::setStudyTime(short mstudyTime)
{
	studyTime = mstudyTime;
}

short Course::getStudyTime()
{
	return studyTime;
}

void Course::setTerm(short mterm)
{
	term = mterm;
}

short Course::getTerm()
{
	return term;
}

void Course::addCondition(string code)
{
	isLimit = true;
	condition.push_back(code);
}

vector<string> Course::getCondition()
{
	return condition;
}
bool Course::IsLimit()
{
	return isLimit;
}
#endif // !Course_CPP

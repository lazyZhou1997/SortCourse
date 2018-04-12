#pragma once
#ifndef Course_h
#define Course_h 1

#include<vector>
#include<iostream>

using namespace std;

//测试通过 周秦春
//日期：2016/12/13/19:55
//作者：周秦春
//存储课程信息
class Course
{
public:
	Course(string code,string name,short studyTime,short term);
	Course();
	~Course();

	//课程编号
	void setCode(string code);
	string getCode();
	//课程名字
	void setName(string mname);
	string getName();
	//课程学时
	void setStudyTime(short mstudyTime);
	short getStudyTime();
	//课程开始学期
	void setTerm(short mterm);
	short getTerm();
	//课程前置条件
	void addCondition(string code);
	vector<string> getCondition();

	bool IsLimit();
private:
	string code;
	string name;
	short studyTime;
	short term;
	vector<string> condition;

	bool isLimit;//是否有前置条件
};

#endif // !Course.h

#pragma once
#ifndef ReadFile_h
#define ReadFile_h 1

#include"Course.h"

#include<fstream>

//测试通过 周秦春
//日期：2016/12/13/20:01
//作者：周秦春
//从文件中读取信息，并保存在Course类中,返回读取的课程总数
extern int getAllCourseFromFile(Course *courses,string fileName,int*nums);

#endif // !

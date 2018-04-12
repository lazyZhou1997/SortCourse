#ifndef readFile_H
#define readFile_H 1

#include"ReadFile.h"

//消除注释，并且存入新临时文件
static void xiao_chu_zhu_shi(fstream &in, fstream &out);
//从临时文件中读取文件的内容
static int du_qu_wen_jian(fstream &in,int*nums,Course*courses);

int getAllCourseFromFile(Course *courses,string fileName,int *nums)
{
	//打开文件
	fstream readFile(fileName,ios::in);
	if (!readFile)
	{
		cout << "打开文件失败！（readFile.cpp）！" << fileName.data();
		return -1;
	}
	//打开临时文件
	string tempFile;
	tempFile = fileName;
	tempFile += ".temp";
	fstream tempOutFile(tempFile, ios::out);
	if (!tempOutFile)
	{
		cout << "打开文件失败！（readFile.cpp）！" << tempFile.data();
		return -1;
	}

	//消除注释
	xiao_chu_zhu_shi(readFile, tempOutFile);
	tempOutFile.close();
	
	//读取文件
	fstream tempInFile(tempFile, ios::in);
	if (!tempInFile)
	{
		cout << "In打开文件失败！（readFile.cpp）！" << tempFile.data();
		return -1;
	}
	int numberOfCourse;
	numberOfCourse = du_qu_wen_jian(tempInFile, nums, courses);
	tempInFile.close();

	//释放资源
	readFile.close();
	return numberOfCourse;
}

void xiao_chu_zhu_shi(fstream &in, fstream &out)
{
	char ch;
	char lastCh = 'a';
	while (!in.eof())
	{

		//消除注释行
		ch = in.get();
		if ('/' == ch)
		{
			ch = in.get();
			if ('/' == ch)
			{
				while ('\n' != (ch = in.get()));
				lastCh = '\n';
				continue;
			}
			else
			{
				in.putback(ch);
				ch = '/';
			}
		}
		//写入临时文件
		if (!('\n'==lastCh&&'\n'==ch))
		{
			out.put(ch);
		}
		lastCh = ch;
	}
}

int du_qu_wen_jian(fstream &in,int *nums,Course* courses)
{
	for (int i = 0; i < 8; i++)
	{
		in >> nums[i];
	}

	int count = 0;
	char *chstemp = new char[50];
	char temp;
	short numtemp;
	while (!in.eof())
	{
		in >> chstemp;
		//由于末尾是空格
		if (in.eof())
		{
			break;
		}
		courses[count].setCode(chstemp);
		in >> chstemp;
		courses[count].setName(chstemp);
		in >> numtemp;
		courses[count].setStudyTime(numtemp);
		in >> numtemp;
		courses[count].setTerm(numtemp);
		
		while ('\n'!=(temp=in.get()))
		{
			if (' '!=temp&&'\t'!=temp)
			{
				in.putback(temp);
				in >> chstemp;
				courses[count].addCondition(chstemp);
			}
		}
		count++;
	}

	//释放资源
	delete chstemp;

	return count;
 }
#endif // !readFile_H
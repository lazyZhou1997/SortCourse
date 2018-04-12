#include"ReadFile.h"
#include"Graph.h"

#include<queue>
#include<iomanip>

#define h_term_num 8

//C:\Users\asus\Desktop\Sort\course_inf1.txt

//全局变量
queue<int>  q[h_term_num + 1];
char course_table[h_term_num + 1][10][6][100];//学期、节次、星期、课程名
int numsOfTerm[h_term_num];



//打印界面
void printMenu(char *fileName);
//建树
void makeGraph(Graph &gra, Course* courses, int numOfCourses);
//拓扑排序
bool topological_order(Graph &gra,Course* courses);
//将入度为0的顶点入对应的队列
void zero_indgree_push(Graph &gra, Course*courses);
//排课
bool range(int num, int term, char* name);
//辅助排课
bool range_one(int &week_day, int term, char* course_name);
bool range_two(int &week_day, int term, char* course_name);
bool range_three(int &week_day, int term, char* course_name);
//查找空课，并返回第一节课的节次
int find_one(int week_day, int term);
int find_two(int week_day, int term);
int find_three(int week_day, int term);


int main()
{
	//打印菜单，获取文件名
	char fileName[100];
	printMenu(fileName);
	
	//读取课程信息
	Course *temp = new Course[100];
	int allCourse;
	allCourse = getAllCourseFromFile(temp,fileName,numsOfTerm);
	if (allCourse < 0)
	{
		cout << "排课失败！" << endl;
		return 1;
	}

	//建图
	Graph gra(allCourse);
	makeGraph(gra, temp, allCourse);

	//清空课表
	for (int i = 1; i <=h_term_num; i++)                     //学期数
		for (int j = 1; j <= 9; j++)                        //节次
			for (int k = 1; k <= 5; k++)                     //星期   
				strcpy(course_table[i][j][k], "");

	//拓补排序
	if (!topological_order(gra, temp))
	{
		//释放资源
		delete[]temp;
		cout << "排课失败!" << endl;
		return 1;
	}

	cout << endl;
	cout << "排课完成！请指定要输入的文件：" << endl;
	cin >> fileName;

	//输出到文件
	fstream outcome(fileName, ios::out);
	if (!outcome)
	{
		cout << "打开文件失败!" << endl;
		return 0;
	}
	
	for (int i = 1; i <= 8; i++)
	{
		
		outcome << '\t' << '\t' << '\t' << '\t' << '\t' << "XX专业第" << i << "学期课表" << endl;
		outcome << endl;
		outcome <<setw(20)<< "名称";
		outcome << setw(20) << "星期一";
		outcome << setw(20) << "星期二";
		outcome << setw(20) << "星期三";
		outcome << setw(20) << "星期四";
		outcome << setw(20) << "星期五";
		outcome << endl;
		for (int j = 1; j <= 9; j++)
		{
			outcome << setw(20) << "第" << j << "节";
			for (int k = 1; k <= 5; k++)
			{
				
				outcome << setw(20) << course_table[i][j][k];
			}
			outcome << endl;
			outcome << endl;
		}

		outcome << endl;
		outcome << endl;
		outcome << endl;
		outcome << endl;
		outcome << endl;
		outcome << endl;
		outcome << endl;
	}

	cout << "输出完毕!" << endl;
	//释放资源
	delete[]temp;
	outcome.close();
	return 0;
}

//测试通过 周秦春
//日期：2016/12/17/11:20
//作者：周秦春
//打印界面，获取要排课的文件名
void printMenu(char *fileName)
{
	cout << "******************************************************" << endl;
	cout << "                 欢迎使用排课系统v1.0:)               " << endl;
	cout << "******************************************************" << endl;
	cout << "请输入课程文件名：" << endl;
	cin >> fileName;

	return;
}

void makeGraph(Graph &gra, Course* courses, int numOfCourses)
{
	vector<string> conditions;
	for (int i = 0; i < numOfCourses; i++)
	{
		if (courses[i].IsLimit())
		{
			conditions = courses[i].getCondition();
			for (int j = 0; j < (int)conditions.size(); j++)
			{
				for (int k = 0; k < numOfCourses; k++)
				{
					if (courses[k].getCode()==conditions.at(j))
					{
						gra.setEdge(k, i, 1);
						break;
					}
				}
			}
		}
	}

	return;
}

//拓补排序
bool topological_order(Graph &gra, Course* courses)
{

	zero_indgree_push(gra, courses);
	//对term中对应的课程排课
	int v;
	int size;
	Course course;
	char name[100];
	for (int term = 1; term <= h_term_num; term++)
	{
		size = (int)q[term].size();
		for (int i = 0; i<size; i++)
		{
			v = q[term].front();
			q[term].pop();
			//排课
			course = courses[v];
			strncpy(name, course.getName().data(), 99);
			range(course.getStudyTime(), term,name);
			
			//所有越v相邻的顶点入度减一
			gra.subOneInDegree(v);
			
			//入队
			int *inDegrees = gra.getAllIndegree();
			for (int j = 0; j < gra.n(); j++)
			{
				if (0 == inDegrees[j]&&(0==courses[j].getTerm()||courses[j].getTerm()>term)&&0==gra.getMark(j))
				{
					q[courses[j].getTerm()].push(j);
					gra.setMark(j, 1);//标记已经访问
				}
				else if(0 == inDegrees[j] && (courses[j].getTerm()>0 && courses[j].getTerm()<=term)&&0==gra.getMark(j))
				{
					cout << "课程冲突，排课结束！" << endl;
					return false;;
				}
				//C:\Users\asus\Desktop\Sort\course_inf1.txt
			}
			
		}

		for (int i = 0;i<numsOfTerm[term-1]-size; i++)
		{
			v = q[0].front();
			q[0].pop();
			//排课
			course = courses[v];
			strncpy(name, course.getName().data(), 99);
			range(course.getStudyTime(), term, name);
			//所有越v相邻的顶点入度减一
			gra.subOneInDegree(v);

			//入队
			int *inDegrees = gra.getAllIndegree();
			for (int j = 0; j < gra.n(); j++)
			{
				if (0 == inDegrees[j] && (0 == courses[j].getTerm() || courses[j].getTerm()>term) && 0 == gra.getMark(j))
				{
					q[courses[j].getTerm()].push(j);
					gra.setMark(j, 1);//标记已经访问
				}
				else if (0 == inDegrees[j] && (0 < courses[j].getTerm() && courses[j].getTerm()<=term)&& 0 == gra.getMark(j))
				{
					cout << "课程冲突，排课结束！" << endl;
					return false;
				}
			}
			
		}
	}

	for (int i = 0; i < gra.n(); i++)
	{
		if (0 == gra.getMark(i))
		{
			cout<<"并未排完所有课程，排课失败！";
			return false;
		}
	}
	
	return true;
}

void zero_indgree_push(Graph &gra,Course*courses)
{
	int *inDegrees = gra.getAllIndegree();
	//将度为0的点入对应的队列
	for (int i = 0; i < gra.n(); i++)
	{
		if (0 == inDegrees[i])
		{
			q[courses[i].getTerm()].push(i);
			gra.setMark(i, 1);//标记已经访问
		}
	}
}

//排课
bool range(int num, int term, char* name)
{
	int static week_day = 1;

	if (num==1)
	{
		if (range_one(week_day,term,name)==false)
		{
			return false;
		}
		else
		{
			week_day = (week_day < 4) ? (week_day + 2) : (week_day + 2 - 5);
			return true;
		}
	}
	else if (num % 3 == 0)
	{
		for (int i = 0; i < num/3; i++)
		{
			if (range_three(week_day, term, name) == false)
			{
				return false;
			}
			else
			{
				week_day = (week_day < 4) ? (week_day + 2) : (week_day + 2 - 5);
				return true;
			}
		}
	}
	else if (num % 2 == 0)
	{
		for (int i = 0; i < num / 2; i++)
		{
			if (range_two(week_day, term, name) == false)
			{
				return false;
			}
			else
			{
				week_day = (week_day < 4) ? (week_day + 2) : (week_day + 2 - 5);
				return true;
			}
		}
	}
	else if (5 == num)
	{
		if (range_three(week_day, term, name) == false)
		{
			return false;
		}
		else
		{
			week_day = (week_day < 4) ? (week_day + 2) : (week_day + 2 - 5);
			if (range_two(week_day, term, name) == false)
			{
				return false;
			}
			else
			{
				week_day = (week_day < 4) ? (week_day + 2) : (week_day + 2 - 5);
				return true;
			}
		}
	}
	return false;
}

//辅助排课，排一节课
bool range_one(int &week_day, int term, char* course_name)
{
	int local;
	for (int i = 0; i < 5; i++)
	{
		local = find_one(week_day, term);
		if (-1 == local)
		{
			week_day = (week_day < 4) ? (week_day + 2) : (week_day + 2 - 5);
		}
		else
		{
			strcpy(course_table[term][local][week_day], course_name);
			return true;
		}
	}
	return false;
}

//辅助排课，排两节课
bool range_two(int &week_day, int term, char* course_name)
{
	int local;
	for (int i = 0; i < 5; i++)
	{
		local = find_two(week_day, term);
		if (-1 == local)
		{
			week_day = (week_day < 4) ? (week_day + 2) : (week_day + 2 - 5);
		}
		else
		{
			strcpy(course_table[term][local][week_day], course_name);
			strcpy(course_table[term][local+1][week_day], course_name);
			return true;
		}
	}
	return false;

}

//辅助排课，排三节课
bool range_three(int &week_day, int term, char* course_name)
{
	int local;
	for (int i = 0; i < 5; i++)
	{
		local = find_three(week_day, term);
		if (-1 == local)
		{
			week_day = (week_day < 4) ? (week_day + 2) : (week_day + 2 - 5);
		}
		else
		{
			strcpy(course_table[term][local][week_day], course_name);
			strcpy(course_table[term][local+1][week_day], course_name);
			strcpy(course_table[term][local+2][week_day], course_name);
			return true;
		}
	}
	return false;
}

//查找一节空课，并返回第一节课的节次
int find_one(int week_day, int term)
{
	for (int i = 1; i <= 9; i++)
	{
		if (strlen(course_table[term][i][week_day])==0)
		{
			return i;
		}

	}
	return -1;
}

//查找两节空课，并返回第一节课的节次
int find_two(int week_day, int term)
{
	if (strlen(course_table[term][1][week_day]) == 0 && strlen(course_table[term][2][week_day]) == 0 )
	{
		return 1;
	}
	if (strlen(course_table[term][3][week_day]) == 0 && strlen(course_table[term][4][week_day]) == 0)
	{
		return 3;
	}
	if (strlen(course_table[term][8][week_day]) == 0 && strlen(course_table[term][9][week_day]) == 0)
	{
		return 8;
	}
	if (strlen(course_table[term][5][week_day]) == 0 && strlen(course_table[term][6][week_day]) == 0)
	{
		return 5;
	}

	return -1;
}

//查找三节空课，并返回第一节课的节次
int find_three(int week_day, int term)
{
	if (strlen(course_table[term][5][week_day]) == 0 && strlen(course_table[term][6][week_day]) == 0 &&
		strlen(course_table[term][7][week_day]) == 0)
	{
		return 5;
	}
	if (strlen(course_table[term][1][week_day]) == 0 && strlen(course_table[term][2][week_day]) == 0 &&
		strlen(course_table[term][3][week_day]) == 0)
	{
		return 1;
	}
	return -1;
}
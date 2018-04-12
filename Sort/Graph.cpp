#include"Graph.h"

Graph::Graph(int n)
{
	numVertex = n;
	numEdge = 0;

	mark = new int[numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		mark[i] = 0;
	}

	matrix = new int*[numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		matrix[i] = new int[numVertex];
	}
	
	for (int i = 0; i < numVertex; i++)
	{
		for (int j = 0; j < numVertex; j++)
		{
			matrix[i][j] = 0;
		}
	}


	//入度
	inDegree = new int[numVertex];
	for (int i = 0; i < numVertex; i++)
	{
		inDegree[i] = 0;
	}
}

Graph::~Graph()
{
	
	delete mark;
	for (int i = 0; i < numVertex; i++)
	{
		delete matrix[i];
	}
	delete matrix;
	delete inDegree;
}

int Graph::n()const
{
	return numVertex;
}

int Graph::e()const
{
	return numEdge;
}

int Graph::first(int v)const
{
	for (int i = 0; i < numVertex; i++)
	{
		if (0!=matrix[v][i])
		{
			return i;
		}
	}

	return numVertex;
}

int Graph::next(int v, int w)const
{
	for (int i = w+1; i < numVertex; i++)
	{
		if (0!=matrix[v][w])
		{
			return i;
		}
	}

	return numVertex;
}

void Graph::setEdge(int v, int w, int wgt)
{
	if (wgt<0)
	{
		std::cout << "权值不能为0";
	}

	if (0==matrix[v][w])
	{
		numEdge++;
		inDegree[w]++;
	}

	matrix[v][w] = wgt;
}

void Graph::deletEdge(int v, int w)
{
	if (0!=matrix[v][w])
	{
		numEdge--;
		inDegree[w]--;//入度减1；
		matrix[v][w] = 0;
	}
}

int Graph::weight(int v, int w)const
{
	return matrix[v][w];
}

int Graph::getMark(int v)const
{
	if (v<0||v>numVertex)
	{
		std::cout << "传入点无效";
	}
	return mark[v];
}

void Graph::setMark(int v, int val)
{
	if (v<0 || v>numVertex)
	{
		std::cout << "传入点无效";
	}

	mark[v] = val;
}

void Graph::subOneInDegree(int v)
{
	for (int i = 0; i < numVertex; i++)
	{
		if (0!=matrix[v][i])
		{
			inDegree[i]--;
		}
	}
}

int * Graph::getAllIndegree()
{
	return inDegree;
}

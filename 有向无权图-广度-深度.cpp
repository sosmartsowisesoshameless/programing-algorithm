#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

//无权有向图

class Dgraph
{
public:
	Dgraph(int numberofvertex = 0, int thenoedge = 0);
	~Dgraph();

	void printmatrix()  //打印矩阵
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
				cout << matrix[i][j] << " ";
			cout << endl;
		}
	}

	int numberofvertex()const { return n; }
	int numberofedge()const { return e; }
	bool directed()const { return true; }//有向
	bool weighted()const { return false; }//加权

	bool exitedge(int i, int j)const;//判断边（i，j)是否存在
	void insertedge(int i, int j);//插入边
	void eraseEdge(int i, int j);//删除边

	int inDegree(int thevertex)const;//顶点的入度
	int outDegree(int thevertex)const;//顶点的出度

	void bfs(int vstart, int vend);//广度优先遍历
	void dfs(int vstart, int vend);//深度优先遍历
	void Recursedfs(int *pre, int *visit, int &find, int vstart, int vend);//递归深度

	void print(int pre[], int start, int end);//打印路径


private:
	int n;//定点数
	int e;//边数
	int **matrix;//邻接矩阵
};

//构造/
Dgraph::Dgraph(int numberofvertex, int numofedge)
{
	if (numberofvertex < 0)
	{
		cout << "number of vertex must >=0" << endl;
		exit(1);//exit 是进程的退出
	}

	n = numberofvertex;
	e = numofedge;
	matrix = new int*[n + 1];
	for (int i = 0; i <= n; i++)
	{
		matrix[i] = new int[n + 1];
	}

	//初始化邻接矩阵
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			matrix[i][j] = 0;
}

//析构
Dgraph::~Dgraph()
{
	for (int i = 0; i <= n; i++)
		delete[] matrix[i];
	delete[] matrix;
	matrix = NULL;
}

//判断边（i，j)是否存在
bool Dgraph::exitedge(int i, int j)const
{
	if (i<1 || i>n || j<1 || j>n || matrix[i][j] == 0)
		return false;
	else
		return true;
}

//插入边
void Dgraph::insertedge(int i, int j)
{
	if (i < 1 || i > n || j < 1 || j > n || i == j)
	{
		cout << "(" << i << "," << j << ") is not a permissble edge";
		exit(1);
	}

	if (matrix[i][j] == 0)
		++e;
	matrix[i][j] = 1;
}

//删除边
void Dgraph::eraseEdge(int i, int j)
{
	if (i > 0 || i <= n || j > 0 || j <= n || matrix[i][j] != 0)
	{
		e--;
		matrix[i][j] = 0;
	}
}

//顶点的入度
int Dgraph::inDegree(int thevertex)const
{
	int sum = 0;
	if (thevertex<1 || thevertex>n)
	{
		cout << "no this vertex!" << endl;
		exit(1);
	}
	for (int i = 0; i < n + 1; i++)
	{
		if (matrix[i][thevertex] != 0)
			sum++;
	}
	return sum;
}

//顶点的出度
int Dgraph::outDegree(int thevertex)const
{
	int sum = 0;
	if (thevertex<1 || thevertex>n)
	{
		cout << "no this vertex!" << endl;
		exit(1);
	}
	for (int i = 0; i < n + 1; i++)
	{
		if (matrix[thevertex][i] != 0)
			sum++;
	}
	return sum;
}

//广度优先遍历
void Dgraph::bfs(int vstart, int vend)
{
	if (vstart == vend || vstart < 1 || vstart > n || vend < 1 || vend > n)
	{
		cout << "the start or the end is wrong!" << endl;
		return;
	}
	int *visited = new int(n + 1);
	int *pre = new int(n + 1);
	deque<int> v;

	for (int i = 0; i < n + 1; i++)
	{
		visited[i] = 0;
		pre[i] = 0;
	}

	/*for (int i = 0; i < n + 1; i++)
	{
		cout << pre[i]<<" ";
	}*/
	cout << endl;
	visited[vstart] = 1;
	/*for (int i = 0; i < n + 1; i++)
	{
		cout << visited[i] << " ";
	}*/
	v.push_back(1);
	//int a= v.front();
	int b = v.size();
	cout << v.size() << endl;
	/*while (!v.empty())
	{
		int cur = v.front();
		v.pop();
		for (int i = 1; i <= n; i++)
		{
			int tmp = matrix[cur][i];
			if (tmp == 1 && visited[i] == 0)
			{
				pre[tmp] = cur;
				if (tmp == vstart)
				{
					print(pre, vstart, vend);
					return;
				}
				else
				{
					visited[tmp] = 1;
					v.push(tmp);
				}
			}

		}
	}*/
}

//打印路径
void Dgraph::print(int pre[], int start, int end)
{
	while (pre[end] != 0 && end != start)
		print(pre, start, pre[end]);
	cout << end << ' ';
}

//深度优先遍历
void Dgraph::dfs(int vstart, int vend)
{
	if (vstart == vend || vstart < 1 || vstart > n || vend < 1 || vend > n)
	{
		cout << "the start or the end is wrong!" << endl;
		return;
	}
	int *visited = new int(n + 1);
	int *pre = new int(n + 1);

	fill(visited, visited + n + 1, 0);
	fill(pre, pre + n + 1, 0);

	visited[vstart] = 1;
	int find = 0;//查找标志

	Recursedfs(pre, visited, find, vstart, vend);

	if (find)
		print(pre, vstart, vend);
}
//递归深度
void Dgraph::Recursedfs(int *pre, int *visited, int &find, int cur, int vend)
{
	if (find)
		return;
	if (cur == vend)
	{
		find = 1;
		return;
	}

	for (int i = 1; i < n + 1; i++)
	{
		int tmp = matrix[cur][i];
		if (visited[tmp] != 1)
		{
			pre[tmp] = cur;
			visited[tmp] = 1;
			Recursedfs(pre, visited, find, tmp, vend);
		}
	}
	return;
}

void test()
{
	Dgraph g(7);
	g.insertedge(1, 2);
	g.insertedge(1, 3);
	g.insertedge(2, 6);
	g.insertedge(4, 6);
	g.insertedge(3, 4);
	g.insertedge(3, 5);
	g.insertedge(5, 6);
	g.insertedge(6, 7);

	g.printmatrix();


	g.bfs(1, 7);
	//g.dfs(1, 7);
}


int main()
{
	test();
	system("pause");
	return EXIT_SUCCESS;
}
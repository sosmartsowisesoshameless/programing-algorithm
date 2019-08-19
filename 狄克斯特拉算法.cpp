#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;


class DWgraph
{
public:
	DWgraph(int vertex = 0, int edge = 0);

	void insertedge(int i, int j, int w);//�����
	void deledge(int i, int j);//ɾ����
	void printedge();//��ӡ���еı�

	void Dijkstra(int i, int j);//�ҿ�˹�����㷨

private:
	int v;//������
	int e;//����
	vector<vector<int>> matrix;
};


DWgraph::DWgraph(int vertex, int edge)
{
	v = vertex;
	e = edge;
	for (int i = 0; i < v; i++)
	{
		vector<int> tmp;
		for (int j = 0; j < v; j++)
		{
			tmp.push_back(0);
		}
		matrix.push_back(tmp);
	}
}

//�����
void DWgraph::insertedge(int i, int j, int w)
{
	if (w == 0)
	{
		cout << "the weight cannot be zero!!" << endl;
		return;
	}
	if (matrix[i - 1][j - 1] == 0)
		e++;
	matrix[i - 1][j - 1] = w;
}

//ɾ����
void DWgraph::deledge(int i, int j)
{
	if (matrix[i - 1][j - 1] != 0)
	{
		matrix[i - 1][j - 1] = 0;
		e--;
	}
	else
	{
		cout << "No this edge!" << endl;
	}
}

//��ӡ���еı�
void DWgraph::printedge()
{
	cout << "Now we have the edge:" << endl;
	for(int i=0;i<v;i++)
		for (int j=0;j<v;j++)
		{
			if (matrix[i][j] != 0)
				cout << i + 1 << "->" << j + 1 <<':' << matrix[i][j] << endl;
		}
}

class Node
{
public:
	int num;
	int father;
	int cost;
	int flag;
};

//�����ʱ��ڵ�
int minfind(vector<Node> f,int e)
{
	int min = 10000;
	int next = 0;
	for (int i = 0; i < e; i++)
	{
		if (f[i].cost < min && f[i].flag == 0)
		{
			min = f[i].cost;
			next = i + 1;
		}
	}
	return next;
}
//��ӡ���·��
void min_print(vector<Node> f,int i,int j)
{
	stack<int> my_stack;
	int num = j;
	my_stack.push(num);
	do
	{
		num = f[num - 1].father;
		my_stack.push(num);
		
	} while (f[num - 1].father);
	cout << "��" << i << "����" << j << "�����·��Ϊ��" << endl;
	while (!my_stack.empty())
	{
		num = my_stack.top();
		cout << num;
		if (num != j)
			cout << "->";
		else
			cout << endl;
		my_stack.pop();
	}
	cout << "�ܺ�ʱΪ" << f[j - 1].cost << endl;
}
//�ҿ�˹�����㷨
void DWgraph::Dijkstra(int i, int j)
{
//�������
	vector<Node> form;
	for (int n = 0; n < v; n++)
	{
		Node temnode;
		temnode.num = n + 1;
		temnode.father = 0;
		temnode.cost = 10000;
		temnode.flag = 0;
		form.push_back(temnode);
	}

	form[i - 1].cost = 0;
	form[i - 1].flag = 1;
	int next = i;
	while (next)
	{

		//���½ڵ���Ϣ
		for(int a = 0; a < v; a++)
		{
			if (matrix[next - 1][a] != 0)
			{
				if (form[a].cost > form[next - 1].cost + matrix[next - 1][a])
				{
					form[a].cost = form[next - 1].cost + matrix[next - 1][a];
					form[a].father = next;
				}
			}
		}
		form[next - 1].flag = 1;
		//Ѱ���¸����Ϊ���ʽڵ�
		next = minfind(form, v);
	}
	if (form[j - 1].cost == 10000)
		cout << "There is no way to this node" << endl;
	else
		min_print(form,i, j);

}

void test()
{
	DWgraph g(8);
	g.insertedge(1, 2, 5);
	g.insertedge(1, 3, 1);
	g.insertedge(2, 5, 10);
	g.insertedge(3, 4, 5);
	g.insertedge(3, 6, 6);
	g.insertedge(4, 5, 3);
	g.insertedge(5, 8, 3);
	g.insertedge(6, 7, 2);
	g.insertedge(7, 8, 10);
	g.printedge();
	g.Dijkstra(1, 8);
}


int main()
{
	test();
	system("pause");
	return EXIT_SUCCESS;
}
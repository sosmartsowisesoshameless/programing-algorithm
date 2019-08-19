#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;


void donic_package(int v[], int w[], int c, int n)
{
	int **arr = new int*[n];
	for (int i = 0; i < n; i++)
		arr[i] = new int[c + 1];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < c + 1; j++)
		{
			if (i == 0)
				arr[i][j] = 0;
			else
			{
				if (w[i] > j)
					arr[i][j] = 0;
				else
				{
					arr[i][j] = v[i] + arr[i - 1][j - w[i]];
				}
				if (arr[i][j] < arr[i - 1][j])
					arr[i][j] = arr[i - 1][j];
			}
			cout.width(4);
			cout << arr[i][j];
		}
		cout << endl;
	}
	cout << "背包能放的最大价值为：" << arr[n - 1][c] << endl;
	for (int i = 0; i < n; i++)
		delete[] arr[i];
	delete[] arr;
}


void text()
{
	/*int v1[] = { 0,60,30,10,50,70 };
	int w1[] = { 0,4,2,1,3,6 };
	int n = 6;
	int cap = 16;//背包容量
	donic_package(v1, w1, cap, n);*/
	int v1[] = { 0,60,30,10,50,70 };
	int w1[] = { 0,4,2,1,3,6 };
	int n = 6;
	int cap = 16;//背包容量
	donic_package(v1, w1, cap, n);

}
int main()
{
	text();
	system("pause");
	return EXIT_SUCCESS;
}
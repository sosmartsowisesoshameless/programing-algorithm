#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <stdlib.h>
using namespace std;

//冒泡排序  
//最差时间复杂度：O(n^2)
//平均时间复杂度：O(n^2)
//平均空间复杂度：O(1)
//稳定性：稳定
void Bubble_sort(int *arr,int length)
{
	for (int i = length-1; i > 0; i--)
	{
		int flag = 0;//判断是否发生交换
		int tem;
		for (int j = 0; j < i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				flag = 1;
				tem = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tem;
			}
		}
		if (flag == 0)
			break;
	}
}

//选择排序 
//最差时间复杂度：O(n^2)
//平均时间复杂度：O(n^2)
//平均空间复杂度：O(1)
//稳定性：稳定
void Selection_sort(int *arr, int length)
{
	for (int i = 0; i < length - 1; i++)
	{
		int minnum = i;
		for (int j = i + 1; j < length; j++)
		{
			if (arr[j] < arr[minnum])
				minnum = j;
		}
		if (minnum != i)
		{
			int tem = arr[i];
			arr[i] = arr[minnum];
			arr[minnum] = tem;
		}
	}
}

//插入排序   最坏为为O(n^2)，最好为O(n)  从小到大
void Insert_sort(int *arr, int length)
{
	for (int i = 1; i < length ; i++)
	{
		int num = i;
		for (int j = 0; j < i; j++)
		{
			if (arr[j] > arr[num])
			{
				num = j;
				break;
			}
		}
		if (num != i)
		{
			int tem = arr[i];
			int k = i;
			while (k != num)
			{
				arr[k] = arr[k - 1];
				k--;
			}
			arr[k] = tem;
		}
	}
}

//希尔排序    时间复杂度为O(n^(3/2))
void Shell_sort(int arr[],int length)
{
	int space;//间距
	int i;
	int j;
	int tem;//临时数据
	space = length / 2;
	while (space != 0)
	{
		for (i = space; i < length; i++)
		{
			tem = arr[i];
			j = i-space;
			while (arr[j] > tem && j >= 0)
			{
				arr[j + space] = arr[j];
				j = j - space;
			}
			arr[j + space] = tem;
		}
		space = space / 2;
	}
}

//快速排序（分而治之）  时间复杂度为O(n log2 n)
void Quick_sort(int arr[], int _start,int _end)
{
	int tmp;
	if (_start < 0 || _end < 0)
		return;
	if (_start == _end)
		return;
	else if (_start == _end - 1)
	{
		if (arr[_start] > arr[_end])
		{
			tmp = arr[_start];
			arr[_start] = arr[_end];
			arr[_end] = tmp;
		}
		return;
	}
	else
	{
		int base = arr[_start];
		int start = _start+1;
		int end = _end;
		while (1)
		{
			while (arr[end] > base)
			{
				end--;
			}
			while (arr[start] < base && start < _end)
			{
				start++;
			}
			if (end > start)
			{
				tmp = arr[start];
				arr[start] = arr[end];
				arr[end] = tmp;
				start++;
				end--;
			}
			else 
			{
				arr[_start] = arr[end];
				arr[end] = base;
				if (end > _start + 1)
					Quick_sort(arr, _start, end - 1);
				if (end < _end - 1)
					Quick_sort(arr, end + 1, _end);
				break;
			}
		}
		return;
	}
}

//堆排序 时间复杂度为O(n log n),从小到大,建立大顶堆
//堆调整
void HeapAjust(int arr[],int nod,int size)
{
	int Last = size / 2 - 1;
	int Lchild;
	int Rchild;
	int max;
	int tmp;
	
	Lchild = (nod + 1) * 2 - 1;
	Rchild = (nod+ 1) * 2;
	if (Rchild < size && arr[Lchild] < arr[Rchild])
		max = Rchild;
	else
		max = Lchild;
	if (arr[nod] < arr[max])
	{
		tmp = arr[nod];
		arr[nod] = arr[max];
		arr[max] = tmp;
		if (max <= Last)
			HeapAjust(arr, max, size);
	}
}
void Heap_sort(int arr[], int length) 
{
	int tmp2;
	for (int i = length ; i >1; i--)
	{
		int LastNonLeaf = i / 2 - 1;
		for (int j = LastNonLeaf; j >= 0; j--)
		{
			HeapAjust(arr, j, i);
		}
		tmp2 = arr[0];
		arr[0] = arr[i - 1];
		arr[i - 1] = tmp2;
	}
}

//基数排序 ，需要很大的额外空间存放数据，  时间复杂度为O(n logp k),p为最大位数，k为最大值
void radix_sort(int arr[],int length)
{
	//寻找最大值，确定最高位数
	int max = 0;
	for (int i = 0; i < length; i++)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	int digit;//最高位数
	if (max > 0)
	{
		digit = 1;
		while (max /= 10)
			digit++;
	}
	int base = 1;
	for (int n = 1; n <= digit; n++,base = base * 10)
	{
		int tmp[10][50] = { 0 };//100大于length即可
		int remainder;
		for (int i = 0; i < length; i++)
		{
			remainder = (arr[i] / base) % 10;
			tmp[remainder][i] = arr[i];
		}
		int k = 0;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < length; j++)
			{
				if (tmp[i][j] != 0)
				{
					arr[k] = tmp[i][j];
					k++;
				}
			}
		}
	}
}

//合并排序法  
//最差时间复杂度：O(nlogn)
//平均时间复杂度：O(nlogn)
//平均空间复杂度：O(1)
//稳定性：稳定
void merge_sort(int arr[],int start,int end)
{
	if (start >= end)
		return;
	int mid = (start + end) / 2;
	merge_sort(arr, start, mid);
	merge_sort(arr, mid + 1, end);

	int Lstart = start;
	int Lend = mid;
	int Rstart = mid + 1;
	int Rend = end;
	int *tmp = new int[end - start + 1];
	int i = Lstart;
	int j = Rstart;
	int k = 0;
	while (i <= Lend && j <= Rend)
	{
		if (arr[i] <= arr[j])
		{
			tmp[k] = arr[i];
			i++;
			k++;
		}
		else
		{
			tmp[k] = arr[j];
			j++;
			k++;
		}
	}
	while (i <= Lend)
	{
		tmp[k] = arr[i];
		i++;
		k++;
	}
	while (j <= Rend)
	{
		tmp[k] = arr[j];
		j++;
		k++;
	}
	k = 0;
	for (int n = start; n <= end; n++, k++)
	{
		arr[n] = tmp[k];
	}
	delete []tmp;

}

void test()
{
	srand((unsigned)(time(NULL)));
	int length =12;
	int i;
	int MAX = 120;

	int num1[12];
	for (i = 0; i < 12; i++)
	{
		num1[i] = rand() % MAX + 1;
	}
	Bubble_sort(num1, length);
	cout << "冒泡排序后为：" << endl;
	for (i = 0; i < length; i++)
		cout << num1[i] << " ";
	cout << endl;


	int num2[12];
	for (i = 0; i < 12; i++)
	{
		num2[i] = rand() % MAX + 1;
	}
	Selection_sort(num2,length);
	cout << "选择排序后为：" << endl;
	for (i = 0; i < length; i++)
		cout << num2[i] << " ";
	cout << endl;


	int num3[12];
	for (i = 0; i < 12; i++)
	{
		num3[i] = rand() % MAX + 1;
	}
	Insert_sort(num3, length);
	cout << "插入排序后为：" << endl;
	for (i = 0; i < length; i++)
		cout << num3[i] << " ";
	cout << endl;


	int num4[12];
	for (i = 0; i < 12; i++)
	{
		num4[i] = rand() % MAX + 1;
	}
	Shell_sort(num4, length);
	cout << "希尔排序后为：" << endl;
	for (i = 0; i < length; i++)
		cout << num4[i] << " ";
	cout << endl;


	int num5[12];
	for (i = 0; i < 12; i++)
	{
		num5[i] = rand() % MAX + 1;
	}
	Quick_sort(num5,0, length-1);
	cout << "快速排序后为：" << endl;
	for (i = 0; i < length; i++)
		cout << num5[i] << " ";
	cout << endl;


	int num6[12];
	for (i = 0; i < 12; i++)
	{
		num6[i] = rand() % MAX + 1;
	}
	Heap_sort(num6, length);
	cout << "堆排序后为：" << endl;
	for (i = 0; i < length; i++)
		cout << num6[i] << " ";
	cout << endl;


	int num7[12];
	for (i = 0; i < 12; i++)
	{
		num7[i] = rand() % MAX + 1;
	}
	radix_sort(num7, length);
	cout << "基数排序后为：" << endl;
	for (i = 0; i < length; i++)
		cout << num7[i] << " ";
	cout << endl;


	int num8[12];
	for (i = 0; i < 12; i++)
	{
		num8[i] = rand() % MAX + 1;
	}
	merge_sort(num8, 0, length - 1);
	cout << "归并排序后为：" << endl;
	for (i = 0; i < length; i++)
		cout << num8[i] << " ";
	cout << endl;
}


int main()
{
	test();
	system("pause");
	return EXIT_SUCCESS;
}
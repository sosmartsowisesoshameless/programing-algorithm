#include <iostream>
#include <stack>
#include  <stack>
#include  <string>
#include  <iostream>
using namespace std;
//初始字符串中的数字均为0到9
stack<char> oper;//运算符存储栈
stack<int> nums;//操作数栈
string post;//后续表达式

//栈内优先级
int inpriority(char ch)
{
	switch(ch)
	{
	case('*'):
		return 3;
		break;
	case('/'):
		return 3;
		break;
	case('+'):
		return 2;
		break;
	case('-'):
		return 2;
		break;
	case('('):
		return 1;
		break;
	default:
		return 0;
	}
}

//栈外优先级
int outpriority(char ch)
{
	switch (ch)
	{
	case('*'):
		return 3;
		break;
	case('/'):
		return 3;
		break;
	case('+'):
		return 2;
		break;
	case('-'):
		return 2;
		break;
	case('('):
		return 4;
		break;
	default:
		return 0;
	}

}

double result(char ch,double a, double b)
{
	switch (ch)
	{
	case('*'):
		return a * b;
		break;
	case('/'):
		return a / b;
		break;
	case('+'):
		return a + b;
		break;
	case('-'):
		return a - b;
		break;
	}
}
char temch;

string postorde(string s)
{
	string pos;
	int i = 0;
	while (s[i]!='\0')
	{
		if (s[i]==')')
		{
			while (oper.top()!='(')
			{
				temch = oper.top();
				pos += temch;
				oper.pop();
			}
			oper.pop();
		}
		else if (s[i] >= '0' && s[i] <= '9')
			pos += s[i];
		else if (oper.empty() || outpriority(s[i]) > inpriority(oper.top()))
			oper.push(s[i]);
		else
		{
			do{
				temch = oper.top();
				pos += temch;
				oper.pop();
			} while (!oper.empty() && outpriority(s[i]) <= inpriority(oper.top()));
			oper.push(s[i]);
		}
		i++;
	}
	while(!oper.empty())
	{
	temch = oper.top();
	pos += temch;
	oper.pop();
	}
	return pos;
}

double cal(string pos)
{
	int i = 0;
	while (pos[i] != '\0')
	{
		if (pos[i] >= '0' && pos[i] <= '9')
			nums.push(pos[i]-'0');
		else
		{
			int b = nums.top();
			nums.pop();
			int a = nums.top();
			nums.pop();
			nums.push(result(pos[i], a, b));
		}
		i++;
	}
	int lastresult = nums.top();
	nums.pop();
	return lastresult;
}

int main()
{
	string s;
	cin >> s;
	cout << postorde(s) << endl;
	cout << cal(postorde(s)) << endl;
	system("pause");
	return EXIT_SUCCESS;
}

#include <iostream>
using namespace std;

class treenood;
void midforeach(treenood* nood);

//数组实现二叉树
void arraytree()
{
	int data[] = { 0,6,3,5,9,7,8,4,2 };
	int tree[16] = { 0 };

	for (int i = 0; i < 9; i++)
		cout << data[i] << " ";
	cout << endl;

	for (int i = 1; i < 9; i++)
	{
		int level = 1;
		for (; tree[level] != 0;)
		{
			if (data[i] > tree[level])
				level = level * 2 + 1;
			else
				level = level * 2;
		}
		tree[level] = data[i];
	}
	for (int i = 1; i < 16; i++)
		cout << tree[i] << " ";
	cout << endl;
}

//链表实现二叉树
class treenood
{
public:
	treenood() {
		lnood = NULL;
		rnood = NULL;
		val = 0;
	};
	treenood(int a)
	{
		lnood = NULL;
		rnood = NULL;
		val = a;
	}
	int val;
	treenood *lnood;//左儿子
	treenood *rnood;//右儿子
};

//树的高度/深度
int valcompare(int a, int b)
{
	return a > b ? a : b;
}
int treeheight(treenood* root)
{
	treenood* nood = root;
	if (nood == NULL)
		return 0;
	if (nood->lnood == NULL && nood->rnood == NULL)
		return 1;
	else
		return 1 + valcompare(treeheight(nood->lnood), treeheight(nood->rnood));
}

//创建树
treenood* creat_tree(treenood* &root, int val)
{
	treenood* newnood = new treenood(val);
	treenood* current = root;
	if (root == NULL)
	{
		root = newnood;
		return root;
	}
	while (1)
	{
		if (val > current->val)
		{

			if (current->rnood != NULL)
				current = current->rnood;
			else
			{
				current->rnood = newnood;
				break;
			}
		}
		else if (val < current->val)
		{

			if (current->lnood != NULL)
				current = current->lnood;
			else
			{
				current->lnood = newnood;
				break;
			}
		}
	}
	return root;

}
//中序遍历
void midforeach(treenood* nood)
{
	if (nood != NULL)
	{
		midforeach(nood->lnood);
		cout << nood->val<<" ";
		midforeach(nood->rnood);
	}
}
//前序遍历
void preforeach(treenood* nood)
{
	if (nood != NULL)
	{
		cout << nood->val << " ";
		preforeach(nood->lnood);
		preforeach(nood->rnood);
	}
}
//后序遍历
void postforeach(treenood* nood)
{
	if (nood != NULL)
	{
		postforeach(nood->lnood);
		postforeach(nood->rnood);
		cout << nood->val << " ";
	}
}

//统计叶节点的数量
int leafnum(treenood* nood)
{
	if (nood == NULL)
		return 0;
	if (nood->lnood == NULL && nood->rnood == NULL)
	{
		return 1;
	}
	return (leafnum(nood->lnood) + leafnum(nood->rnood));
}

//查找节点
treenood* findnood(treenood* root,int val)
{
	while (root != NULL)
	{
		if (val == root->val)
		{
			cout << "找到元素了" << endl;
			return root;
		}
		else if (val > root->val)
			root = root->rnood;
		else
			root = root->lnood;
			
	}
	cout << "未找到元素" << val << endl;
	return  NULL;
}

//插入元素
void insert(treenood* &root, int val)
{
	if (findnood(root, val) != NULL)
		cout << "树中已有该元素，无法插入" << endl;
	else
		creat_tree(root, val);
}

//删除元素-中序立即先行者（前驱点）
void deleteval(treenood* &root, int val)
{
	treenood *valfather, *replacefather, *replace, *nood;
	nood = root;
	valfather = NULL;
	while (nood != NULL)
	{
		if (val == nood->val)
		{
			cout << "找到元素了" << endl;
			break;
		}
		else if (val > nood->val)
		{
			valfather = nood;
			nood = nood->rnood;
		}
		else
		{
			valfather = nood;
			nood = nood->lnood;
		}
	}
	if (nood == NULL)
	{
		cout << "未找到元素,无法删除" << val << endl;
		return;
	}
	//独子为右儿子
	else if (nood->lnood == NULL)
	{
		if (valfather == NULL)
		{
			root = nood->rnood;
			delete nood;
			return;
		}
		else if (valfather->lnood == nood)
		{
			valfather->lnood = nood->rnood;
			delete nood;
			return;
		}
		else
		{
			valfather->rnood = nood->rnood;
			delete nood;
			return;
		}
	}
	//独子为左儿子
	else if (nood->rnood == NULL)
	{
		if (valfather == NULL)
		{
			root = nood->lnood;
			delete nood;
			return;
		}
		else if (valfather->lnood == nood)
		{
			valfather->lnood = nood->lnood;
			delete nood;
			return;
		}
		else
		{
			valfather->rnood = nood->lnood;
			delete nood;
			return;
		}
	}
	//左右都有儿子，找先驱点
	else
	{
		replace = nood->lnood;
		replacefather = NULL;
		while (replace->rnood != NULL)
		{
			replacefather = replace;
			replace = replace->rnood;
		}

		//若先驱点是被删除点的左儿子
		if (replacefather == NULL)
		{
			if (valfather == NULL)    //删除点为根结点
			{
				replace->rnood = nood->rnood;
				root = replace;
				delete nood;
				return;
			}
			else if (valfather->lnood == nood)
			{
				valfather->lnood = replace;
				replace->rnood = nood->rnood;
				delete nood;
				return;
			}
			else
			{
				valfather->rnood = replace;
				replace->rnood = nood->rnood;
				delete nood;
				return;
			}
		}
		//若先驱点不是被删除点的左儿子
		else
		{
			if (valfather == NULL)
			{
				replacefather->rnood = replace->lnood;
				replace->lnood = nood->lnood;
				replace->rnood = nood->rnood;
				root = replace;
				delete nood;
				return;
			}
			else if (valfather->lnood == nood)
			{
				replacefather->rnood = replace->lnood;
				replace->lnood = nood->lnood;
				replace->rnood = nood->rnood;
				valfather->lnood = replace;
				delete nood;
				return;
			}
			else
			{
				replacefather->rnood = replace->lnood;
				replace->lnood = nood->lnood;
				replace->rnood = nood->rnood;
				valfather->rnood = replace;
				delete nood;
				return;
			}
		}
	}
}


	

int main()
{
	treenood* root = NULL;
	int temval[10] = { 55,66,22,88,99,33,77,11,44,5 };
	for (int i = 0; i < 10; i++)
	{
		cout << temval[i] << " ";
		root = creat_tree(root, temval[i]);
	}
	cout << endl << "完成链表二叉树的建立" << endl;

	//进行中序遍历
	midforeach(root);
	cout << endl;

	//进行前序遍历
	preforeach(root);
	cout << endl;

	//进行后序遍历
	postforeach(root);
	cout << endl;

	cout << "叶节点数量为：" << leafnum(root) << endl;

	//查找33
	if (findnood(root, 33) != NULL)
		cout << "33的所在地址为：" << findnood(root, 33) << endl;

	//插入62
	insert(root, 62);
	midforeach(root);
	cout << endl;

		//高度
	cout << "树的高度为：" << treeheight(root) << endl;
	
	//删除66结点
	deleteval(root, 55);
	midforeach(root);
	cout << endl;
	
	system("pause");
	return EXIT_SUCCESS;
}
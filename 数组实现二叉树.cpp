#include <iostream>
using namespace std;

class treenood;
void midforeach(treenood* nood);

//����ʵ�ֶ�����
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

//����ʵ�ֶ�����
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
	treenood *lnood;//�����
	treenood *rnood;//�Ҷ���
};

//���ĸ߶�/���
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

//������
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
//�������
void midforeach(treenood* nood)
{
	if (nood != NULL)
	{
		midforeach(nood->lnood);
		cout << nood->val<<" ";
		midforeach(nood->rnood);
	}
}
//ǰ�����
void preforeach(treenood* nood)
{
	if (nood != NULL)
	{
		cout << nood->val << " ";
		preforeach(nood->lnood);
		preforeach(nood->rnood);
	}
}
//�������
void postforeach(treenood* nood)
{
	if (nood != NULL)
	{
		postforeach(nood->lnood);
		postforeach(nood->rnood);
		cout << nood->val << " ";
	}
}

//ͳ��Ҷ�ڵ������
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

//���ҽڵ�
treenood* findnood(treenood* root,int val)
{
	while (root != NULL)
	{
		if (val == root->val)
		{
			cout << "�ҵ�Ԫ����" << endl;
			return root;
		}
		else if (val > root->val)
			root = root->rnood;
		else
			root = root->lnood;
			
	}
	cout << "δ�ҵ�Ԫ��" << val << endl;
	return  NULL;
}

//����Ԫ��
void insert(treenood* &root, int val)
{
	if (findnood(root, val) != NULL)
		cout << "�������и�Ԫ�أ��޷�����" << endl;
	else
		creat_tree(root, val);
}

//ɾ��Ԫ��-�������������ߣ�ǰ���㣩
void deleteval(treenood* &root, int val)
{
	treenood *valfather, *replacefather, *replace, *nood;
	nood = root;
	valfather = NULL;
	while (nood != NULL)
	{
		if (val == nood->val)
		{
			cout << "�ҵ�Ԫ����" << endl;
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
		cout << "δ�ҵ�Ԫ��,�޷�ɾ��" << val << endl;
		return;
	}
	//����Ϊ�Ҷ���
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
	//����Ϊ�����
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
	//���Ҷ��ж��ӣ���������
	else
	{
		replace = nood->lnood;
		replacefather = NULL;
		while (replace->rnood != NULL)
		{
			replacefather = replace;
			replace = replace->rnood;
		}

		//���������Ǳ�ɾ����������
		if (replacefather == NULL)
		{
			if (valfather == NULL)    //ɾ����Ϊ�����
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
		//�������㲻�Ǳ�ɾ����������
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
	cout << endl << "�������������Ľ���" << endl;

	//�����������
	midforeach(root);
	cout << endl;

	//����ǰ�����
	preforeach(root);
	cout << endl;

	//���к������
	postforeach(root);
	cout << endl;

	cout << "Ҷ�ڵ�����Ϊ��" << leafnum(root) << endl;

	//����33
	if (findnood(root, 33) != NULL)
		cout << "33�����ڵ�ַΪ��" << findnood(root, 33) << endl;

	//����62
	insert(root, 62);
	midforeach(root);
	cout << endl;

		//�߶�
	cout << "���ĸ߶�Ϊ��" << treeheight(root) << endl;
	
	//ɾ��66���
	deleteval(root, 55);
	midforeach(root);
	cout << endl;
	
	system("pause");
	return EXIT_SUCCESS;
}
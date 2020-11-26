#include "AVL_Element.h"
#include "AVL.h"
#include "vector"
#include <iostream>

using namespace std;

static vector<vector<int>>output;
void create_output_BST(shared_ptr<AVL_Element> p, const unsigned int level)
{
	if (output.size() < level + 1)
	{
		vector<int> a;
		output.push_back(a);
	}
	if (p)
	{
		create_output_BST(p->getLeft(), level + 1);
		output[level].push_back(p->getDate());
		create_output_BST(p->getRight(), level + 1);
	}
	else
	{
		output[level].push_back(-1);
	}
}
void print_AVL(const AVL& p)
{
	output.clear();
	create_output_BST(p.getRoot(), 0);
	const unsigned  int level = output.size();
	const unsigned  int x = (1 << level) - 1;
	unsigned int a = x, b = (a - 1) / 2;
	for (unsigned int l = 0; l < level - 1; ++l)
	{
		for (unsigned int j = 0; j < b; ++j) cout << "  ";
		for (unsigned int i = 0; i < output[l].size(); ++i)
		{
			if (output[l][i] != -1)
				cout << output[l][i];
			else
				cout << '-';
			if (l != 0)
				for (unsigned int j = 0; j < a; ++j) cout << "  ";
		}
		cout << '\n';
		a = b+1;
		b /= 2;
	}

}
void print_element(const shared_ptr<AVL_Element> x)
{
	cout << endl;
	cout << x->getDate() << endl;
	cout << "l: ";
	if (x->getLeft() == 0)
		cout << "-" << endl;
	else
		cout << x->getLeft()->getDate() << endl;
	cout << "r: ";
	if (x->getRight() == 0)
		cout << "-" << endl;
	else
		cout << x->getRight()->getDate() << endl;
	if (x->getLeft() != 0)
		print_element(x->getLeft());
	if (x->getRight() != 0)
		print_element(x->getRight());
}

int main()
{
	setlocale(0,"");
	AVL* AVL_TREE;
	int buff1;
	char buff2;
	cout << "Введите корень дерева\n";
	cin >> buff1;
	AVL_TREE = new AVL(buff1);
	do
	{
		print_AVL(*AVL_TREE);
		cout << endl;
		print_element(AVL_TREE->getRoot());
		cout << endl;

		cout << "1. Добавить элемент\n";
		cout << "2. Удалить элемент\n";
		cout << "3. Закончить\n";
		cin >> buff2;
		if (buff2 != '3')
		{
			cout << "Введите элемент для удаления/добавления \n";
			cin >> buff1;
		}
		switch (buff2)
		{
		case('1'):
			AVL_TREE->insert(buff1);
			break;
		case('2'):
			if (AVL_TREE->getCount() != 1)
			{
				AVL_TREE->tree_delete(buff1);
			}
			break;
		case('3'):
			exit(0);
			break;
		default:
			continue;
		}
		system("cls");
	} while (1);
	return 0;
}
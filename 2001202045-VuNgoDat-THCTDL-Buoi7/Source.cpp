#include<iostream>
#include<fstream>
#include<Windows.h>
#include<string>
#include"PhanSo.h"
#include"BRTree.h"
#include"PrintTree.h"
using namespace std;
//Struct and Constant

//Prototype
void showPS(BRTNode<PhanSo>* p);
void menu();
void traversePS(BRTree<PhanSo> tree);
void NLR_BFS(BRTNode<PhanSo>* root);
void NRL_BFS(BRTNode<PhanSo>* root);
void LNR_DFS(BRTNode<PhanSo>* root);
void RNL_DFS(BRTNode<PhanSo>* root);
void NLR_DFS(BRTNode<PhanSo>* root);
void NRL_DFS(BRTNode<PhanSo>* root);
void inputPS(PhanSo& x);
void insertX(BRTree<PhanSo>& tree);
void removeX(BRTree<PhanSo>& tree);
void findX(BRTree<PhanSo> tree);

//Main
void main()
{
	PhanSo a[100] = { {1,3},{2,4},{2,5},{9,8},{9,2},{5,5},{3,4},{75,43},{4,5},{2,3} };
	BRTree<PhanSo> tree;
	initBRTree(tree);
	int chon;
	do
	{
		system("cls");
		menu();
		print_ascii_tree(tree.Root);
		set_Color(0, 7);
		cout << "Chon: ";
		cin >> chon;
		
		system("cls");
		print_ascii_tree(tree.Root);
		set_Color(0, 7);
		switch (chon)
		{
		case 1:
			for (int i = 0; i < 10; i++)
			{
				toiGianPS(a[i]);
				if (findBRTNode(tree.Root, a[i]) == NULL)
				{
					insert(tree.Root, a[i]);
				}
			}
			showBRTree_InOrder(tree.Root, showPS);
			break;
		case 2:
			break;
		case 3:
			traversePS(tree);
			break;
		case 4://Chieu rong
			NLR_BFS(tree.Root);
			cout << endl;
			NRL_BFS(tree.Root);
			cout << endl;
			break;
		case 5:
			cout << "LNR: ";
			LNR_DFS(tree.Root);
			cout << endl;
			cout << "RNL: ";
			RNL_DFS(tree.Root);
			cout << endl;
			cout << "NLR: ";
			NLR_DFS(tree.Root);
			cout << endl;
			cout << "NRL: ";
			NRL_DFS(tree.Root);
			cout << endl;
			break;
		case 6:
			insertX(tree);
			break;
		case 7:
			findX(tree);
			break;
		case 8:		
			removeX(tree);
			break;
		default:
			cout << "EXIT!" << endl;
			break;
		}
		cout << endl;
		set_Color(0, 7);
		system("pause");
	} while (chon > 0 && chon <= 10);
}

//Functions
void showPS(BRTNode<PhanSo>* p)
{
	if (p->Color == RED)
		set_Color(15, 12);	//Light Red=12 (C), BRight White=15 (F)
	else if (p->Color == BLACK)
		set_Color(15, 0);	//Black=0, BRight White=15 (F)
	cprintf(" [%d/%d]", p->Info.tu,p->Info.mau);
	//xuatPhanSo(p->Info);
	//set_Color(14, 2);		//Light Yellow=14 (E), Green=2
	set_Color(0, 7);
}
void menu()
{
	ifstream in;
	string filename = "menu.txt";
	SetConsoleOutputCP(65001);
	in.open(filename);
	if (in)
	{
		while (!in.eof())
		{
			string line;
			getline(in, line);
			cout << line << endl;
		}
	}
	in.close();
}
void traversePS(BRTree<PhanSo> tree)
{
	NLR(tree.Root, showPS);
	cout << endl;
	NRL(tree.Root, showPS);
	cout << endl;
	LNR(tree.Root, showPS);
	cout << endl;
	RNL(tree.Root, showPS);
	cout << endl;
	LRN(tree.Root, showPS);
	cout << endl;
	RLN(tree.Root, showPS);
	cout << endl;
}
void NLR_BFS(BRTNode<PhanSo>* root)
{
	if (root == NULL) return;

	queue <BRTNode<PhanSo>*> q;
	q.push(root);

	while (!q.empty()) {
		BRTNode<PhanSo>* p;
		p = q.front();
		q.pop();
		showPS(p);
		if (p->Left != NULL)
			q.push(p->Left);
		if (p->Right != NULL)
			q.push(p->Right);
	}

}
void NRL_BFS(BRTNode<PhanSo>* root)
{
	if (root == NULL) return;

	queue <BRTNode<PhanSo>*> q;
	q.push(root);

	while (!q.empty()) {
		BRTNode<PhanSo>* p;
		p = q.front();
		q.pop();
		showPS(p);
		if (p->Right != NULL)
			q.push(p->Right);
		if (p->Left != NULL)
			q.push(p->Left);
	}
}
void LNR_DFS(BRTNode<PhanSo>* root)
{
	if (root == NULL) return;

	stack <BRTNode<PhanSo>*> s;

	while (!s.empty() || root) {
		if (root) {
			s.push(root);
			root = root->Left;
		}
		else {
			root = s.top();
			s.pop();
			showPS(root);
			root = root->Right;
		}
	}
}
void RNL_DFS(BRTNode<PhanSo>* root)
{
	if (root == NULL) return;

	stack <BRTNode<PhanSo>*> s;

	while (!s.empty() || root) {
		if (root) {
			s.push(root);
			root = root->Right;
		}
		else {
			root = s.top();
			s.pop();
			showPS(root);
			root = root->Left;
		}
	}
}
void NRL_DFS(BRTNode<PhanSo>* root)
{
	if (root == NULL) return;

	stack <BRTNode<PhanSo>*> s;

	while (!s.empty() || root) {
		if (root) {
			showPS(root);
			s.push(root);
			root = root->Right;
		}
		else {
			root = s.top();
			s.pop();
			root = root->Left;
		}
	}
}
void NLR_DFS(BRTNode<PhanSo>* root)
{
	if (root == NULL) return;

	stack <BRTNode<PhanSo>*> s;

	while (!s.empty() || root) {
		if (root) {
			showPS(root);
			s.push(root);
			root = root->Left;
		}
		else {
			root = s.top();
			s.pop();
			root = root->Right;
		}
	}
}
void inputPS(PhanSo& x)
{
	cout << "\nNhap tu so:";
	cin >> x.tu;
	do
	{
		cout << "\nNhap mau so:";
		cin >> x.mau;
	} while (x.mau <= 0);
}
void insertX(BRTree<PhanSo>& tree)
{
	PhanSo x;
	cout << "\nNhap phan so X";
	inputPS(x);

	toiGianPS(x);
	if (findBRTNode(tree.Root, x) == NULL)
	{
		insert(tree.Root, x);
	}
	else
	{
		cout << "\nPhan tu da bi trung!" << endl;
	}
}
void removeX(BRTree<PhanSo>& tree)
{
	PhanSo x;
	cout << "\nNhap phan so X";
	inputPS(x);
	toiGianPS(x);
	deleteByInfo(tree.Root, x);
}
void findX(BRTree<PhanSo> tree)
{
	PhanSo x;
	cout << "\nNhap phan so X";
	inputPS(x);

	toiGianPS(x);
	if (findBRTNode(tree.Root, x) == NULL)
	{
		cout << "\nKhong tim thay phan tu!" << endl;
	}
	else
	{
		cout << "\nDa tim thay phan tu " << x.tu << "/" << x.mau << endl;
	}
}
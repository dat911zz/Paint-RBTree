#include<iostream>
#include<fstream>
#include<Windows.h>
#include<string>
#include"PhanSo.h"
#include"BRTree.h"
using namespace std;
//Struct and Constant

//Prototype
void showPS(BRTNode<PhanSo>* p);
void menu();
void traversePS(BRTree<PhanSo> tree);
//Main
void main()
{
	PhanSo a[100] = { {1,3},{2,4},{2,5},{9,8},{9,2},{5,5},{3,4},{75,43} };
	BRTree<PhanSo> tree;
	initBRTree(tree);
	int chon;
	do
	{
		system("cls");
		menu();
		cout << "Chon: ";
		cin >> chon;
		switch (chon)
		{
		case 1:
			for (int i = 0; i < 8; i++)
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
			traversePS(tree);
			break;
		case 3://Chieu rong
			showLevelOrder(tree.Root, showPS);
			cout << endl;
			iterativeInOrder(tree.Root, showPS);
			cout << endl;
			iterativePostOrder(tree.Root, showPS);
			break;
		case 4:
			break;
		case 5:
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
		set_Color(15, 12);	//Light Red=12 (C), Bright White=15 (F)
	else if (p->Color == BLACK)
		set_Color(15, 0);	//Black=0, Bright White=15 (F)
	cprintf(" [%d/%d]", p->Info.tu,p->Info.mau);
	//xuatPhanSo(p->Info);
	set_Color(14, 2);		//Light Yellow=14 (E), Green=2
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
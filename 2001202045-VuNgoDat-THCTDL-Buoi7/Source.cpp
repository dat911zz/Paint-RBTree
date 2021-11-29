#include<iostream>
#include"PhanSo.h"
#include"BRTree.h"
using namespace std;
//Struct and Constant

//Prototype
void showPS(BRTNode<PhanSo>* p);
//Main
void main()
{
	PhanSo a[100] = { {1,3},{2,4},{2,5},{9,8},{9,2},{5,5} };
	BRTree<PhanSo> tree;
	initBRTree(tree);
	for (int i = 0; i < 5; i++)
	{
		toiGianPS(a[i]);
		insert(tree.Root, a[i]);
	}
	showBRTree_InOrder(tree.Root, showPS);
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
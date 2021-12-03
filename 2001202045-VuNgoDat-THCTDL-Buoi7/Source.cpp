#include<iostream>
#include<fstream>
#include<Windows.h>
#include<string>
#include"PhanSo.h"
#include"BRTree.h"
#include"Dictionary.h"
#include"PrintDictionaryTree.h"
#include"PrintTree.h"
using namespace std;
//Struct and Constant

//Prototype
void readFilePS(BRTree<PhanSo>& tree);
void showPS(BRTNode<PhanSo>* p);
void showPS_2(PhanSo x);
void menu();
void menu_2();
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
void removeElementsGreaterThan2(BRTNode<PhanSo>*& root);
bool isPrime(int x);
void removeDenominatorPrimeElements(BRTNode<PhanSo>*& root);
double sumOfFractions(BRTNode<PhanSo>* root);
PhanSo sumOfFractions_2(BRTNode<PhanSo>* root);
int countFractionsLevelK(BRTNode<PhanSo>* root, int k);
void deleteBRTree(BRTNode<PhanSo>*& root);
void xuatPSTuNhoHonMau(BRTNode<PhanSo>* root);
void xuatPSMauLaSCP(BRTNode<PhanSo>* root);
bool isPerfectNum(int n);
void xuatPSTuVaMauLaSoHoanHao(BRTNode<PhanSo>* root);

void readFileDictionary(BRTree<Dictionary>& tree, string filename);
void showDictionaryNode(BRTNode<Dictionary>* root);


//Main
void main()
{
	PhanSo a[100] = { {1,3},{2,4},{2,5},{9,4},{9,2},{5,5},{3,4},{75,43},{5,7},{2,3} };
	int n = 10;
	BRTree<PhanSo> tree;
	BRTree<Dictionary> dictionary;
	initBRTree(tree);
	initBRTree(dictionary);
	int chon;
	cout << "1- Phan so\t2- Tu dien" << endl;
	cout << "Chon: ";
	cin >> chon;
	switch (chon)
	{
	case 1:
		do
		{
			system("cls");
			menu();
			print_ascii_tree(tree.Root);
			set_Color(0, 7);
			cout << "==========================================================================" << endl;
			cout << "Chon: ";
			cin >> chon;

			system("cls");
			print_ascii_tree(tree.Root);
			set_Color(0, 7);
			switch (chon)
			{
			case 1:
				for (int i = 0; i < n; i++)
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
				readFilePS(tree);
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
				print_ascii_tree(tree.Root);
				set_Color(0, 7);
				break;
			case 9:
				removeElementsGreaterThan2(tree.Root);
				break;
			case 10:
				removeDenominatorPrimeElements(tree.Root);
				print_ascii_tree(tree.Root);
				set_Color(0, 7);
				break;
			case 11:
				cout << "\nTong phan so trong cay: " << sumOfFractions(tree.Root);
				cout << "\nTong phan so trong cay(phan so): ";
				PhanSo sum = sumOfFractions_2(tree.Root);
				toiGianPS(sum);
				showPS_2(sum);
				break;
			case 12:
				int k;
				cout << "\nNhap muc k: ";
				cin >> k;
				cout << "\nSo luong phan so muc k: " << countFractionsLevelK(tree.Root, k);
				break;
			case 13:
				deleteBRTree(tree.Root);
				break;
			case 14:
				cout << "\nXuat PS co tu nho hon mau: ";
				xuatPSTuNhoHonMau(tree.Root);
				break;
			case 15:
				cout << "\nXuat PS co mau so la so chinh phuong: ";
				xuatPSMauLaSCP(tree.Root);
				break;
			case 16:
				cout << "\nXuat PS co tu so va mau so dong thoi la so hoan thien: ";
				xuatPSTuVaMauLaSoHoanHao(tree.Root);
				break;
			default:
				cout << "EXIT!" << endl;
				break;
			}
			cout << endl;
			set_Color(0, 7);
			system("pause");
		} while (chon > 0 && chon <= 16);
		break;
	case 2:
		do
		{
			system("cls");
			menu_2();
			print_ascii_tree(tree.Root);
			set_Color(0, 7);
			cout << "==========================================================================" << endl;
			cout << "Chon: ";
			cin >> chon;

			system("cls");
			print_ascii_tree(tree.Root);
			set_Color(0, 7);
			switch (chon)
			{
			case 1:
				readFileDictionary(dictionary, "Dictionary.txt");
				print_ascii_tree_2(dictionary.Root);
				cout << "\nLNR: ";
				LNR(dictionary.Root, showDictionaryNode);
				break;
			case 2:
				print_ascii_tree_2(dictionary.Root);
				cout << "\nBFS: ";
				levelOrder(dictionary.Root, showDictionaryNode);
				cout << "\nDFS: ";
				iterativePreOrder(dictionary.Root, showDictionaryNode);
				break;
			case 3:

				break;
			case 4:
				break;
			default:
				cout << "EXIT!" << endl;
				break;
			}
			cout << endl;
			system("pause");
		} while (chon > 0 && chon <= 9);
		break;
	}
	
}

//Functions
void readFilePS(BRTree<PhanSo>& tree)
{
	ifstream in;
	string filename = "PhanSo.txt";
	if (in)
	{
		while (!in.eof())
		{
			PhanSo tmp;
			in >> tmp.tu >> tmp.mau;
			toiGianPS(tmp);
			if (findBRTNode(tree.Root, tmp) == NULL)
			{
				insert(tree.Root, tmp);
			}
		}
	}
	
}
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
void showPS_2(PhanSo x)
{
	printf(" [%d/%d]", x.tu, x.mau);
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
void menu_2()
{
	ifstream in;
	string filename = "menu_2.txt";
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
void removeElementsGreaterThan2(BRTNode<PhanSo>*& root)
{
	if (root == NULL)
	{
		return;
	}
	while(root && root->Info > PhanSo{2, 1})
	{
		deleteByInfo(root, root->Info);
	}
	removeElementsGreaterThan2(root->Left);
	removeElementsGreaterThan2(root->Right);
}
bool isPrime(int x)
{
	if (x < 2)
	{
		return false;
	}
	if (x == 2)
	{
		return true;
	}
	if (x % 2 == 0)
	{
		return false;
	}
	for (int i = 2; i <= (int)sqrt(x); i++)
	{
		if (x % i == 0)
		{
			return false;
		}
	}
	return true;
}
void removeDenominatorPrimeElements(BRTNode<PhanSo>*& root)
{
	if (root == NULL)
	{
		return;
	}
	removeDenominatorPrimeElements(root->Left);
	removeDenominatorPrimeElements(root->Right);
	while (root && isPrime(root->Info.mau))
	{
		deleteByInfo(root, root->Info);
	}
}
double sumOfFractions(BRTNode<PhanSo>* root)
{
	if (root == NULL)
	{
		return 0;
	}
	double l = sumOfFractions(root->Left);
	double r = sumOfFractions(root->Right);
	return (1.0 * root->Info.tu / root->Info.mau) + l + r;
}
PhanSo sumOfFractions_2(BRTNode<PhanSo>* root)
{
	if (root == NULL)
	{
		return { 0,1 };
	}
	PhanSo l = sumOfFractions_2(root->Left);
	PhanSo r = sumOfFractions_2(root->Right);
	return (root->Info + l) + r;
}
int countFractionsLevelK(BRTNode<PhanSo>* root, int k)
{
	if (root == NULL)
	{
		return 0;
	}
	int l = countFractionsLevelK(root->Left, k - 1);
	int r = countFractionsLevelK(root->Right, k - 1);
	return k == 0 ? 1 + l + r : l + r;
}
void deleteBRTree(BRTNode<PhanSo>*& root)
{
	if (root == NULL)
	{
		return;
	}
	deleteBRTree(root->Left);
	deleteBRTree(root->Right);
	while (root != NULL)
	{
		deleteByInfo(root, root->Info);
	}
}
void xuatPSTuNhoHonMau(BRTNode<PhanSo>* root)
{
	if (root == NULL)
	{
		return;
	}
	if (root->Info.tu < root->Info.mau)
	{
		showPS(root);
	}
	xuatPSTuNhoHonMau(root->Left);
	xuatPSTuNhoHonMau(root->Right);
}
bool isSquareNum(int n)
{
	int x = sqrt(n);
	return x * x == n;
}
void xuatPSMauLaSCP(BRTNode<PhanSo>* root)
{
	if (root == NULL)
	{
		return;
	}
	if (isSquareNum(root->Info.mau))
	{
		showPS(root);
	}
	xuatPSMauLaSCP(root->Left);
	xuatPSMauLaSCP(root->Right);
}
bool isPerfectNum(int n)
{
	int sum = 0;

	for (int i = 1; i < n; i++)
	{
		if (n % i == 0)
		{
			sum += i;
		}
	}
	return sum == n;
}
void xuatPSTuVaMauLaSoHoanHao(BRTNode<PhanSo>* root)
{
	if (root == NULL)
	{
		return;
	}
	if (isPerfectNum(root->Info.tu) && isPerfectNum(root->Info.mau))
	{
		showPS(root);
	}
	xuatPSTuVaMauLaSoHoanHao(root->Left);
	xuatPSTuVaMauLaSoHoanHao(root->Right);
}
//============================================
//Bai 4
void readFileDictionary(BRTree<Dictionary>& tree, string filename)
{
	ifstream in;
	in.open(filename);
	if (in)
	{
		initBRTree(tree);
		Dictionary tmp;
		while (!in.eof())
		{
			in >> tmp.word >> tmp.mean;
			insert(tree.Root, tmp);
		}
	}
}
void showDictionaryNode(BRTNode<Dictionary>* root)
{
	printf(" [%s|%s]", root->Info.word, root->Info.mean);
}
BRTNode<Dictionary>* searchMeanOfWord(BRTNode<Dictionary>* root, const char* x)
{
	if (root == NULL)
	{
		return NULL;
	}

	if (root->Info.mean == x)
	{
		return root;
	}
	else
	{
		if (true)
		{

		}
	}
	searchMeanOfWord(root->Left, x);
	searchMeanOfWord(root->Right, x);
}
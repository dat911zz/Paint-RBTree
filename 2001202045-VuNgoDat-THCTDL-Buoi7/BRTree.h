#ifndef BRTree_h
#define BRTree_h

#include <conio.h>
#include <stdio.h>
#include <queue>
#include <stack>
#include <Windows.h>
using namespace std;

/* Khai báo kiểu dữ liệu của Node */


/* Khai báo thuộc tính color */
enum EColor { RED, BLACK };

/* Khai báo cấu trúc node */
template <class T>
struct BRTNode
{
	T Info;
	EColor Color;
	BRTNode<T> *Left, *Right, *Parent;
};

/* Khai báo cấu trúc cây Đỏ-Đen */
template <class T>
struct BRTree
{
	BRTNode<T> *Root;
};
//==================================================
template <class T>
BRTNode<T>* createBRTNode(T x);
void set_Color(int colorBackground, int colorText);
template <class T>
void showTNode(BRTNode<T> *p);
template <class T>
void initBRTree(BRTree<T> &brt);
template <class T>
void swapColors(EColor &color1, EColor &color2);
template <class T>
void swapInfos(T &info1, T &info2);
template <class T>
void showBRTree_PreOrder(BRTNode<T> *root, void (*show)(BRTNode<T>*));
template <class T>
void showBRTree_InOrder(BRTNode<T> *root, void (*show)(BRTNode<T>*));
template <class T>
void showBRTree_PostOrder(BRTNode<T> *root, void (*show)(BRTNode<T>*));
template <class T>
void levelOrder(BRTNode<T> *root, void (*show)(BRTNode<T>*));
template <class T>
void showLevelOrder(BRTNode<T> *root, void (*show)(BRTNode<T>*));
template <class T>
void iterativePreOrder(BRTNode<T> *root, void (*show)(BRTNode<T>*));
template <class T>
void showPreOrder(BRTNode<T> *root, void (*show)(BRTNode<T>*));
template <class T>
void iterativeInOrder(BRTNode<T> *root, void (*show)(BRTNode<T>*));
template <class T>
void showInOrder(BRTNode<T> *root, void (*show)(BRTNode<T>*));
template <class T>
void iterativePostOrder(BRTNode<T> *root, void (*show)(BRTNode<T>*));
template <class T>
void showPostOrder(BRTNode<T> *root, void (*show)(BRTNode<T>*));
template <class T>
BRTNode<T>* BRTInsert(BRTNode<T>* root, BRTNode<T> *pNew);
template <class T>
void rotateLeft(BRTNode<T> *&root, BRTNode<T> *&p);
template <class T>
void rotateRight(BRTNode<T> *&root, BRTNode<T> *&p);
template <class T>
void fixViolation(BRTNode<T> *&root, BRTNode<T> *&p);
template <class T>
void insert(BRTNode<T> *&root, T Info);
template <class T>
bool isOnLeft(BRTNode<T> *p);
template <class T>
bool hasRedChild(BRTNode<T> *p);
template <class T>
BRTNode<T> *findUncle(BRTNode<T> *p);
template <class T>
BRTNode<T> *findSibling(BRTNode<T>* p);
template <class T>
BRTNode<T> *findSuccessor(BRTNode<T> *p);
template <class T>
void fixDoubleBlack(BRTNode<T> *&root, BRTNode<T> *p);
template <class T>
BRTNode<T> *BSTReplace(BRTNode<T> *p);
template <class T>
void deleteNode(BRTNode<T> *&root, BRTNode<T> *pDelete);
template <class T>
BRTNode<T> *search(BRTNode<T> *root, T x);
template <class T>
void deleteByInfo(BRTNode<T> *&root, T x);

#endif
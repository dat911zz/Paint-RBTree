#ifndef _TREE_
#define _TREE_
#include<stdio.h>
#include<string.h>

struct asciinode
{
    asciinode* Left;
    asciinode* Right;

    int edge_length;//length of the edge from this node to its children
    int height;
    int lablen;
    EColor Color;

    int parent_dir; //-1=I am Left, 0=I am root, 1=Right   
    char label[11];//max supported unit32 in dec, 10 digits max
};


int MIN(int X, int Y);
int MAX(int X, int Y);

template <class data> asciinode* build_ascii_tree_recursive(data* t);
template <class data> asciinode* build_ascii_tree(data* t);
void deleteAscii(asciinode* root);
void compute_lprofile(asciinode* node, int x, int y);

void compute_rprofile(asciinode* node, int x, int y);
void compute_edge_lengths(asciinode* node);
void print_level(asciinode* node, int x, int level);

//prints ascii tree for given Tree structure
template <class data> void print_ascii_tree(data* t);

//====================================================================================================

int MIN(int X, int Y)
{
    return ((X) < (Y)) ? (X) : (Y);
}

int MAX(int X, int Y)
{
    return ((X) > (Y)) ? (X) : (Y);
}

#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY (1<<20)

//adjust gap between Left and Right nodes
int gap = 3;
//used for printing next node in the same level, 
//this is the x coordinate of the next char printed
int print_next;

template <class data>
asciinode* build_ascii_tree_recursive(data* t)
{
    asciinode* node;

    if (t == NULL) return NULL;

    node = new asciinode;
    node->Left = build_ascii_tree_recursive(t->Left);
    node->Right = build_ascii_tree_recursive(t->Right);

    if (node->Left != NULL)
        node->Left->parent_dir = -1;

    if (node->Right != NULL)
        node->Right->parent_dir = 1;

    node->Color = t->Color;
    sprintf_s(node->label, "%d/%d", t->Info.tu, t->Info.mau);
    //std::cout << t->Info;
    node->lablen = strlen(node->label);

    return node;
}


//Copy the tree into the ascii node structre
template <class data>
asciinode* build_ascii_tree(data* t)
{
    asciinode* node;
    if (t == NULL) return NULL;
    node = build_ascii_tree_recursive(t);
    node->parent_dir = 0;
    return node;
}
//Free all the nodes of the given tree
void deleteAscii(asciinode* root)
{
    if (root == NULL) return;
    deleteAscii(root->Left);
    deleteAscii(root->Right);
    delete root;
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_lprofile(asciinode* node, int x, int y)
{
    int i, isLeft;
    if (node == NULL)
        return;

    isLeft = (node->parent_dir == -1);
    lprofile[y] = MIN(lprofile[y], x - ((node->lablen - isLeft) / 2));
    if (node->Left != NULL)
    {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
        {
            lprofile[y + i] = MIN(lprofile[y + i], x - i);
        }
    }
    compute_lprofile(node->Left, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_lprofile(node->Right, x + node->edge_length + 1, y + node->edge_length + 1);
}

void compute_rprofile(asciinode* node, int x, int y)
{
    int i, notLeft;
    if (node == NULL) return;
    notLeft = (node->parent_dir != -1);
    rprofile[y] = MAX(rprofile[y], x + ((node->lablen - notLeft) / 2));
    if (node->Right != NULL)
    {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
        {
            rprofile[y + i] = MAX(rprofile[y + i], x + i);
        }
    }
    compute_rprofile(node->Left, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_rprofile(node->Right, x + node->edge_length + 1, y + node->edge_length + 1);
}

//This function fills in the edge_length and 
//height fields of the specified tree
void compute_edge_lengths(asciinode* node)
{
    int h, hmin, i, delta;
    if (node == NULL) return;
    compute_edge_lengths(node->Left);
    compute_edge_lengths(node->Right);

    /* first fill in the edge_length of node */
    if (node->Right == NULL && node->Left == NULL)
    {
        node->edge_length = 0;
    }
    else
    {
        if (node->Left != NULL)
        {
            for (i = 0; i < node->Left->height && i < MAX_HEIGHT; i++)
            {
                rprofile[i] = -INFINITY;
            }
            compute_rprofile(node->Left, 0, 0);
            hmin = node->Left->height;
        }
        else
        {
            hmin = 0;
        }
        if (node->Right != NULL)
        {
            for (i = 0; i < node->Right->height && i < MAX_HEIGHT; i++)
            {
                lprofile[i] = INFINITY;
            }
            compute_lprofile(node->Right, 0, 0);
            hmin = MIN(node->Right->height, hmin);
        }
        else
        {
            hmin = 0;
        }
        delta = 4;
        for (i = 0; i < hmin; i++)
        {
            delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
        }

        //If the node has two children of height 1, then we allow the
        //two leaves to be within 1, instead of 2 
        if (((node->Left != NULL && node->Left->height == 1) ||
            (node->Right != NULL && node->Right->height == 1)) && delta > 4)
        {
            delta--;
        }

        node->edge_length = ((delta + 1) / 2) - 1;
    }

    //now fill in the height of node
    h = 1;
    if (node->Left != NULL)
    {
        h = MAX(node->Left->height + node->edge_length + 1, h);
    }
    if (node->Right != NULL)
    {
        h = MAX(node->Right->height + node->edge_length + 1, h);
    }
    node->height = h;
}

//This function prints the given level of the given tree, assuming
//that the node has the given x cordinate.
void print_level(asciinode* node, int x, int level)
{
    int i, isLeft;
    if (node == NULL) return;
    isLeft = (node->parent_dir == -1);
    if (level == 0)
    {
        for (i = 0; i < (x - print_next - ((node->lablen - isLeft) / 2)); i++)
        {
            printf(" ");
        }
        print_next += i;
        if (node->Color == RED)
            set_Color(15, 12);	//Light Red=12 (C), BRight White=15 (F)
        else if (node->Color == BLACK)
            set_Color(15, 0);	//Black=0, BRight White=15 (F)
        printf("%s", node->label);
        //xuatPhanSo(p->Info);
        //set_Color(14, 2);		//Light Yellow=14 (E), Green=2
        
        print_next += node->lablen;
    }
    else if (node->edge_length >= level)
    {
        if (node->Left != NULL)
        {
            for (i = 0; i < (x - print_next - (level)); i++)
            {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (node->Right != NULL)
        {
            for (i = 0; i < (x - print_next + (level)); i++)
            {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    }
    else
    {
        print_level(node->Left,
            x - node->edge_length - 1,
            level - node->edge_length - 1);
        print_level(node->Right,
            x + node->edge_length + 1,
            level - node->edge_length - 1);
    }
}

//prints ascii tree for given Tree structure
template <class data>
void print_ascii_tree(data* t)
{
    asciinode* proot;
    int xmin, i;
    if (t == NULL) return;

    proot = build_ascii_tree<data>(t);
    compute_edge_lengths(proot);
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
    {
        lprofile[i] = INFINITY;
    }
    compute_lprofile(proot, 0, 0);
    xmin = 0;
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
    {
        xmin = MIN(xmin, lprofile[i]);
    }
    for (i = 0; i < proot->height; i++)
    {
        print_next = 0;
        print_level(proot, -xmin, i);
        printf("\n");
    }
    if (proot->height >= MAX_HEIGHT)
    {
        printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
    }
    deleteAscii(proot);
}

#endif
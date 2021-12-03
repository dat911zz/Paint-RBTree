#ifndef _TREE_DIC_
#define _TREE_DIC_
#include<stdio.h>
#include<string.h>

struct asciinode_2
{
    asciinode_2* Left;
    asciinode_2* Right;

    int edge_length;//length of the edge from this node to its children
    int height;
    int lablen;
    EColor Color;

    int parent_dir; //-1=I am Left, 0=I am root, 1=Right   
    char label[100];
};


int MIN_2(int X, int Y);
int MAX_2(int X, int Y);

template <class data> asciinode_2* build_ascii_tree_recursive_2(data* t);
template <class data> asciinode_2* build_ascii_tree_2(data* t);
void deleteAscii_2(asciinode_2* root);
void compute_lprofile_2(asciinode_2* node, int x, int y);

void compute_rprofile_2(asciinode_2* node, int x, int y);
void compute_edge_lengths_2(asciinode_2* node);
void print_level_2(asciinode_2* node, int x, int level);

//prints ascii tree for given Tree structure
template <class data> void print_ascii_tree_2(data* t);

//====================================================================================================

int MIN_2(int X, int Y)
{
    return ((X) < (Y)) ? (X) : (Y);
}

int MAX_2(int X, int Y)
{
    return ((X) > (Y)) ? (X) : (Y);
}

#define MAX_HEIGHT 1000
int lprofile_2[MAX_HEIGHT];
int rprofile_2[MAX_HEIGHT];
#define INFINITY (1<<20)

//adjust gap between Left and Right nodes
int gap = 3;
//used for printing next node in the same level, 
//this is the x coordinate of the next char printed
int print_next;

template <class data>
asciinode_2* build_ascii_tree_recursive_2(data* t)
{
    asciinode_2* node;

    if (t == NULL) return NULL;

    node = new asciinode_2;
    node->Left = build_ascii_tree_recursive_2(t->Left);
    node->Right = build_ascii_tree_recursive_2(t->Right);

    if (node->Left != NULL)
        node->Left->parent_dir = -1;

    if (node->Right != NULL)
        node->Right->parent_dir = 1;

    node->Color = t->Color;
    sprintf(node->label, "[%s]", t->Info.word);
    //std::cout << t->Info;
    //node->lablen = strlen(node->label);
    node->lablen = strlen(node->label);
    return node;
}


//Copy the tree into the ascii node structre
template <class data>
asciinode_2* build_ascii_tree_2(data* t)
{
    asciinode_2* node;
    if (t == NULL) return NULL;
    node = build_ascii_tree_recursive_2(t);
    node->parent_dir = 0;
    return node;
}
//Free all the nodes of the given tree
void deleteAscii_2(asciinode_2* root)
{
    if (root == NULL) return;
    deleteAscii_2(root->Left);
    deleteAscii_2(root->Right);
    delete root;
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_lprofile_2(asciinode_2* node, int x, int y)
{
    int i, isLeft;
    if (node == NULL)
        return;

    isLeft = (node->parent_dir == -1);
    lprofile_2[y] = MIN_2(lprofile_2[y], x - ((node->lablen - isLeft) / 2));
    if (node->Left != NULL)
    {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
        {
            lprofile_2[y + i] = MIN_2(lprofile_2[y + i], x - i);
        }
    }
    compute_lprofile_2(node->Left, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_lprofile_2(node->Right, x + node->edge_length + 1, y + node->edge_length + 1);
}

void compute_rprofile_2(asciinode_2* node, int x, int y)
{
    int i, notLeft;
    if (node == NULL) return;
    notLeft = (node->parent_dir != -1);
    rprofile_2[y] = MAX_2(rprofile_2[y], x + ((node->lablen - notLeft) / 2));
    if (node->Right != NULL)
    {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++)
        {
            rprofile_2[y + i] = MAX_2(rprofile_2[y + i], x + i);
        }
    }
    compute_rprofile_2(node->Left, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_rprofile_2(node->Right, x + node->edge_length + 1, y + node->edge_length + 1);
}

//This function fills in the edge_length and 
//height fields of the specified tree
void compute_edge_lengths_2(asciinode_2* node)
{
    int h, hmin, i, delta;
    if (node == NULL) return;
    compute_edge_lengths_2(node->Left);
    compute_edge_lengths_2(node->Right);

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
                rprofile_2[i] = -INFINITY;
            }
            compute_rprofile_2(node->Left, 0, 0);
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
                lprofile_2[i] = INFINITY;
            }
            compute_lprofile_2(node->Right, 0, 0);
            hmin = MIN_2(node->Right->height, hmin);
        }
        else
        {
            hmin = 0;
        }
        delta = 4;
        for (i = 0; i < hmin; i++)
        {
            delta = MAX_2(delta, gap + 1 + rprofile_2[i] - lprofile_2[i]);
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
        h = MAX_2(node->Left->height + node->edge_length + 1, h);
    }
    if (node->Right != NULL)
    {
        h = MAX_2(node->Right->height + node->edge_length + 1, h);
    }
    node->height = h;
}

//This function prints the given level of the given tree, assuming
//that the node has the given x cordinate.
void print_level_2(asciinode_2* node, int x, int level)
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
        //printf("%s", node->label);
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
        print_level_2(node->Left,
            x - node->edge_length - 1,
            level - node->edge_length - 1);
        print_level_2(node->Right,
            x + node->edge_length + 1,
            level - node->edge_length - 1);
    }
}

//prints ascii tree for given Tree structure
template <class data>
void print_ascii_tree_2(data* t)
{
    asciinode_2* proot;
    int xmin, i;
    if (t == NULL) return;

    proot = build_ascii_tree_2<data>(t);
    compute_edge_lengths_2(proot);
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
    {
        lprofile_2[i] = INFINITY;
    }
    compute_lprofile_2(proot, 0, 0);
    xmin = 0;
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
    {
        xmin = MIN_2(xmin, lprofile_2[i]);
    }
    for (i = 0; i < proot->height; i++)
    {
        print_next = 0;
        print_level_2(proot, -xmin, i);
        printf("\n");
    }
    if (proot->height >= MAX_HEIGHT)
    {
        printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
    }
    set_Color(0, 7);
    deleteAscii_2(proot);
}

#endif
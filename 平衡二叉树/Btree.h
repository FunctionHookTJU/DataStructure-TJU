#ifndef BTREE_H
#define BTREE_H
#define LEFT 0
#define RIGHT 1
struct BNode{
    int data;
    BNode *lch,*rch;

    BNode(int val) : data(val), lch(nullptr), rch(nullptr) {}
};

class Btree{
private:
int depth;
int size;
BNode *rootBtree;

public:
Btree(int a[],int sizes);

~Btree();

bool SearchBST(BNode *T, int a, BNode *f, BNode *&p);

void InsertBST(int a);

bool DeleteBST();



};


#endif // BTREE_H
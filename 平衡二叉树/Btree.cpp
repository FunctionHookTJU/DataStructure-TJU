#include <iostream>
#include "Btree.h"

Btree::Btree(int a[],int sizes){
    size = 0;
    rootBtree = nullptr;
    if(sizes == 0){
        return;
    }

    for(int i=0;i<sizes;i++){
        InsertBST(a[i]);
    }
}


bool Btree::SearchBST(BNode *T,int a,BNode *f,BNode *&p){
    if(T == nullptr){
        p = f; // not found, p points to parent (可能为 nullptr 表示树为空)
        return false;
    }

    if(T->data == a){
        p = T; // found
        return true;
    }

    if(a < T->data)
        return SearchBST(T->lch, a, T, p);
    else
        return SearchBST(T->rch, a, T, p);
}
void Btree::InsertBST(int a){
    BNode *p = nullptr;
    if(!SearchBST(rootBtree, a, nullptr, p)){
        BNode *newNode = new BNode(a);
        if(p == nullptr){
            // tree was empty
            rootBtree = newNode;
        } else if(a < p->data){
            p->lch = newNode;
        } else {
            p->rch = newNode;
        }
        size++;
    }
}

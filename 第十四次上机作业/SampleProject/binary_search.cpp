#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct BNode{
    int data;
    BNode *lch,*rch;

    BNode(int val) : data(val), lch(nullptr), rch(nullptr) {}
};
class Btree{
private:
int depth;
int size;
BNode* root;
    void deleteTree(BNode* node) {
        if (node == nullptr) return;
        deleteTree(node->lch);
        deleteTree(node->rch);
        delete node;
    }
public:
    ~Btree() {
        deleteTree(root);
    }

Btree(int a[],int sizes){
    size = 0;
    root = nullptr;
    if(sizes == 0){
        return;
    }

    for(int i=0;i<sizes;i++){
        InsertBST(a[i]);
    }
}

bool SearchBST(BNode *T, int a, BNode *f, BNode *&p){
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
bool SearchBigger(BNode *T,int a,BNode *f,BNode *&p){
    if(T == nullptr){
        p = f;
        return false;
    }
    if(T->data >= a){
        p = T;
        return true;
    }
    if(a < T->data)
        return SearchBigger(T->lch, a, T, p);
    else
        return SearchBigger(T->rch, a, T, p);
}

public:
bool SearchBigger(int a, BNode *&p){
    return SearchBigger(root, a, nullptr, p);
}

private:
void InsertBST(int a){
    BNode *p = nullptr;
    if(!SearchBST(root, a, nullptr, p)){
        BNode *newNode = new BNode(a);
        if(p == nullptr){
            // tree was empty
            root = newNode;
        } else if(a < p->data){
            p->lch = newNode;
        } else {
            p->rch = newNode;
        }
        size++;
    }
}

void DeleteBST(BNode * root){
    if(root == nullptr) return;
    DeleteBST(root->lch);
    DeleteBST(root->rch);
    delete root;
}
};

int main(){
    
    int n=0,q=0;
    ifstream file_in("problem1_data/1.in");
    file_in>>n>>q;
    int *arr = new int [n];
    for(int i=0;i<n;i++){
        file_in>>arr[i];
    }
    Btree tree(arr,n);

    int *Query=new int[q];
    
    for(int i=0;i<q;i++){
        file_in>>Query[i];
    }
    BNode *ans = nullptr;
    ofstream file_out("problem1_data/1.out");
    for(int j=0;j<q;j++){
        tree.SearchBigger(Query[j], ans);
        if(ans != nullptr){
            cout << ans->data << endl;
            file_out << ans->data << endl;
        }
    }
    
    file_out.close();
    delete[] arr;
    delete[] Query;
    return 0;
}
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct BNode{
    int data;
    int count;  // 记录相同元素的个数
    BNode *lch,*rch;

    BNode(int val) : data(val), count(1), lch(nullptr), rch(nullptr) {}
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

void inorderTraversal(BNode *T,int *arr,int &index){
    if(T == nullptr) return;
    inorderTraversal(T->lch,arr,index);
    // 根据count重复输出该元素
    for(int i = 0; i < T->count; i++){
        arr[index++] = T->data;
    }
    inorderTraversal(T->rch,arr,index);
}

// 返回排序后的数组
void Bsort(int *arr){
    if(size == 0) return ;
    
    int index = 0;
    inorderTraversal(root, arr, index);
    return;
}

int getSize(){
    return size;
}

private:
void InsertBST(int a){
    BNode *p = nullptr;
    if(!SearchBST(root, a, nullptr, p)){
        // 没找到，插入新节点
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
    } else {
        // 找到了相同元素，增加计数
        p->count++;
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

long long countTriangles(int arr[], int n) {
    if (n < 3) return 0;
    long long ans = 0;
    for (int k = n - 1; k >= 2; --k) {          // 最长边
        int i = 0, j = k - 1;
        while (i < j) {
            if (arr[i] + arr[j] > arr[k]) {
                ans += j - i;   // [i..j-1] 都满足
                --j;
            } else {
                ++i;
            }
        }
    }
    return ans;
}
int main(){
    int n1=0,n2=0;
    ifstream file1("problem2_data/1.in");
    ifstream file2("problem2_data/2.in");
    
    file1>>n1;
    int *arr1=new int [n1];
    for(int i=0;i<n1;i++){
        file1>>arr1[i];
    }
    Btree tree(arr1,n1);
    tree.Bsort(arr1);
    file1.close();

    file2>>n2;
    int *arr2=new int [n2];
    for(int i=0;i<n2;i++){
        file2>>arr2[i];
    }
    Btree tree2(arr2,n2);
    tree2.Bsort(arr2);
    file2.close();

    ofstream out1("problem2_data/1.out");
    long long ans=countTriangles(arr1,n1);
    cout<<ans<<endl;
    out1<<ans<<endl;
    out1.close();

    ofstream out2("problem2_data/2.out");
    ans=countTriangles(arr2,n2);
    cout<<ans<<endl;
    out2<<ans<<endl;
    out2.close();
    delete[] arr1;
    delete[] arr2;

    return 0;
}
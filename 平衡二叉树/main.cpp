#include <iostream>
#include "Btree.h"
using namespace std;
int main(){
    int a[15]={42, 17, 89, 33, 67, 25, 94, 12, 56, 78, 19, 81, 47, 62, 38};
    int l=sizeof(a);
    cout<<"The size of a[] is"<<l<<endl;
    Btree(a,15);
    return 0;
}
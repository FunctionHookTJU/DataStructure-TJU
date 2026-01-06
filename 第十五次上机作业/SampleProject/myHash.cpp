/*******************************************************************************
* FileName:         myHash.cpp
* Author:           于乘骁
* Student Number:   3024244054
* Date:             2025/12/29 09:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #15
*******************************************************************************/

#include "myHash.h"
#include <cstring>


MyHash::MyHash(int max_element){
    maxSize = nextPrime(max_element);
    keys = new int[maxSize];
    values = new int[maxSize];
    nowSize = 0;
    for(int i = 0; i < maxSize; i++) {
        keys[i] = 0;
        values[i] = 0;
    }
}

MyHash::~MyHash(){
    delete[] keys;
    delete[] values;
}

void MyHash::setvalue(int key, int value){
    if(nowSize >= maxSize && find(key) == -1) return;
    
    int index = hash_Mod(key);
    
    for (int attempt = 0; attempt < maxSize; attempt++) {
        int newIndex = rehash(index, attempt);
        
        if (keys[newIndex] == 0) {
            keys[newIndex] = key;
            values[newIndex] = value;
            nowSize++;
            return;
        }
        
        if (keys[newIndex] == key) {
            values[newIndex] = value;
            return;
        }
    }
}

int MyHash::getvalue(int key){
    if(key == 0) return 0;
    return find(key);
}

int MyHash::find(int key){
    int index = hash_Mod(key);
    
    for (int attempt = 0; attempt < maxSize; attempt++) {
        int newIndex = rehash(index, attempt);
        
        if (keys[newIndex] == 0) {
            return -1;
        }
        
        if (keys[newIndex] == key) {
            return values[newIndex];
        }
    }
    
    return -1;
}
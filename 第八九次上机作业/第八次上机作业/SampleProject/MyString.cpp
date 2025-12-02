/*******************************************************************************
* FileName:         MyString.cpp
* Author:           Your_Name
* Student Number:   3022244xxx
* Date:             2023/03/23 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #5
*                   完成程度：
*                       简要说一下自己写了多少，完成了哪些函数
*******************************************************************************/
#include <cstdio>
#include <cstdlib>
#include "MyString.h"


MyString::MyString(const char* str){
    len =0;
    if(str != nullptr){
        while(str[len]!='\0'){
            len++;
        }
        data = new char[len+1];
        for(int i=0;i<len;i++){
            data[i]=str[i];
        }
        data[len]='\0';
    }
    else{
       data = new char[1];
       data[0]='\0';
       len =0;
    }
}

MyString::~MyString(){
    // 释放动态分配的内存
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
}

int MyString::length() const{
    
    if(data == nullptr)return 0;
    int cnt =0;
    while(data[cnt]!= '\0' ){
        cnt ++;
    }
    return cnt;
}

void MyString::replace(const char* replace, int loc){
    if(replace != nullptr){
        int i=0;
        while(replace[i]!='\0'){
            data[loc+i]=replace[i];
            i++;
        }
        
        return;
    }
    else return;
}

int MyString::find(const char* str) const{
   
    if (str == nullptr || data == nullptr) {
        return -1;
    }
    int patternLen = 0;
    while (str[patternLen] != '\0') {
        patternLen++;
    }
    if (patternLen == 0) {
        return 0;
    }
    if (patternLen > len) {
        return -1;
    }

    // 构建NEXT数组
    // pi[i] 表示 pattern[0..i-1] 的最长真前缀也是真后缀的长度
    int pi[patternLen];
    pi[0] = 0; // 第一个元素总是0
    
    for (int i = 1; i < patternLen; i++) {
        int j = pi[i-1];
        // 根据模式字符串中的下一个字符调整j
        while (j > 0 && str[i] != str[j]) {
            j = pi[j-1];
        }
        if (str[i] == str[j]) {
            j++;
        }
        pi[i] = j;
    }
    
    // 使用KMP算法在文本中搜索模式
    int j = 0; // 模式字符串的索引
    for (int i = 0; i < len; i++) {
        // 在一些匹配后发生不匹配
        while (j > 0 && data[i] != str[j]) {
            j = pi[j-1];
        }
        // 匹配
        if (data[i] == str[j]) {
            j++;
        }
        // 找到完全匹配
        if (j == patternLen) {
            return i - patternLen + 1;
        }
    }
    
    // 未找到匹配
    return -1;
}

const char* MyString::c_string() const{
    return data;
}
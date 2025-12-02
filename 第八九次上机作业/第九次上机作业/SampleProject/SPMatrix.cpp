/*******************************************************************************
* FileName:         SPMatrix.cpp
* Author:           于乘骁
* Student Number:   3024244054
* Date:             2025/11/25 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #6
*
*******************************************************************************/

#include "SPMatrix.h"
#include <vector>
#include <algorithm>
using namespace std;
SPMatrix::SPMatrix(int r, int c){
    max_row = r;
    max_col = c;
}

SPMatrix::SPMatrix(int r, int c, int max_element){
    max_row = r;
    max_col = c;
    max_elem = max_element;

}

int SPMatrix::get(int i, int j)const{
    for (const auto& elem : data) {
        if (elem.row_e == i && elem.col_e == j) {
            return elem.value;
        }
    }
    return 0;
}

void SPMatrix::set(int i, int j, int val){
    // 如果val为0，删除该元素
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (it->row_e == i && it->col_e == j) {
            if (val == 0) {
                data.erase(it);
            } else {
                it->value = val;
            }
            return;
        }
    }
    
    if (val != 0) {
        element_SPM elem;
        elem.row_e = i;
        elem.col_e = j;
        elem.value = val;
        data.push_back(elem);
    }
}


void SPMatrix::rotate() {
    int *rowSize = new int[max_col](); // 初始化为0，转置矩阵每行非零元素的个数
    int *rowStart = new int[max_col];  // 转置矩阵每行第一个非零元素对应其三元组的下标

    for (const auto& elem : data) {
        rowSize[elem.col_e]++;
    }

    // 计算转置后每行第一个非零元素的起始位置
    rowStart[0] = 0;
    for (int i = 1; i < max_col; i++) {
        rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
    }

    // 创建转置矩阵
    SPMatrix temp(max_col, max_row, max_elem);
    temp.data.resize(max_elem);

    // 填充转置矩阵的三元组数据
    for (const auto& elem : data) {
        int pos = rowStart[elem.col_e]++;
        temp.data[pos].row_e = elem.col_e;
        temp.data[pos].col_e = elem.row_e;
        temp.data[pos].value = elem.value;
    }

    // 将转置结果赋值给当前矩阵
    *this = temp;

    // 释放动态分配的内存
    delete[] rowSize;
    delete[] rowStart;
}

SPMatrix SPMatrix::operator+(const SPMatrix& b){
    SPMatrix result(max_row,max_col,max_elem + b.max_elem);
    int i=0,j=0;
    int n1 = data.size() , n2 = b.data.size();

    while(i<n1 && j<n2){
        int r1 = data[i].row_e, c1 = data[i].col_e;
        int r2 = b.data[j].row_e, c2 = b.data[j].col_e;
        if(r1<r2||(r1==r2&& c1 <c2)){
            result.data.push_back(data[i]);
            i++;
        }
        else if(r1>r2||(r1==r2&& c1 >c2)){
            result.data.push_back(b.data[j]);
            j++;
        }
        else{
            int summed_value = data[i].value + b.data[j].value;
            if(summed_value != 0){
                element_SPM elem;
                elem.row_e = r1;
                elem.col_e = c1;
                elem.value = summed_value;
                result.data.push_back(elem);
            }
            i++;
            j++;
        }
    }
    while(i<n1){
        result.data.push_back(data[i]);
        i++;
    }
    while(j<n2){
        result.data.push_back(b.data[j]);
        j++;
    }
    result.max_elem = result.data.size();
    return result;
}

SPMatrix SPMatrix::operator-(const SPMatrix& b){
    SPMatrix result(max_row,max_col,max_elem + b.max_elem);
    int i=0,j=0;
    int n1 = data.size() , n2 = b.data.size();
    while (i<n1 && j<n2){
        int r1 = data[i].row_e, c1 = data[i].col_e;
        int r2 = b.data[j].row_e, c2 = b.data[j].col_e;
        if (r1 < r2 || (r1 == r2 && c1 < c2)) {
            result.data.push_back(data[i]);
            i++;
        } else if (r1 > r2 || (r1 == r2 && c1 > c2)) {
            // 注意这里要取-b的值
            result.data.push_back({r2, c2, -b.data[j].value});
            j++;
        } else {
            int diff = data[i].value - b.data[j].value;
            if (diff != 0) {
                result.data.push_back({r1, c1, diff});
            }
            i++;
            j++;
        }
    }
    // 剩余部分直接加入
    while (i < n1) {
        result.data.push_back(data[i]);
        i++;
    }
    while (j < n2) {
        result.data.push_back({b.data[j].row_e, b.data[j].col_e, -b.data[j].value});
        j++;
    }
    result.max_elem = result.data.size();
    return result;
}

SPMatrix SPMatrix::operator*(const SPMatrix& b){

    // 结果矩阵的最大元素数不会超过A的非零元素数 * B的非零元素数
    SPMatrix result(max_row, b.max_col, max_elem * b.max_elem);

    // 先将b转置，便于按列查找
    SPMatrix bT = b;
    bT.rotate();

    // 遍历A的每一行
    for (int i = 0; i < max_row; ++i) {
        // 遍历B的每一列（即bT的每一行）
        for (int j = 0; j < b.max_col; ++j) {
            int sum = 0;
            // 遍历A的第i行的所有非零元素
            for (const auto& a_elem : data) {
                if (a_elem.row_e != i) continue;
                // 在bT的第j行中查找与a_elem.col_e对应的元素
                for (const auto& b_elem : bT.data) {
                    if (b_elem.row_e == j && b_elem.col_e == a_elem.col_e) {
                        sum += a_elem.value * b_elem.value;
                    }
                }
            }
            if (sum != 0) {
                result.data.push_back({i, j, sum});
            }
        }
    }
    result.max_elem = result.data.size();
    return result;
}

SPMatrix::~SPMatrix(){
    
}
/*******************************************************************************
* FileName:         MySort.cpp
* Author:           Your_name
* Student Number:   Student_Number
* Date:             2023/05/26 09:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #16
*******************************************************************************/

#include "MySort.h"
#define EXCHANGE(a, b) {int temp = a; a = b; b = temp;}
void MySort::bubbleSort(int* arr, int len){
    for(int i = 0; i < len - 1; i++){
        for(int j = 0; j < len - i - 1; j++){
            if(arr[j] > arr[j + 1]){
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void MySort::quickSortHelper(int* arr, int left,int right){
    if(left<right){
        int pivot = partition(arr,left,right);
        quickSortHelper(arr,left,pivot-1);
        quickSortHelper(arr,pivot+1,right);
    }

}

int MySort::partition(int *arr,int left,int right){
    int pivot = arr[left];
    while(left<right){
        while(left<right && arr[right]>=pivot) right--;
        EXCHANGE(arr[left],arr[right]);
        while(left<right && arr[left]<=pivot) left++;
        EXCHANGE(arr[left],arr[right]);
    }
    return left;

}
void MySort::quickSort(int* arr, int len){
    //int base = arr[0];
    quickSortHelper(arr,0,len-1);

}

void MySort::heapify(int* arr, int idx, int len){
    int largest = idx;
    int left = 2 * idx + 1; 
    int right = 2 * idx + 2;
    
    if(left < len && arr[left] > arr[largest]){
        largest = left;
    }
    if(right < len && arr[right] > arr[largest]){
        largest = right;
    }
    
    if(largest != idx){
        EXCHANGE(arr[idx], arr[largest]);
        heapify(arr, largest, len);
    }
}

void MySort::heapSort(int* arr, int len){
    for(int i = len / 2 - 1; i >= 0; i--){
        heapify(arr, i, len);
    }
    
    for(int i = len - 1; i > 0; i--){
        EXCHANGE(arr[0], arr[i]); 
        heapify(arr, 0, i); 
    }
}
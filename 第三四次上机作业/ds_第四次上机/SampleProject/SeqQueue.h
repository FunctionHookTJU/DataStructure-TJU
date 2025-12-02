/*******************************************************************************
* FileName:         SeqStack.h
* Author:           your_name
* Student Number:   3022244xxx
* Date:             2023/03/17 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #4
*                   待完成的SeqQueue.h文件
*******************************************************************************/

#ifndef SEQQUEUE_H
#define SEQQUEUE_H

#include "MyQueue.h"

class SeqQueue: public MyQueue{
private:
    static const int INITIAL_CAPACITY = 100; // 队列初始容量
    int* data; // 存储队列元素的数组
    int frontP; // 队首指针
    int rearP; // 队尾指针
    int capacity; // 队列容量
public:
    SeqQueue();
    virtual ~SeqQueue();
    void pop_front();
    void push_back(int data);
    int front() const;
};
#endif
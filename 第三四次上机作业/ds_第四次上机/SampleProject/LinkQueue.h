/*******************************************************************************
* FileName:         SeqQueue.h
* Author:           your_name
* Student Number:   3022244xxx
* Date:             2023/03/17 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #4
*                   需要完成的SeqQueue.h，
*******************************************************************************/

#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "MyQueue.h"

class LinkQueue: public MyQueue{
private:
    struct Node {
        int data;
        Node* next;
        Node(int d) : data(d), next(nullptr) {}
    };
    
    Node* frontP;  // 队头指针
    Node* rearP;   // 队尾指针
    int size;
public:
    LinkQueue();
    virtual ~LinkQueue();
    void push_back(int data);
    void pop_front();
    int front() const;
};


#endif

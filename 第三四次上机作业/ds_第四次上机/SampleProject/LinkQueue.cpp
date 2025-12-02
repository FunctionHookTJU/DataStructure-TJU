#include "LinkQueue.h"

LinkQueue::LinkQueue() {
    frontP = nullptr;
    rearP = nullptr;
    size = 0;
}

LinkQueue::~LinkQueue(){
    while(frontP != nullptr){
        Node * temp = frontP;
        frontP = frontP->next;
        delete temp;
    }
    rearP = nullptr;
    size = 0;
}

void LinkQueue::push_back(int data){
    if(frontP == nullptr){
        Node * newNode = new Node(data);
        rearP = newNode;
        frontP = newNode;
        //frontP = rearP = new Node(data);
    }
    else{
        Node* newNode = new Node(data);
        rearP->next = newNode;
        rearP = newNode;
    }
    size++;
}

void LinkQueue::pop_front(){
    if(size == 0) return;

    Node * temp = frontP;
    frontP = frontP->next;
    delete temp;
    size--;

    if(size == 0) rearP = nullptr;
}


int LinkQueue::front() const{
    if(frontP == nullptr) return -1;
    return frontP->data;
}
#include "SeqQueue.h"

SeqQueue::SeqQueue(){
    capacity = INITIAL_CAPACITY;
    data = new int[capacity];
    frontP = 0;
    rearP = 0;
}

SeqQueue::~SeqQueue(){
    delete[] data;
    data = nullptr;
}

void SeqQueue::pop_front(){
    if(frontP == rearP){ 
        return;
    }
    for(int i = frontP; i < rearP - 1; i++){
        data[i] = data[i + 1];
    }
    rearP--;  
}

void SeqQueue::push_back(int data){
    if(rearP>=capacity){
        return;
    }
    
    this->data[rearP]=data;
    rearP++;
    return;
}

int SeqQueue::front() const{
    if(frontP == rearP){ 
        return -1;
    }
    return data[frontP];
}
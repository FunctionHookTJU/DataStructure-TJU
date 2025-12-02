/*******************************************************************************
* FileName:         LinkList.cpp
* Author:           Your_Name
* Student Number:   3022244xxx
* Date:             2023/02/26 11:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #2
*                   作业在这个文件中完成，需要补全LinkList类的实现，
*                   写明必要的注释
*******************************************************************************/

#include "LinkList.h"

LinkList::LinkList(){
    head = nullptr;
    len = 0;
}

LinkList::~LinkList(){
    node* p = head;
    while (p != nullptr) {
        node* toDelete = p;
        p = p->next;
        delete toDelete;
    }
}

int LinkList::length() const{
    
    return len;
}

int LinkList::getData(const int& location) const{
    if(location<0||location >=len||head==nullptr){
        return -1;
    }
    node *p=head;
    int count=0;
    while(count<location&&p!=nullptr){
        p=p->next;
        count++;
    }
    return p->value;
}

void LinkList::insert(const int& data, const int& location){
    
    if(location < 0 || location > len) {
        return; 
    }

    node* newNode = new node();
    newNode->value = data;
    newNode->next = nullptr;
    
    if (head == nullptr || location == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        node* p = head;
        int count = 0;
        while (count < location - 1 && p->next != nullptr) {
            p = p->next;
            count++;
        }
        
        newNode->next = p->next;
        p->next = newNode;
    }
    
    len++;
}

bool LinkList::remove(const int& location){
    if(location<0||location >=len||head==nullptr){
        return false;
    }

    node *toDelete=nullptr;
    int count=0;
    if(location==0){
        toDelete=head;
        head=head->next;
    }
    else{
        node*p=head;
        int count=0;
        while(count<location-1&&p->next!=nullptr){
            p=p->next;
            count++;
        }
        if(p->next==nullptr)return false;
        toDelete=p->next;
        p->next=toDelete->next;
    }
    delete toDelete;

    len--;
    return true;
}

void LinkList::converse() {
    if (len == 0 || len == 1) {
        return;
    }
    
    node* prev = nullptr;
    node* curr = head;
    node* next = nullptr;
    
    while (curr != nullptr) {
        next = curr->next;  
        curr->next = prev;  
        prev = curr;       
        curr = next;      
    }
    
    head = prev;
}

void LinkList::append(const LinkList& append_list){
    // 如果要追加的链表为空，直接返回
    if (append_list.head == nullptr) {
        return; 
    }
    
    // 找到当前链表的尾节点（如果当前链表为空则为nullptr）
    node *p_current = head;
    if (head != nullptr) {
        while (p_current->next != nullptr) {
            p_current = p_current->next;
        }
    }
    
    // 遍历要追加的链表，复制所有节点
    node *p_append = append_list.head;
    while (p_append != nullptr) {
        node *new_node = new node();
        new_node->value = p_append->value;
        new_node->next = nullptr;
        
        if (p_current == nullptr) {
            // 当前链表为空，设置新节点为头节点
            head = new_node;
        } else {
            // 当前链表非空，追加到尾部
            p_current->next = new_node;
        }
        
        p_current = new_node;
        p_append = p_append->next;
        len++;
    }
}
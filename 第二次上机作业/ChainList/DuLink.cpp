#include "DuLink.h"

DuLink::DuLink(){
    head = nullptr;  // 初始化头指针为空
    tail = nullptr;  // 初始化尾指针为空
    len = 0;         // 初始长度为0
}
DuLink::~DuLink(){
    node* p = head;
    while (p != nullptr) {
        node* toDelete = p;
        p = p->next;
        delete toDelete;
    }
}

int DuLink::length() const {
    return len;
}
int DuLink::getData(const int& location) const{
    if(location < 0 || location >= len || head == nullptr || len == 0){
        return -1;
    }
    
    if(location <= len / 2){
        node *p = head;
        int count = 0;
        while(count < location && p != nullptr){
            p = p->next;
            count++;
        }
        return (p != nullptr) ? p->value : -1;
    }
    else{
        node *q = tail;
        int count = len - 1;
        while(count > location && q != nullptr){
            q = q->pre;
            count--;
        }
        return (q != nullptr) ? q->value : -1;
    }
}
void DuLink::insert(const int& data, const int& location) {
    if (location < 0 || location > len) {
        return;
    }
    node* newNode = new node();
    newNode->value = data;
    newNode->next = nullptr;
    newNode->pre = nullptr;
    if (head == nullptr || location == 0) {
        newNode->next = head;
        if (head != nullptr) {
            head->pre = newNode;
        }
        head = newNode;
        if (len == 0) {
            tail = newNode;
        }
    }
    else if (location == len) {
        tail->next = newNode;
        newNode->pre = tail;
        tail = newNode;
    }
    else {
        if (location <= len / 2) {
            node* p = head;
            int count = 0;
            while (count < location - 1 && p != nullptr) {
                p = p->next;
                count++;
            }
            newNode->next = p->next;
            newNode->pre = p;
            if (p->next != nullptr) {
                p->next->pre = newNode;
            }
            p->next = newNode;
        }

        else {
            node* p = tail;
            int count = len - 1;
            while (count > location && p != nullptr) {
                p = p->pre;
                count--;
            }
            newNode->pre = p->pre;
            newNode->next = p;
            if (p->pre != nullptr) {
                p->pre->next = newNode;
            }
            p->pre = newNode;
        }
    }
    len++;
}
bool DuLink::remove(const int& location) {
    if (location < 0 || location >= len || head == nullptr) {
        return false;
    }
    
    node* toDelete = nullptr;
    
    if (head == tail) {
        toDelete = head;
        head = nullptr;
        tail = nullptr;
    }
    else if (location == 0) {
        toDelete = head;
        head = head->next;
        head->pre = nullptr;  
    }
    else if (location == len - 1) {
        toDelete = tail;
        tail = tail->pre;
        tail->next = nullptr; 
    }

    else {
        if (location < len / 2) {
          
            node* p = head;
            int pos = 0;  
            while (pos < location - 1) {
                p = p->next;
                pos++;
            }
            toDelete = p->next;
            p->next = toDelete->next;
            if (toDelete->next != nullptr) {
                toDelete->next->pre = p;
            }
        }
        else {
         
            node* p = tail;
            int pos = len - 1;  
            while (pos > location) {  
                p = p->pre;
                pos--;
            }
            toDelete = p;
            if (p->pre != nullptr) {
                p->pre->next = p->next;
            }
            if (p->next != nullptr) {
                p->next->pre = p->pre;
            }
        }
    }
    
    delete toDelete;
    len--;
    return true;
}


void DuLink::append(const DuLink& append_list){
    if (append_list.head == nullptr) {
        return;
    }

    node* p_append = append_list.head;

    // 当前链表为空：创建新链表并复制所有节点
    if (head == nullptr) {
        head = new node();
        head->value = p_append->value;
        head->next = nullptr;
        head->pre = nullptr;
        tail = head;
        len++;

        p_append = p_append->next;
        while (p_append != nullptr) {
            node* new_node = new node();
            new_node->value = p_append->value;
            new_node->next = nullptr;
            new_node->pre = tail;
            tail->next = new_node;
            tail = new_node;
            len++;
            p_append = p_append->next;
        }
        return;
    }

    // 当前链表非空：从 tail 开始追加复制节点
    node* p_current = tail;
    while (p_append != nullptr) {
        node* new_node = new node();
        new_node->value = p_append->value;
        new_node->next = nullptr;
        new_node->pre = p_current;
        if (p_current != nullptr) {
            p_current->next = new_node;
        }
        p_current = new_node;
        tail = new_node;
        len++;
        p_append = p_append->next;
    }
}

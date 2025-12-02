#include "CycLink.h"

CycLink::CycLink(){
    head = nullptr;
    tail = nullptr;
    len = 0;
}

CycLink::~CycLink(){
    if (head == nullptr) return;
    
    node* p = head;
    while (p->next != head) {
        node* toDelete = p;
        p = p->next;
        delete toDelete;
    }
    delete p;
}

int CycLink::length() const {
    return len;
}

int CycLink::getData(const int& location) const {
    if (location < 0 || location >= len || head == nullptr) {
        return -1;
    }
    
    node* p = head;
    int count = 0;
    while (count < location && p != nullptr) {
        p = p->next;
        count++;
    }
    return (p != nullptr) ? p->value : -1;
}

void CycLink::insert(const int& data, const int& location) {
    if (location < 0 || location > len) {
        return;
    }
    
    node* newNode = new node();
    newNode->value = data;
    newNode->next = nullptr;
    
    if (head == nullptr) {
        newNode->next = newNode;
        head = newNode;
        tail = newNode;
    }
    else if (location == 0) {
        newNode->next = head;
        head = newNode;
        tail->next = head;
    }
    else if (location == len) {
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;
    }
    else {
        node* p = head;
        int count = 0;
        while (count < location - 1) {
            p = p->next;
            count++;
        }
        newNode->next = p->next;
        p->next = newNode;
    }
    
    len++;
}

bool CycLink::remove(const int& location) {
    if (location < 0 || location >= len || head == nullptr) {
        return false;
    }
    
    node* toDelete = nullptr;
    
    if (head == tail) {
        toDelete = head;
        delete toDelete;
        head = nullptr;
        tail = nullptr;
        len--;
        return true;
    }
    
    if (location == 0) {
        toDelete = head;
        head = head->next;
        tail->next = head;
        delete toDelete;
    }
    else if (location == len - 1) {
        node* p = head;
        while (p->next != tail) {
            p = p->next;
        }
        toDelete = tail;
        tail = p;
        tail->next = head;
        delete toDelete;
    }
    else {
        node* p = head;
        int count = 0;
        while (count < location - 1) {
            p = p->next;
            count++;
        }
        toDelete = p->next;
        p->next = toDelete->next;
        delete toDelete;
    }
    
    len--;
    return true;
}

void CycLink::converse() {
    if (len == 0 || len == 1) {
        return;
    }
    
    node* prev = tail;
    node* curr = head;
    node* next = nullptr;
    
    for (int i = 0; i < len; i++) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    
    head = prev;
    tail = curr;
}

void CycLink::append(const CycLink& append_list) {
    if (append_list.head == nullptr) {
        return;
    }
    
    if (head == nullptr) {
        node* p_append = append_list.head;
        for (int i = 0; i < append_list.len; i++) {
            node* new_node = new node();
            new_node->value = p_append->value;
            
            if (head == nullptr) {
                new_node->next = new_node;
                head = new_node;
                tail = new_node;
            } else {
                new_node->next = head;
                tail->next = new_node;
                tail = new_node;
            }
            p_append = p_append->next;
            len++;
        }
        return;
    }
    
    node* p_append = append_list.head;
    for (int i = 0; i < append_list.len; i++) {
        node* new_node = new node();
        new_node->value = p_append->value;
        new_node->next = head;
        tail->next = new_node;
        tail = new_node;
        p_append = p_append->next;
        len++;
    }
}
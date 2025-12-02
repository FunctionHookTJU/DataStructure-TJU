//自行实现循环链表

#ifndef CYCLINK_H
#define CYCLINK_H
class CycLink {
private:
    //value为节点的值， next为后继节点。
    struct node {
        int value;
        node* next;
    };
    // a pointer point to link list.
    node* head;
    node* tail;
    // the number of elements in Linklist.
    int len;

public:
    CycLink();
    int length() const;
    int getData(const int& location) const;
    void insert(const int& data, const int& location);
    bool remove(const int& location);
    void converse();
    void append(const CycLink& append_list);
    ~CycLink();
};
#endif

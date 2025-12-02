// 自行实现双向链表
#ifndef DULINK_H
#define DULINK_H
class DuLink {
private:
    //value为节点的值， next为后继节点。
    struct node {
        int value;
        node* next;
        node* pre;
    };
    // a pointer point to link list.
    node* head;
    node* tail;
    // the number of elements in Linklist.
    int len;

public:
    DuLink();
    int length() const;
    int getData(const int& location) const;
    void insert(const int& data, const int& location);
    bool remove(const int& location);
    void converse();
    void append(const DuLink& append_list);
    ~DuLink();
};

#endif // DULINK_H

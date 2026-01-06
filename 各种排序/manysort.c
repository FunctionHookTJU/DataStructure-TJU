#include "manysort.h"

/**
 * 表插入排序：构建有序循环链表
 */
void TableInsertSort(SLinkListType *SL) {
    int i, p, q;
    SL->r[0].rc.key = 2147483647; // 假设r[0]作为表头，其key设为最大值（或不使用其key）
    SL->r[0].next = 1;            // 指向第一个节点
    SL->r[1].next = 0;            // 第一个节点的指针域指向表头，形成循环
    
    for (i = 2; i <= SL->length; ++i) {
        q = 0;
        p = SL->r[q].next; // p指向搜索序列的当前节点
        
        // 寻找插入位置：在第q个记录之后，第p个记录之前
        while (p != 0 && SL->r[p].rc.key <= SL->r[i].rc.key) {
            q = p;
            p = SL->r[p].next;
        }
        
        // 插入记录 i
        SL->r[i].next = p;
        SL->r[q].next = i;
    }
}

/**
 * 根据图示伪代码实现的物理重排逻辑
 * 目的是根据 next 指针的顺序，将记录物理地调整到对应的位置上
 */
void Arrange(SLinkListType *SL) {
    int i, p, q;
    p = SL->r[0].next; // p指示第1个有序记录的位置
    
    for (i = 1; i < SL->length; ++i) { // 依次对第 i 个位置进行调整
        // 第 i 个有序记录当前被移动到了位置 p
        // 如果 p < i，说明第 p 个记录已经排好序并被交换到别处了
        // 我们需要顺着指针链找到现在实际持有该记录的位置
        while (p < i) {
            p = SL->r[p].next;
        }
        
        q = SL->r[p].next; // 记录下一个待排序记录在原链表中的位置
        
        if (p != i) {
            // 物理交换第 i 个和第 p 个记录
            SLNode temp = SL->r[p];
            SL->r[p] = SL->r[i];
            SL->r[i] = temp;
            
            // 关键：交换后，原本在 p 位置的指针信息现在在 i 位置
            // 既然记录已经归位到 i，我们需要让 i 的 next 指向 p (即原 i 被移去的地方)
            // 这样后续的 while(p < i) 才能找到被交换走的记录
            SL->r[i].next = p;
        }
        p = q;
    }
}

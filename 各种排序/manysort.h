#ifndef MANYSORT_H
#define MANYSORT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 宏定义 */
#define MAXSIZE 1000       // 最大记录数
#define SIZE 100           // 表插入排序最大长度
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int KeyType;       // 关键字类型为整型

/* 记录类型定义 */
typedef struct {
    KeyType key;           // 关键字项
} RedType;

/* 顺序表类型定义 */
typedef struct {
    RedType r[MAXSIZE + 1]; // r[0] 闲置或用作哨兵
    int length;             // 顺序表长度
} SqList;

/* 表插入存储结构 (根据图示更新) */
typedef struct {
    RedType rc;             // 记录项
    int next;               // 指针项
} SLNode;

typedef struct {
    SLNode r[SIZE];         // 表记录
    int length;             // 表长度
} SLinkListType;

void TableInsertSort(SLinkListType *SL);
void Arrange(SLinkListType *SL);

#endif

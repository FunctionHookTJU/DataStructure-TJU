/*******************************************************************************
* FileName:         Graph.cpp
* Author:           Your_name
* Student Number:   Student_Number
* Date:             2023/04/29 09:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #12
*******************************************************************************/

#include "Graph.h"
#include <cstring>
#include <iostream>
using namespace std;
//#define INT_MAX 2147483647
Graph::Graph(int v){
    if (v < 1) v = 1;
    maxV = v;
    adjList = new EdgeNode *[v+1];
    inList = new EdgeNode* [v+1];
    inDegree = new int [v+1];
    outDegree = new int [v+1];
    for(int i=0;i<=v;i++){
        adjList[i]=nullptr;
        inList[i]=nullptr;
        inDegree[i]=0;
        outDegree[i]=0;
    }
}

Graph::~Graph(){
    for(int i=0;i<=maxV;i++){
        EdgeNode* p = adjList[i];
        while(p != nullptr){
            EdgeNode* temp = p;
            p = p->next;
            delete temp;
        }
        p = inList[i];
        while (p!= nullptr){
            EdgeNode* temp =p;
            p=p->next;
            delete temp;
        }
    }
    delete[] adjList;
    delete[] inList;
    delete[] inDegree;
    delete[] outDegree;
}

void Graph::appendEdge(EdgeNode*& list, int to, int w){
    EdgeNode* node = new EdgeNode;
    node->to = to;
    node->weight = w;
    node->next = nullptr;
    if (list == nullptr){
        list = node;
    }else{
        EdgeNode* tail = list;
        while (tail->next != nullptr) tail = tail->next;
        tail->next = node;
    }
}

void Graph::addedge(int s, int t, int w){
    if (s < 1 || s > maxV || t < 1 || t > maxV) return;
    appendEdge(adjList[s], t, w);
    appendEdge(inList[t], s, w);
    outDegree[s]++;
    inDegree[t]++;
}

int Graph::getV(){
    return maxV;
}

int* Graph::topological(){
    int *result = new int[maxV];      // 存储拓扑序列
    int *inDeg = new int[maxV+1];     // 拷贝一份入度数组
    memcpy(inDeg, inDegree, sizeof(int)*(maxV+1));
    int front = 0, rear = 0;          // 队列指针
    int *queue = new int[maxV+1];     // 辅助队列

    // 入度为0的点入队
    for(int u=1; u<=maxV; u++){
        if(inDeg[u] == 0){
            queue[rear++] = u;
        }
    }
 
    int idx = 0;
    while(front < rear){
        int u = queue[front++];
        result[idx] = u;
        idx++;
        // 遍历u的所有出边
        EdgeNode* p = adjList[u];
        while(p != nullptr){
            int v = p->to;
            inDeg[v]--;
            if(inDeg[v] == 0){
                queue[rear++] = v;
            }
            p = p->next;
        }
    }

    delete[] inDeg;
    delete[] queue;

    // 如果idx==maxV，说明无环，返回拓扑序列
    if(idx == maxV){
        return result;
    }else{
        cout << "Graph has no topological order due to cycle." << endl;
        delete[] result;
        return nullptr; // 有环，无法拓扑排序
    }
}

int* Graph::ka(){
    // 获取拓扑序列
    int *topo = topological();
    if(topo == nullptr){
        return nullptr;             // 有环时没有关键事件
    }

    int *ve = new int[maxV + 1];    // 最早发生时间
    int *vl = new int[maxV + 1];    // 最晚允许时间
    
    // 初始化最早发生时间
    memset(ve, 0 , sizeof(int)*(maxV+1));
    // 依据拓扑序计算最早发生时间 ve
    for(int i = 0; i < maxV; ++i){
        int u = topo[i];
        EdgeNode *p = adjList[u];
        while(p != nullptr){
            int v = p->to;
            int cand = ve[u] + p->weight;
            if(cand > ve[v]){
                ve[v] = cand;
            }
            p = p->next;
        }
    }

    // 找到项目完成时间（最大的ve值）
    int totalTime = 0;
    for(int i = 1; i <= maxV; ++i){
        if(ve[i] > totalTime){
            totalTime = ve[i];
        }
    }
    
    // 初始化最晚允许时间
    for(int i = 1; i <= maxV; ++i){
        vl[i] = totalTime;
    }

    // 逆拓扑序刷新最晚允许时间 vl
    for(int i = maxV - 1; i >= 0; --i){
        int u = topo[i];
        EdgeNode *p = adjList[u];
        while(p != nullptr){
            int v = p->to;
            int cand = vl[v] - p->weight;
            if(cand < vl[u]){
                vl[u] = cand;
            }
            p = p->next;
        }
    }

    // 收集关键事件节点（顶点满足 ve[i] == vl[i]）
    int *result = new int[maxV];
    int idx = 0;
    
    for(int i = 0; i < maxV; ++i){
        int u = topo[i];
        // 判断是否为关键事件节点
        if(ve[u] == vl[u]){
            result[idx++] = u;
        }
    }
    
    // 补齐剩余位置为0（如果有的话）
    for(int i = idx; i < maxV; ++i){
        result[i] = 0;
    }

    delete[] topo;
    delete[] ve;
    delete[] vl;
    return result;
}
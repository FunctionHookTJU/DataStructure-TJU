/*******************************************************************************
* FileName:         Graph.cpp
* Author:           Your_name
* Student Number:   Student_Number
* Date:             2025/12/01
* Version:          v1.0
* Description:      Data Structure Experiment #10
*******************************************************************************/

#include "Graph.h"
#include <queue>

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

int Graph::getInDegree(int v){
    return inDegree[v];
}

int Graph::getOutDegree(int v){
    return outDegree[v];
}

int Graph::access(int s, int t){
    if (s < 1 || s > maxV || t < 1 || t > maxV) return -1; // 边界检查
    EdgeNode* p = adjList[s]; // 修正：遍历出边表
    while(p != nullptr){
        if(p->to == t){
            return p->weight;
        }
        p = p->next;
    }
    return -1; // 未找到
}

int Graph::getDist(int s, int t){
    if (s < 1 || s > maxV || t < 1 || t > maxV) return -1;
    if (s == t) return 0;
    
    int *dist = new int [maxV+1];
    for(int i=1;i< maxV+1;i++){
        dist[i]=-1;//初始化未访问状态
    }
    using namespace std;
    queue<int> q;
    q.push(s);
    dist[s]=0;

    while(!q.empty()){
        int u = q.front();
        q.pop();
        EdgeNode* p = adjList[u];
        while(p !=nullptr){
            int v = p->to;
            if(dist[v]==-1){
                dist[v]=dist[u]+1;
                if(v == t){
                    int result = dist[v];
                    delete[]dist;
                    return result;

                }
                q.push(v);
            }
            p=p->next;
        }
    }
    delete[] dist;
    return -1;

}
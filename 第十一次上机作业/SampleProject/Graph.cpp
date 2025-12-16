/*******************************************************************************
* FileName:         Graph.cpp
* Author:           Your_name
* Student Number:   Student_Number
* Date:             2023/04/22 09:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #11
*******************************************************************************/

#include "Graph.h"
#include <cstring>
#define INT_MAX 2147483647
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
    EdgeNode* newNode = new EdgeNode;
    newNode->to = to;
    newNode->weight = w;
    newNode->next = list;
    list = newNode;
}

void Graph::addedge(int s, int t, int w){
    if (s < 1 || s > maxV || t < 1 || t > maxV) return;
    appendEdge(adjList[s], t, w);
    appendEdge(inList[t], s, w);
    outDegree[s]++;
    inDegree[t]++;
}

int Graph::prim(){
    bool* vis = new bool[maxV+1];
    int* dist = new int[maxV+1];
    memset(vis , false,sizeof(bool)*(maxV+1));
    memset(dist , 0x3f3f3f3f,sizeof(int)*(maxV+1));
    dist[1] = 0;
    int totalcost = 0;
    int cnt = 0;
    for(int i = 0;i<maxV;i++){
        int u = -1;
        int minD = 0x3f3f3f3f;
        for(int j=1;j<=maxV;j++){
            if(!vis[j] && dist[j]<minD){
                minD = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        vis[u] = true;
        totalcost  += minD;
        ++cnt;
        // 遍历 u 的所有邻接边，更新距离
        EdgeNode* p = adjList[u];
        while(p != nullptr){
            int v = p->to;
            if(!vis[v] && p->weight < dist[v]){
                dist[v] = p->weight;
            }
            p = p->next;
        }
    }
    delete[] vis;
    delete[] dist;
    return cnt == maxV ? totalcost : -1;
}

int Graph::kruskal(){
    // 边的结构体，用于排序
    struct Edge{
        int from, to, weight;
        bool operator<(const Edge& other) const{
            return weight < other.weight;
        }
    };
    
    // 收集所有边（无向图，每条边只记录一次）
    Edge* edges = new Edge[maxV * maxV];
    int edgeCount = 0;
    
    for(int u = 1; u <= maxV; u++){
        EdgeNode* p = adjList[u];
        while(p != nullptr){
            int v = p->to;
            // u从1开始遍历，则总是指向u之后的节点，避免重复。
            if(u < v){
                edges[edgeCount].from = u;
                edges[edgeCount].to = v;
                edges[edgeCount].weight = p->weight;
                edgeCount++;
            }
            p = p->next;
        }
    }
    
    // 对边按权重排序（简单冒泡排序）
    for(int i = 0; i < edgeCount - 1; i++){
        for(int j = 0; j < edgeCount - i - 1; j++){
            if(edges[j + 1] < edges[j]){
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
    
    // 并查集初始化
    int* parent = new int[maxV + 1];
    for(int i = 1; i <= maxV; i++){
        parent[i] = i;  // 每个节点的父节点初始化为自己
    }
    
    // 查找根节点函数（带路径压缩）
    struct UnionFind{
        int* parent;
        int find(int x){
            if(parent[x] != x){
                parent[x] = find(parent[x]);  // 路径压缩
            }
            return parent[x];
        }
    };
    
    UnionFind uf;
    uf.parent = parent;
    
    int totalcost = 0;
    int edgeUsed = 0;
    
    // 按权重从小到大遍历每条边
    for(int i = 0; i < edgeCount; i++){
        int u = edges[i].from;
        int v = edges[i].to;
        int w = edges[i].weight;
        
        int rootU = uf.find(u);
        int rootV = uf.find(v);
        
        // 如果 u 和 v 不在同一集合，则加入这条边
        if(rootU != rootV){
            parent[rootU] = rootV;  // 合并集合
            totalcost += w;
            edgeUsed++;
            
            // 如果已经使用了 maxV-1 条边，MST 构建完成
            if(edgeUsed == maxV - 1){
                break;
            }
        }
    }
    
    delete[] edges;
    delete[] parent;
    
    // 如果使用的边数等于 maxV-1，说明构建成功
    return edgeUsed == maxV - 1 ? totalcost : -1;
}
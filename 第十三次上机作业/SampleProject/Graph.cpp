/*******************************************************************************
* FileName:         Graph.cpp
* Author:           Your_name
* Student Number:   Student_Number
* Date:             2025/12/15 09:24:55
* Version:          v1.0
* Description:      Data Structure Experiment #13
*******************************************************************************/

#include <vector>
#include <limits>
#include "Graph.h"
using namespace std;
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

#define INF 0x3f3f3f3f

vector<int> Graph::dijkstra_impl(int start)const{
    vector<int> dist(maxV+1, INF);
    vector<bool> visited(maxV+1, false);
    
    dist[start] = 0;
    
    for(int i = 1; i <= maxV; i++){
        int u = -1;
        for(int v = 1; v <= maxV; v++){
            if(!visited[v] && (u == -1 || dist[v] < dist[u])){
                u = v;
            }
        }
        
        if(u == -1 || dist[u] == INF) break;
        
        visited[u] = true;
        
        // 松弛相邻顶点
        EdgeNode* p = adjList[u];
        while(p != nullptr){
            int v = p->to;
            if(dist[u] + p->weight < dist[v]){
                dist[v] = dist[u] + p->weight;
            }
            p = p->next;
        }
    }
    
    return dist;
}

int* Graph::dijkstra(){
    vector<int> dist = dijkstra_impl(1);
    int* result = new int[maxV+1];
    
    result[0] = 0;
    for(int i = 1; i <= maxV; i++){
        if(dist[i] == INF){
            result[i] = -1;
        }else{
            result[i] = dist[i];
        }
    }
    
    return result;
}
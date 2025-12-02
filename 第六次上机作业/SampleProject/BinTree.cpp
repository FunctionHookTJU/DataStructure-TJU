/*******************************************************************************
 * FileName:         BinTree.cpp
 * Author:           Your_name
 * Student Number:   Student_Number
 * Date:             2023/04/04 09:24:55
 * Version:          v1.0
 * Description:      Data Structure Experiment #8
 *******************************************************************************/

#include "BinTree.h"
#include <queue>
#include <stack>
#include <iostream>
using namespace std;
BinTree::BinTree()
{
    root = nullptr;
}

BinTree::~BinTree()
{
    deletetree(root);
}

void BinTree::insert(int val, int parent, int flg)
{
    node* newNode = new node;
    newNode->val = val;
    newNode->left = nullptr;
    newNode->right = nullptr;
    
    if(parent == 0){
        root = newNode;
        return;
    }
    
    std::queue<node*> q;
    q.push(root);
    int nodeNumber = 1;
    
    while(!q.empty()){
        node* current = q.front();
        q.pop();
        
        if(nodeNumber == parent){
            if(flg == -1){
                current->left = newNode;
            }
            else if(flg == 1){
                current->right = newNode;
            }
            return;
        }
        
        if(current->left != nullptr){
            q.push(current->left);
        }
        if(current->right != nullptr){
            q.push(current->right);
        }
        
        nodeNumber++;
    }
}

int *BinTree::p_traversal() const
{
    if (root == nullptr) return nullptr;
    
    int nodeCount = countNode();
    int* result = new int[nodeCount];
    
    stack<node*> st;
    st.push(root);
    int index = 0;
    
    while (!st.empty()) {
        node* cur = st.top(); 
        st.pop();  
        result[index++] = cur->val;
        
        if (cur->right) st.push(cur->right);
        if (cur->left) st.push(cur->left);
    }
    
    return result;
}

int *BinTree::m_traversal() const
{
    if(root == nullptr) return nullptr;
    
    int nodeCount = countNode();
    int* result = new int[nodeCount];
    
    stack<node*> st;
    node* cur = root;
    int index = 0;
    
    while (cur || !st.empty()) {
        while (cur) {
            st.push(cur);
            cur = cur->left;
        }
        cur = st.top(); st.pop();
        result[index++] = cur->val;
        cur = cur->right;
    }
    
    return result;
}

int *BinTree::s_traversal() const
{
    if (root == nullptr) return nullptr;
    
    int nodeCount = countNode();
    int* result = new int[nodeCount];
    
    stack<node*> st;
    node* cur = root;
    node* lastVisited = nullptr;
    int index = 0;
    
    while (cur || !st.empty()) {
        while (cur) {
            st.push(cur);
            cur = cur->left;
        }
        
        cur = st.top();
        
        if (!cur->right || cur->right == lastVisited) {
            result[index++] = cur->val;
            st.pop();
            lastVisited = cur;
            cur = nullptr;
        } else {
            cur = cur->right;
        }
    }
    
    return result;
}

int BinTree::countNode() const{
    return countNodeHelper(root);
}

int BinTree::countNodeHelper(node* node) const{
    if (node == nullptr) return 0;
    
    return 1 + countNodeHelper(node->left) + countNodeHelper(node->right);
}

int BinTree::height() const
{
    return heightHelper(root);
}

int BinTree::heightHelper(node* node) const
{
    if (node == nullptr) return 0;
    
    int lheight = heightHelper(node->left);
    int rheight = heightHelper(node->right);
    
    return (lheight > rheight) ? (lheight + 1) : (rheight + 1);
}

void BinTree::deletetree(node *root) const
{
    if (root == nullptr)
        return;
    deletetree(root->left);
    deletetree(root->right);
    delete root;
}


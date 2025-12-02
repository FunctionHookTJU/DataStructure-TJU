/*******************************************************************************
* FileName:         Haffman.cpp
* Author:           Your_name
* Student Number:   Student_Number
* Date:             2025/11/16
* Version:          v1.1
* Description:      Data Structure Experiment #7
*******************************************************************************/

#include "Huffman.h"
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

HuffmanTree::HuffmanTree(const int* Table){
    struct Node {
        HuffmanTree* tree;
        int weight;
    };
    vector<Node> nodes;
    for (int i = 0; i < 26; i++) {
        if (Table[i] > 0) {
            HuffmanTree* node = new HuffmanTree();
            node->data = 'a' + i;
            node->weight = Table[i];
            node->left = nullptr;
            node->right = nullptr;
            nodes.push_back({node, Table[i]});
        }
    }
    while (nodes.size() > 1) {
        sort(nodes.begin(), nodes.end(), [](const Node& a, const Node& b) {
            return a.weight < b.weight;
        });
        Node first = nodes[0];
        Node second = nodes[1];
        nodes.erase(nodes.begin());
        nodes.erase(nodes.begin());
        HuffmanTree* parent = new HuffmanTree();
        parent->data = '\0';
        parent->weight = first.weight + second.weight;
        if (first.weight <= second.weight) {
            parent->left = first.tree;
            parent->right = second.tree;
        } else {
            parent->left = second.tree;
            parent->right = first.tree;
        }
        nodes.push_back({parent, parent->weight});
    }
    if (!nodes.empty()) {
        HuffmanTree* root = nodes[0].tree;
        this->data = root->data;
        this->weight = root->weight;
        this->left = root->left;
        this->right = root->right;
        root->left = nullptr;
        root->right = nullptr;
        delete root;
    }
}

HuffmanTree::~HuffmanTree(){
    if (left != nullptr) {
        delete left;
        left = nullptr;
    }
    if (right != nullptr) {
        delete right;
        right = nullptr;
    }
}

void HuffmanTree::buildCodeTable(string code, map<char, string>& codeMap) {
    if (left == nullptr && right == nullptr && data != '\0') {
        codeMap[data] = code;
        return;
    }
    if (left != nullptr) {
        left->buildCodeTable(code + "0", codeMap);
    }
    if (right != nullptr) {
        right->buildCodeTable(code + "1", codeMap);
    }
}

string HuffmanTree::Encode(string message){
    map<char, string> codeMap;
    buildCodeTable("", codeMap);
    string result = "";
    for (int i = 0; i < message.length(); i++) {
        char ch = message[i];
        if (codeMap.find(ch) != codeMap.end()) {
            result += codeMap[ch];
        }
    }
    return result;
}

string HuffmanTree::Decode(string message){
    string result = "";
    HuffmanTree* current = this;
    for (int i = 0; i < message.length(); i++) {
        char bit = message[i];
        if (bit == '0') {
            if (current->left != nullptr) {
                current = current->left;
            }
        } else if (bit == '1') {
            if (current->right != nullptr) {
                current = current->right;
            }
        }
        if (current->left == nullptr && current->right == nullptr && current->data != '\0') {
            result += current->data;
            current = this;
        }
    }
    return result;
}
/*******************************************************************************
* FileName:         Haffman.h
* Author:           Name
* Student Number:   3024244XXX
* Date:             2025/11/16 
* Version:          v1.1
* Description:      Data Structure Experiment #7
*******************************************************************************/

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <string>
#include <map>
using std::string;
using std::map;

class HuffmanTree{
private:
    char data;
    int weight;
    HuffmanTree *left,*right;
    
    // 私有默认构造函数，用于内部创建节点
    HuffmanTree() : data('\0'), weight(0), left(nullptr), right(nullptr) {}
    
    // 私有辅助函数：递归构建编码表
    void buildCodeTable(string code, map<char, string>& codeMap);
    
public:
    /**
     *  构造函数
        @name HuffmanTree(const int* Table)
        @param arg1 数字出现的频度表
        @return
        注意： 要求树的左孩子为权制较小的编码，左孩子的二进制编号为0
    */
    HuffmanTree(const int* Table);

    /**
     *  析构函数
        @name ~HuffmanTree()
        @param 
        @return
    */
    ~HuffmanTree();

    /**
     *  获取message的霍夫曼编码
        @name string Encode(string)
        @param  arg1 待编码待字符串
        @return 对应的霍夫曼编码
    */
    string Encode(string message);


    /**
     *  获取message的霍夫曼解码
        @name string Decode(stirng)
        @param 
        @return 解码出的内容
    */
    string Decode(string message);
};

#endif
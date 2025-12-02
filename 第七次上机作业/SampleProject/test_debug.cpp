#include <iostream>
#include <cstdio>
#include <cstring>

#include "Huffman.h"
using namespace std;

int main()
{
    int table[26];
    memset(table, 0, sizeof(table));
    table[0] = 4;  // a
    table[1] = 2;  // b
    table[2] = 1;  // c
    
    HuffmanTree hf(table);
    
    string encoded = hf.Encode("abc");
    cout << "Encode(\"abc\") = \"" << encoded << "\"" << endl;
    cout << "Expected: \"10100\"" << endl;
    
    if(encoded == "10100") {
        cout << "pass check point 1!" << endl;
    } else {
        cout << "FAIL check point 1!" << endl;
    }
    
    string decoded = hf.Decode("10100");
    cout << "Decode(\"10100\") = \"" << decoded << "\"" << endl;
    cout << "Expected: \"abc\"" << endl;
    
    if(decoded == "abc") {
        cout << "pass check point 2!" << endl;
    } else {
        cout << "FAIL check point 2!" << endl;
    }

    system("pause");
    return 0;
}

#include <iostream>
#include <string>
using namespace std;

// 递归函数：将数字n转换为2的幂次方表示
string convert(int n) {
    if (n == 0) {
        return "0";
    }
    
    string result = "";
    bool first = true;  // 标记是否是第一项
    
    // 从高位到低位检查每一位
    for (int i = 31; i >= 0; i--) {  // 2^31 = 2147483648 足够大
        if (n & (1 << i)) {  // 检查第i位是否为1
            if (!first) {
                result += "+";
            }
            first = false;
            
            // 根据幂次的大小决定如何表示
            if (i == 0) {
                result += "2(0)";
            } else if (i == 1) {
                result += "2";
            } else {
                result += "2(" + convert(i) + ")";
            }
        }
    }
    
    return result;
}

int main() {
    int n;
    cin >> n;
    cout << convert(n) << endl;
    return 0;
}
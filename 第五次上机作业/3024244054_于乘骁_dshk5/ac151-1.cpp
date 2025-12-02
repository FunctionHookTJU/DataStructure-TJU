#include <iostream>
#include <stack>
#include <cstring>
#include <cmath>
using namespace std;

// 优先级函数，返回操作符优先级
int youxian(char c) {
    if (c == '^') return 2;
    if (c == '*' || c == '/') return 1;
    if (c == '+' || c == '-') return 0;
    return -1; // 非法操作符
}

stack<int> num;
stack<char> ope;
bool hasError = false; // 错误标志

// 计算函数，根据操作符和两个操作数返回结果
int panduan(char op, int a, int b) {
    if (op == '+')
        return b + a;
    else if (op == '-')
        return b - a;
    else if (op == '*')
        return b * a;
    else if (op == '/') {
        if (a == 0) { // 除零错误
            hasError = true;
            return 0;
        }
        return b / a;
    }
    else if (op == '^')
        return pow(b, a);
    return 0;
}

// 执行一次操作
void work() {
    if (ope.empty() || num.size() < 2) {
        hasError = true;
        return;
    }

    char op = ope.top();
    ope.pop();
    int a = num.top();
    num.pop();
    int b = num.top();
    num.pop();
    int tmp = panduan(op, a, b);
    num.push(tmp);
}

int main() {
    char s[1000];
    cin >> s;
    int len = strlen(s);
    
    // 清空栈和错误标志
    while (!num.empty()) num.pop();
    while (!ope.empty()) ope.pop();
    hasError = false;

    for (int i = 0; i < len; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            int tmp = 0;
            while (i < len && s[i] >= '0' && s[i] <= '9') {
                tmp = tmp * 10 + (s[i] - '0');
                i++;
            }
            num.push(tmp);
            i--;
        }
        else if (s[i] == '(') {
            ope.push(s[i]);
        }
        else if (s[i] == ')') {
            // 找到匹配的左括号并执行操作
            while (!ope.empty() && ope.top() != '(') {
                work();
                if (hasError) break;
            }
            // 如果找到了左括号，弹出它
            if (!ope.empty() && ope.top() == '(') {
                ope.pop();
            }
            // 如果没有找到左括号（右括号多余），忽略这个右括号
        }
        else if (s[i] == '-' && (i == 0 || s[i-1] == '(' || youxian(s[i-1]) >= 0)) {
            // 处理负号：在表达式开头、左括号后、或运算符后的减号视为负号
            num.push(0); // 将负号转换为 0-x
            ope.push('-');
        }
        else if (youxian(s[i]) >= 0) { // 合法操作符
            while (!ope.empty() && ope.top() != '(' && youxian(s[i]) <= youxian(ope.top())) {
                work();
                if (hasError) break;
            }
            ope.push(s[i]);
        }
        else { // 非法字符
            hasError = true;
            break;
        }
    }

    // 处理剩余操作符，忽略多余的左括号
    if (!hasError) {
        while (!ope.empty()) {
            if (ope.top() == '(') {
                // 忽略多余的左括号
                ope.pop();
            } else {
                work();
                if (hasError) break;
            }
        }
    }

    // 输出结果
    if (hasError || num.empty() || num.size() != 1) {
        cout << -1 << endl;
    }
    else {
        cout << num.top() << endl;
    }

    return 0;
}
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

char s[1000];
int pos = 0; // 当前解析位置
bool hasError = false;

// 前向声明
int parseExpression();

// 跳过空白字符
void skipSpaces() {
    while (pos < strlen(s) && s[pos] == ' ') {
        pos++;
    }
}

// 解析数字
int parseNumber() {
    skipSpaces();
    int num = 0;
    bool hasDigit = false;
    
    while (pos < strlen(s) && s[pos] >= '0' && s[pos] <= '9') {
        num = num * 10 + (s[pos] - '0');
        pos++;
        hasDigit = true;
    }
    
    if (!hasDigit) {
        hasError = true;
        return 0;
    }
    
    return num;
}

// 解析因子 (数字或括号表达式或负数)
int parseFactor() {
    skipSpaces();
    
    if (pos >= strlen(s)) {
        hasError = true;
        return 0;
    }
    
    // 处理括号
    if (s[pos] == '(') {
        pos++; // 跳过 '('
        int result = parseExpression();
        skipSpaces();
        
        if (pos < strlen(s) && s[pos] == ')') {
            pos++; // 跳过 ')'
        }
        // 如果没有匹配的右括号，忽略（相当于多余的左括号）
        
        return result;
    }
    
    // 处理负号
    if (s[pos] == '-') {
        pos++;
        return -parseFactor();
    }
    
    // 处理正号
    if (s[pos] == '+') {
        pos++;
        return parseFactor();
    }
    
    // 处理数字
    if (s[pos] >= '0' && s[pos] <= '9') {
        return parseNumber();
    }
    
    hasError = true;
    return 0;
}

// 解析幂运算 (右结合)
int parsePower() {
    int left = parseFactor();
    
    if (hasError) return 0;
    
    skipSpaces();
    
    if (pos < strlen(s) && s[pos] == '^') {
        pos++;
        int right = parsePower(); // 右结合，递归调用自己
        
        if (hasError) return 0;
        
        return pow(left, right);
    }
    
    return left;
}

// 解析乘除运算
int parseTerm() {
    int left = parsePower();
    
    if (hasError) return 0;
    
    while (true) {
        skipSpaces();
        
        if (pos >= strlen(s)) break;
        
        char op = s[pos];
        
        if (op == '*' || op == '/') {
            pos++;
            int right = parsePower();
            
            if (hasError) return 0;
            
            if (op == '*') {
                left = left * right;
            } else {
                if (right == 0) {
                    hasError = true;
                    return 0;
                }
                left = left / right;
            }
        } else {
            break;
        }
    }
    
    return left;
}

// 解析加减运算
int parseExpression() {
    int left = parseTerm();
    
    if (hasError) return 0;
    
    while (true) {
        skipSpaces();
        
        if (pos >= strlen(s)) break;
        
        char op = s[pos];
        
        if (op == '+' || op == '-') {
            pos++;
            int right = parseTerm();
            
            if (hasError) return 0;
            
            if (op == '+') {
                left = left + right;
            } else {
                left = left - right;
            }
        } else if (op == ')') {
            // 遇到右括号，返回当前结果
            break;
        } else {
            // 遇到非法字符
            break;
        }
    }
    
    return left;
}

int main() {
    cin >> s;
    
    pos = 0;
    hasError = false;
    
    int result = parseExpression();
    
    // 检查是否有多余的右括号
    skipSpaces();
    while (pos < strlen(s) && s[pos] == ')') {
        pos++; // 忽略多余的右括号
        skipSpaces();
    }
    
    // 检查是否还有未处理的字符
    if (pos < strlen(s) && s[pos] != '\0') {
        hasError = true;
    }
    
    if (hasError) {
        cout << -1 << endl;
    } else {
        cout << result << endl;
    }
    
    return 0;
}
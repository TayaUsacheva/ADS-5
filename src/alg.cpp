// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int getPrior(char ch) {
    switch (ch) {
    case '(':
        return 0;
    case ')':
        return 1;
    case '+':
        return 2;
    case '-':
        return 2;
    case '*':
        return 3;
    case '/':
        return 3;
    default:
        return -1;
    }
}
std::string infx2pstfx(std::string infx) {
    std::string pstfx;
    int i = 0;
    char x = infx[i];
    char temp = 0;
    TStack <char, 100> stChar;
    while (x) {
        int pr = getPrior(x);
        if (pr > -1) {
            if ((pr == 0 || pr > getPrior(temp) 
                 || stChar.isEmpty()) && x != ')') {
                if (stChar.isEmpty())
                    temp = x;
                stChar.push(x);
            } else if (x == ')') {
                while (stChar.get() != '(') {
                    pstfx.push_back(stChar.get());
                    pstfx.push_back(' ');
                    stChar.pop();
                }
                stChar.pop();
                if (stChar.isEmpty())
                    temp = 0;
                } else {
                    while (!stChar.isEmpty() && getPrior(stChar.get()) >= pr) {
                        pstfx.push_back(stChar.get());
                        pstfx.push_back(' ');
                        stChar.pop();
                    }
                    if (stChar.isEmpty())
                        temp = x;
                    stChar.push(x);
                }
        } else {
            pstfx.push_back(x);
            pstfx.push_back(' ');
        }
        x = infx[++i];
}
while (!stChar.isEmpty()) {
    pstfx.push_back(stChar.get());
    pstfx.push_back(' ');
    stChar.pop();
}
    pstfx.erase(pstfx.end() - 1, pstfx.end());
    return pstfx;
}
int count1(const int& n1, const int& n2, const int& oper) {
    switch (oper) {
    default:
        break;
    case '+': return n1 + n2;
    case '-': return n1 - n2;
    case '*': return n1 * n2;
    case '/': return n1 / n2;
    }
return 0;
}

int eval(std::string prf) {
    TStack <int, 100> stInt;
    std::string num = "";
    for (int i = 0; i < prf.size(); i++) {
        if (getPrior(prf[i]) == -1) {
            if (prf[i] == ' ') {
                continue;
            } else if (isdigit(prf[i + 1])) {
                num += prf[i];
                continue;
            } else {
                num += prf[i];
                stInt.push(atoi(num.c_str()));
                num = "";
            }
        } else {
          int b = stInt.get();
          stInt.pop();
          int a = stInt.get();
          stInt.pop();
          stInt.push(count1(a, b, prf[i]));
        }
  }
  return stInt.get();
}

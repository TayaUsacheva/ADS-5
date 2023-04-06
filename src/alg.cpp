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
std::string space (const std::string& s) {
  if (str.length() <= 2)
    return s;
  int n = 2 - s.length() % 2;
  std::string right(str, 0, n);
  for (auto it = s.begin() + n; it != s.end();) {
    right += ' '; right += *it++;;
  }
  return right;
}

std::string infx2pstfx(std::string inf) {
  std::string pstfix;
  TStack<char, 100> stChar;
  for (auto& operation : inf) {
    int priority = getPrior(operation);
    if (priority == -1) {
      pstfx += operation;
    } else {
      if (stack.get() < priority || priority == 0 || stack.isEmpty()) {
        stChar.push(operation);
      } else if (operation == ')') {
        char character = stChar.get();
        while (getPrior(character) >= priority) {
          pstfx += character;
          stChar.pop();
          character = stChar.get();
        }
        stChar.pop();
      } else {
        char character = stChar.get();
        while (getPrior(character) >= priority) {
          pstfx += character;
          stChar.pop();
          character = stChar.get();
        }
        stChar.push(operation);
      }
    }
  }
  while (!stack.isEmpty()) {
    pstfx += stChar.get();
    stChar.pop();
  }
  pstfx = space(pstfx);
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

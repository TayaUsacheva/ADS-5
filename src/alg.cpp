// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int getPrior(char ch) {
    std::pair<char, int> prior[6];
    switch (ch) {
    case '(':
        prior[0].first = '(';
        prior[0].second = 0;
    case ')':
        prior[1].first = ')';
        prior[1].second = 1;
    case '+':
        prior[2].first = '+';
        prior[2].second = 2;
    case '-':
        prior[3].first = '-';
        prior[3].second = 2;
    case '*':
        prior[4].first = '*';
        prior[4].second = 3;
    case '/':
        prior[5].first = '/';
        prior[5].second = 3;
    default:
        return -1;
    }
    int pr = -1;
    for (int i = 0; i < 6; ++i) {
        if (ch == prior[i].first){
            pr = prior[i].second;
            break;
        }
    }
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

std::string space(const std::string& s) {
  if (s.length() <= 2)
    return s;
  int n = 2 - s.length() % 2;
  std::string right(s, 0, n);
  for (auto it = s.begin() + n; it != s.end();) {
    right += ' '; right += *it++;;
  }
  return right;
}

std::string infx2pstfx(std::string inf) {
  std::string pstfx;
  TStack<char, 100> stChar;
  for (auto& operation : inf) {
    int priority = getPrior(operation);
    if (priority == -1) {
      pstfx += operation;
    } else {
      if (stChar.get() < priority || priority == 0 || stChar.isEmpty()) {
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
  while (!stChar.isEmpty()) {
    pstfx += stChar.get();
    stChar.pop();
  }
  pstfx = space(pstfx);
  return pstfx;
}

int eval(std::string prf) {
    TStack <int, 100> stInt;
    std::string rez = "";
    for (int i = 0; i < prf.size(); i++) {
        if (getPrior(prf[i]) == -1) {
            if (prf[i] == ' ') {
                continue;
            } else if (isdigit(prf[i + 1])) {
                rez += prf[i];
                continue;
            } else {
                rez += prf[i];
                stInt.push(atoi(rez.c_str()));
                rez = "";
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

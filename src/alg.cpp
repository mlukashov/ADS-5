// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int Prior(char d) {
    switch (d) {
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
    }
    return -1;
}
std::string infx2pstfx(std::string inf) {
 TStack<char, 100> st1;
    std::string str = "";
    int res = 0;
    for (char a : inf) {
        bool truefalse = true;
        if (Prior(a) == 0) {
            st1.push(a);
            truefalse = false;
        }
        if (Prior(a) == -1) {
            str = str + a;
            str = str + ' ';
            truefalse = false;
        }
        if (Prior(a) > Prior(st1.get())) {
            st1.push(a);
            truefalse = false;
        }
        if (st1.isEmpty() && Prior(a) != -1) {
            st1.push(a);
            truefalse = false;
        }
        if (a != ')' && truefalse) {
            while (Prior(st1.get()) >= Prior(a)) {
                str = str + st1.pop();
                str = str + ' ';
            }
            st1.push(a);
        }
        if (a == ')') {
            while (st1.get() != '(') {
                str = str + st1.pop();
                str = str + ' ';
            }
            st1.pop();
        }
        if (res == inf.size() - 1) {
            while (!st1.isEmpty()) {
                str = str + st1.pop();
                if (st1.pri() != -1) {
                    str = str + ' ';
                }
            }
        }
        ++res;
    }
    return str;
}

int eval(std::string post) {
        TStack<int, 100> st2;
        for (char s : post) {
            if (s == '+') {
                int a = st2.pop();
                a = a + st2.pop();
                st2.push(a);
            }
            if (s == '-') {
                int a = st2.pop();
                a = st2.pop() - a;
                st2.push(a);
            }
            if (s == '*') {
                int a = st2.pop();
                a = a * st2.pop();
                st2.push(a);
            }
            if (s == '/') {
                int a = st2.pop();
                a = st2.pop() / a;
                st2.push(a);
            }
            if (s == ' ') {
                continue;
            }
            if ((s - '0') > 0) {
                int a = s - '0';
                st2.push(a);
            }
        }
        return st2.get();
}

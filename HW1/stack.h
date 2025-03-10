//
// Created by Ege Tan on 21.10.2024.
//
#ifndef HW1_STACK_H
#define HW1_STACK_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

template <class type>
class stack
{
private:
    vector<type> mystack;
    int pointer;
    int size;
public:
    stack(int maxSize = 14);
    bool empty();
    bool isfull();
    void push(type elem);
    void pop();
    type top();
    void print();
};

#include "stack.cpp"
#endif //HW1_STACK_H

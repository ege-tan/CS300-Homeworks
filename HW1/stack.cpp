//
// Created by Ege Tan on 21.10.2024.
//
#include "stack.h"

template<class type>
stack<type>::stack(int maxSize) :size(maxSize), pointer(-1) {
    mystack.resize(size);
}

template<class type>
bool stack<type>::empty() {
    return pointer == -1;
}

template<class type>
bool stack<type>::isfull() {
    return pointer == size - 1;
}

template<class type>
void stack<type>::push(type elem) {
    if (isfull() == false) {
        pointer++;
        mystack[pointer] = elem;
    }
}

template<class type>
void stack<type>::pop() {
    if (empty()==false) {
        mystack[pointer] = {};
        pointer--;
    }
}

template<class type>
type stack<type>::top() {
    if (empty() == false) {
        return mystack[pointer];
    }
    throw out_of_range("Stack is empty");
}

template<class type>
void stack<type>::print() {
    for (int i = 0; i <= pointer; i++) {
        cout << mystack[i] << " ";
    }
    cout << endl;
}

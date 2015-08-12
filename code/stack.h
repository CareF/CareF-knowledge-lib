//Annotation in UTF-8
#ifndef _STACK_
#define _STACK_
#include "lkdnode.h"
//使用链表实现一个栈
template<typename T>
class Stack{
private:
    Lkdnode<T>* topp;
    unsigned int count;
public:
    Stack();
    ~Stack();
    T pop();
    void push(T data);
    T top();
    unsigned int size();
    bool isempty();
};

template <typename T>
Stack<T>::Stack(): count(0){
    topp = new Lkdnode<T>(0);
    //建一个空的结点作为栈底
}

template <typename T>
Stack<T>::~Stack(){
    while(! this->isempty()){
        this->pop();
    }
}

template <typename T>
T Stack<T>::pop(){
    T rtdata;
    rtdata = topp->data;
    topp = topp->prev;
    delete topp->next;
    count--;
    return rtdata;
}

template <typename T>
void Stack<T>::push(T data){
    topp->next = new Lkdnode<T>(data, topp);
    topp = topp->next;
    count++;
}

template <typename T>
T Stack<T>::top(){
    return topp->data;
}

template <typename T>
unsigned int Stack<T>::size(){
    return count;
}

template <typename T>
bool Stack<T>::isempty(){
    return count == 0;
}
#endif

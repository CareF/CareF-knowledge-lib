#ifndef _LKDNODE_
#define _LKDNODE_
//实现链表结点
#include <cstring> 
template <typename T>
struct Lkdnode{
    T data;
    Lkdnode<T>* prev;
    Lkdnode<T>* next;
    Lkdnode(T dat, Lkdnode<T>* pre = NULL, 
        Lkdnode<T>* nex = NULL)://
        data(dat),prev(pre),next(nex){};
};
#endif

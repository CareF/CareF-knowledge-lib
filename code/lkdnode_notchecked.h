#ifndef _LKDNODE_
#define _LKDNODE_
//实现链表结点
#include <cstring> 
template <typename T>
struct LkdNode{
    T data;
    LkdNode<T>* prev;
    LkdNode<T>* next;
    LkdNode(T const& dat, LkdNode<T>* pre = NULL, 
        LkdNode<T>* nex = NULL)://
        data(dat),prev(pre),next(nex){};
    void destroylater(){
        LkdNode* pres = this->next;
        while(pres != NULL){
            LkdNode* tmp = pres->next;
            delete pres;
            pres = tmp;
        }
        next = NULL;
    };
    void insert(T const& dat){
        next = new LkdNode(dat, this, next);
    };
};

template <typename T>
void addNode((LkdNode<T>*)& nodepos, LkdNode<T>* newnode){
    if(nodepos == NULL){
        nodepos = newnode;
    }
    else{
        nodepos->next->prev = newnode;
        newnode->next = nodepos->next;
        nodepos = newnode;
    }
}

template <typename T>
void destroy((LkdNode<T>*)& nodepos){
    while(nodepos != NULL){
        nodepos = nodepos->next;
        delete node->prev;
    }
}
#endif

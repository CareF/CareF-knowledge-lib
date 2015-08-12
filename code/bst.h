//Annotation in UTF-8
#ifndef _BST_
#define _BST_
#include "binnode.h"
#include "stack.h"
#include <cstddef>
template <typename T>
static inline void swap(T& a, T& b){
    T tmp = a;
    a = b;
    b = tmp;
    return;
}

template <typename T>
class BST{
public:
    BST():_root(NULL),_hot(NULL){};
    BST(const T& rootd);
    BST(const BST& bst);//深拷贝
    ~BST();

    int size() const {return _root == NULL? 0 : _root->size;};

    BinNode<T>* & search(const T& d);
    BinNode<T>* & insert(const T& d);
    bool remove(const T& d);
    void removeRk(size_t rank);

    //寻秩操作, 假定树是从小到大排列的数组
    T operator[](size_t rank); 

protected:
    BinNode<T>* _hot;
    BinNode<T>* & searchIn(BinNode<T>* & v, const T& d);
    BinNode<T>* & getNo(size_t rank);
    
    //返回值指向实际被删除节点的接替者，
    //hot指向实际被删除节点的父亲——二者均有可能是NULL
    BinNode<T>* removeAt(BinNode<T>* & v);

    BinNode<T>* _root;
};

template <typename T>
BST<T>::BST(const T& rootd):_hot(NULL){
    _root = new BinNode<T>(rootd);
}
template <typename T>
BST<T>::BST(const BST& bst):_hot(bst._hot){
    //深拷贝
    Stack<BinNode<T>* > tmps;
    _root = new BinNode<T> (*bst._root);
    tmps.push(_root);
    while(!tmps.isempty()){
        BinNode<T>* node = tmps.pop();
        if(node->lc != NULL)
            tmps.push(node->lc = new BinNode<T>(*node->lc));
        if(node->rc != NULL)
            tmps.push(node->rc = new BinNode<T>(*node->rc));
    }
    return;
}
template <typename T>
BST<T>::~BST(){
	if(_root == NULL)
	   return;
    Stack<BinNode<T>* > tmps;
    tmps.push(_root);
    while(!tmps.isempty()){
        BinNode<T>* node = tmps.pop();
        if(node->lc != NULL)
            tmps.push(node->lc);
        if(node->rc != NULL)
            tmps.push(node->rc);
        delete node;
    }
    return;
}

template <typename T>
BinNode<T>* & BST<T>::search(const T& d){
    //返回值指向命中节点, 或假想的通配哨兵
    //_hot指向其父亲, 退化时为初始值NULL
    _hot = NULL;
    return searchIn(_root, d);
}
template <typename T>
BinNode<T>* & BST<T>::searchIn(BinNode<T>* & v, const T& d){
    if(v == NULL || v->data == d)
        return v;
    _hot = v;
    while(true){
        BinNode<T>* & c = (d < _hot->data)? _hot->lc : _hot->rc;
        if(c == NULL || c->data == d)
            return c;
        _hot = c;
    }
}

template <typename T>
BinNode<T>* & BST<T>::insert(const T& d){
    //无论e是否存在于原树中, 返回时总有x->data == e
    //不允许重复元素
    BinNode<T>* & x = search(d);
    if(x == NULL){
        x = new BinNode<T>(d, _hot);
        for(BinNode<T>* p = _hot; p != NULL; p = p->pr)
            p->size++;
    }
    return x;
}

template <typename T>
bool BST<T>::remove(const T& d){
    //返回值指示删除成功与否
    BinNode<T>* & x = search(d);
    if(x == NULL)
        return false;
    removeAt(x);
    for(BinNode<T>* p = _hot; p!= NULL; p = p->pr)
        p->size--;
    return true;
}
template <typename T>
void BST<T>::removeRk(size_t rank){
    BinNode<T>* & x = getNo(rank);
    removeAt(x);
    for(BinNode<T>* p = _hot; p!= NULL; p = p->pr)
        p->size--;
    return;
}
template <typename T>
BinNode<T>* BST<T>::removeAt(BinNode<T>* & v){
    BinNode<T>* w = v;
    BinNode<T>* succ = NULL;
    if(v->lc == NULL)
        succ = v = v->rc;
    else if(v->rc == NULL)
        succ = v = v->lc;
    else{
        //寻找 w 的直接后继
        w = w->rc;
        while(w->lc != NULL)
            w = w->lc;
        swap(v->data, w->data);
        (w->pr == v? w->pr->rc : w->pr->lc) //
            = succ = w->rc;
    }
    _hot = w->pr;
    if(succ != NULL)
        succ->pr = _hot;
    delete w;
    return succ;
}
template <typename T>
BinNode<T>* & BST<T>::getNo(size_t rank){
    //实现寻秩操作
    if( rank<0 || rank >= size())
        return _root;
    BinNode<T>* pos=_root;
    while(rank >= 0){
        if(pos->lc != NULL){
            if(rank == pos->lc->size)
                break;
            else if(rank > pos->lc->size){
                rank -= pos->lc->size+1;
                pos = pos->rc;
            }
            else
                pos = pos->lc;
        }
        else if(rank == 0)
            break;
        else{
            rank--;
            pos = pos->rc;
        }
    }
    if(pos == _root)
        return _root;
    return (pos == pos->pr->lc ? pos->pr->lc : pos->pr->rc);
}
template <typename T>
T BST<T>::operator[](size_t rank){
    //重载 [] 操作符方便调用
    return getNo(rank)->data;
}
#endif

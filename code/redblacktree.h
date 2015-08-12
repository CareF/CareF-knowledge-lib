//Annotation in UTF-8
#ifndef _RBT_
#define _RBT_
#include "bst.h"
#define IsBlack(p) ( (p) == NULL || (p)->color == RB_BLACK )
template <typename T>
class RedBlack: public BST<T>{
public:
    RedBlack(){};
    RedBlack(const T& rootd):BST<T>(rootd){};
    RedBlack(const RedBlack& rbt):BST<T>(rbt){};
    ~RedBlack(){};

    BinNode<T>*  insert(const T& e);
    bool remove(const T& e);
    void removeRk(size_t rank);

protected:
    int updateHeight(BinNode<T>* x);
    void getPr(BinNode<T>* to, BinNode<T>* from);//to 取得 from 的 pr 关系
    BinNode<T>* connect12(BinNode<T>* lc, BinNode<T>* pr, BinNode<T>* rc);
    BinNode<T>* connect34(BinNode<T>* lc, BinNode<T>* pr, BinNode<T>* rc, //
        BinNode<T>* t0, BinNode<T>* t1, BinNode<T>* t2, BinNode<T>* t3);
    //旋转子树, 返回调整后的局部子树根节点, 向上寻三代重新调整
    BinNode<T>* rotateAt(BinNode<T>* v);

    void removing(BinNode<T>* & x);
    void solveDoubleR(BinNode<T>* x);
    void solveDoubleB(BinNode<T>* x);
};
template <typename T>
int RedBlack<T>::updateHeight(BinNode<T>* x){
    x->height = stature(x->lc) > stature(x->rc) ? stature(x->lc) : stature(x->rc);
    if(x->color == RB_BLACK)
        x->height++;
    return x->height;
}

template <typename T>
void RedBlack<T>::getPr(BinNode<T>* to, BinNode<T>* from){
    to->pr = from->pr;
    if(from->pr != NULL)
        (from == from->pr->lc ? from->pr->lc : from->pr->rc) = to;
    else
        this->_root = to;
    return;
}
template <typename T>
BinNode<T>* RedBlack<T>::connect12(BinNode<T>* lc, BinNode<T>* pr, BinNode<T>* rc){
    pr->size = 1;
    pr->lc = lc;
    if(lc != NULL){
        lc->pr = pr;
        pr->size += lc->size;
    }
    pr->rc = rc;
    if(rc != NULL){
        rc->pr = pr;
        pr->size += rc->size;
    }
    updateHeight(pr);
    return pr;
}
template <typename T>
BinNode<T>* RedBlack<T>::connect34(BinNode<T>* lc, BinNode<T>* pr, BinNode<T>* rc, //
        BinNode<T>* t0, BinNode<T>* t1, BinNode<T>* t2, BinNode<T>* t3){
    connect12(t0,lc,t1);
    connect12(t2,rc,t3);
    connect12(lc,pr,rc);
    return pr;
}
template <typename T>
BinNode<T>* RedBlack<T>::rotateAt(BinNode<T>* v){
    BinNode<T>* p = v->pr;
    BinNode<T>* g = p->pr;
    if(p == g->lc){
        if(v == p->lc){
            getPr(p,g);
            return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        }
        else{
            getPr(v,g);
            return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    }
    else{
        if(v == p->rc){
            getPr(p,g);
            return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
        }
        else{
            getPr(v,g);
            return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
        }
    }
}

template <typename T>
BinNode<T>* RedBlack<T>::insert(const T& e){
    //无论e是否存在于原树中, 返回时总有x->data == e
    //不允许重复元素
    BinNode<T>* &x = this->search(e);
    if(x != NULL) //已经存在元素, 不操作
        return x;

    x = new BinNode<T>(e,this->_hot);
    //更新子树大小
    for(BinNode<T>* p = x->pr; p != NULL; p = p->pr)
        p->size++;
    solveDoubleR(x);
    return x;
}
template <typename T>
void RedBlack<T>::solveDoubleR(BinNode<T>* x){
    if(x->pr == NULL){
        x->color = RB_BLACK;
        x->height++;
        return;
    }
    BinNode<T>* p = x->pr;//x的父节点, 非空
    if(p->color == RB_BLACK){
        //颜色已经正确
        return;
    }

    BinNode<T>* g = p->pr;//p的父节点必非空, 黑
    BinNode<T>* u = (p == g->lc)? g->rc : g->lc;//叔叔节点

    if(u == NULL || u->color == RB_BLACK){//u 是黑色的, 
        //x p g 在同一个B树节点, g 转红, 
        if((x == p->lc) == (p == g->lc)) //x, p同侧
            p->color = RB_BLACK;
        else //x, p异侧
            x->color = RB_BLACK;
        g->color = RB_RED;
        rotateAt(x);//rotate 过程一并解决的 height
    }
    else{ //u 是红色的
        u->color = RB_BLACK;
        u->height++;
        p->color = RB_BLACK;
        p->height++;
        if(g->pr != NULL)
            g->color = RB_RED;
        solveDoubleR(g);
    }
}

template <typename T>
bool RedBlack<T>::remove(const T& e){
    BinNode<T>* & x = this->search(e);
    if(x == NULL)
        return false;
    removing(x);
    return true;
}
template <typename T>
void RedBlack<T>::removeRk(size_t rank){
    removing(this->getNo(rank));
    return;
}
template <typename T>
void RedBlack<T>::removing(BinNode<T>* & x){
    BinNode<T>* r = this->removeAt(x);
    if(this->_root == NULL)
        return;
    if(this->_hot == NULL){//删除的是根节点
        this->_root->color = RB_BLACK;
        updateHeight(this->_root);
        return;
    }

    for(BinNode<T>* p = this->_hot; p!= NULL; p = p->pr)
        p->size--;
    if(stature(this->_hot->lc) == stature(this->_hot->rc) && //
        this->_hot->height == (this->_hot->color == RB_BLACK ? //
                    stature(this->_hot->lc)+1 : stature(this->_hot->lc)))
        //已经满足红黑树平衡要求
        return;
    if(r != NULL && r->color == RB_RED){\
        //替代结点为红, 只需要翻转颜色即可
        r->color = RB_BLACK;
        r->height++;
        return;
    }
    solveDoubleB(r);
    return;
}
template <typename T>
void RedBlack<T>::solveDoubleB(BinNode<T>* x){
    BinNode<T>* p = x == NULL? this->_hot : x->pr;
    if(p == NULL)
        return;

    BinNode<T>* s = (x==p->lc) ? p->rc : p->lc;//x的兄弟
    if(s == NULL || s->color == RB_BLACK){
        //兄弟 s 为黑
        BinNode<T>* t = NULL; //找 s 的红孩子
        if(s->lc != NULL && s->lc->color == RB_RED)
            t = s->lc;
        else if(s->rc != NULL && s->rc->color == RB_RED)
            t = s->rc;
        if(t != NULL){
            //s 有红孩子
            RBColor pOldColor = p->color;
            BinNode<T>* b = rotateAt(t);
            if(b->lc != NULL){
                b->lc->color = RB_BLACK;
                updateHeight(b->lc);
            }
            if(b->rc != NULL){
                b->rc->color = RB_BLACK;
                updateHeight(b->rc);
            }
            b->color = pOldColor;
            updateHeight(b);
        }
        else{
            //s 没有红孩子
            s->color = RB_RED;
            s->height--;
            if(p->color == RB_RED)
                p->color = RB_BLACK;
            else{
                p->height--;
                solveDoubleB(p);
            }
        }
    }
    else{
        //兄弟 s 为红, 则其孩子均为黑
        s->color = RB_BLACK;
        p->color = RB_RED;
        this->_hot = p;
        rotateAt(s == s->pr->lc ? s->lc : s->rc);
        solveDoubleB(x);
    }
}
#endif

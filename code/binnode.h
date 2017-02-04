//Annotation in UTF-8
#ifndef _BINNODE_
#define _BINNODE_
#include <cstddef>
#define stature(p) ((p)!=NULL ? (p)->height : -1)
typedef enum { RB_RED, RB_BLACK} RBColor;

template <typename T>
struct BinNode{
    T data;
    BinNode<T>* pr;
    BinNode<T>* lc;
    BinNode<T>* rc;
    int size;
    RBColor color;
    int height;

    BinNode(T da, BinNode<T>* p = NULL,//
        BinNode<T>* l = NULL, BinNode<T>* r = NULL,//
        int h = -1, RBColor c = RB_RED):
        data(da),lc(l),rc(r),pr(p),height(h),color(c){
            size = 1 + (l==NULL? 0: l->size) + (r==NULL? 0:r->size);
        };
};

#endif
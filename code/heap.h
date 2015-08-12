//Annotation in UTF-8
#ifndef _HEAP_
#define _HEAP_
/*
 *实现了一个堆
 *参考了邓老师的代码
 */
 #include "vector.h"
template <typename T>
static inline void swap(T& a, T& b){
    T tmp = a;
    a = b;
    b = tmp;
    return;
}

static inline Rank pr(Rank i){return (i - 1) >> 1;}
static inline Rank lc(Rank i){return (i << 1) + 1;}
static inline Rank rc(Rank i){return (i + 1) << 1;}

template <typename T, typename CMP>
class heap{
public:
    heap(Rank n, T const* data):elem(n,data){
        for(Rank i = pr(n-1); i>=0; i--)
            percolateDown(n, i);
    };
    heap(Rank n, T const* data, CMP c):elem(n,data),_cmp(c){
        for(Rank i = pr(n-1); i>=0; i--)
            percolateDown(n, i);
    };
    ~heap();

    T top(){
        return elem[0];
    };
    T pop(){
        T maxelem = elem[0];
        elem[0] = remove(elem.size()-1);
        percolateDown(elem.size(), 0);
        return maxelem;
    };
    void push(T const& d){
        elem.insert(d);
        percolateUp(elem.size());
    };
    void exctop(T const& d){
        elem[0] = d;
        percolateDown(elem.size(), 0);
    };

protected:
    inline Rank propPr(Rank max, Rank i, T elemi){
        if(rc(i) < max){
            if(elemi < elem[lc(i)])
                return elem[lc(i)] < elem[rc(i)]?  rc(i) : lc(i);
            else
                return elemi < elem[rc(i)]? rc(i) : i;
        }
        else if(lc(i) < max){
            return elemi < elem[lc(i)]? lc(i) : i;
        }
        else
            return i;
    }
    inline Rank percolateDown(Rank max, Rank i){
        Rank j;
        T tmp = elem[i];
        while(i != (j = propPr(max, i, tmp)) ){
            elem[i] = elem[j];
            i = j;
        }
        elem[i] = tmp;
        return i;
    };
    inline Rank percolateUp(Rank i){
        T tmp = elem[i];
        while(0 < i){
            Rank j = pr(i);
            if(cmp(tmp, elem[j]))
                break;
            elem[i] = elem[j];
            i = j;
        }
        elem[i] = tmp;
        return i;
    };
private:
    Vector<T> elem;
    CMP _cmp;
};


//重载默认从小到大排序
template <typename T>
struct less{
    virtual bool operator()(T const& a, T const& b)const{
        return a<b;
    };
};
#endif

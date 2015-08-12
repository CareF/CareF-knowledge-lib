//Annotation in UTF-8
#ifndef _HEAPSORT_
#define _HEAPSORT_
/*
 *实现了一个堆排序
 *参考了邓老师的代码
 */
template <typename T>
static inline void swap(T& a, T& b){
    T tmp = a;
    a = b;
    b = tmp;
    return;
}

typedef int Rank;
static inline Rank pr(Rank i){return (i - 1) >> 1;}
static inline Rank lc(Rank i){return (i << 1) + 1;}
static inline Rank rc(Rank i){return (i + 1) << 1;}

template <typename T, typename CMP>
static inline Rank propPr(T elem[], Rank max, Rank i, CMP const& cmp){
    if(rc(i) < max){
        if(cmp(elem[i], elem[lc(i)]))
            return cmp(elem[lc(i)], elem[rc(i)])?  rc(i) : lc(i);
        else
            return cmp(elem[i], elem[rc(i)])? rc(i) : i;
    }
    else if(lc(i) < max){
        return cmp(elem[i], elem[lc(i)])? lc(i) : i;
    }
    else
        return i;
}

template <typename T, typename CMP>
static inline Rank percolateDown(T elem[], Rank max, Rank i, CMP const& cmp){
    Rank j;
    while(i != (j = propPr(elem, max, i, cmp)) ){
        swap(elem[i],elem[j]);
        i = j;
    }
    return i;
}

template <typename T, typename CMP>
void heapsort(T elem[], Rank max, CMP const& cmp){
    for(Rank i = pr(max-1); i>=0; i--)
        percolateDown(elem, max, i, cmp);
    while(--max > 0){
        swap(elem[0],elem[max]);
        percolateDown(elem,max,0,cmp);
    }
    return;
}

//重载默认从小到大排序
template <typename T>
struct less{
    virtual bool operator()(T const& a, T const& b)const{
        return a<b;
    };
};

template <typename T>
void heapsort(T elem[], Rank max){
    heapsort(elem, max, less<T>() );
    return;
}
#endif

#ifndef _VECTOR_
#define _VECTOR_
/*实现可扩充的vector模版类
 *Author: 吕铭 Ming Lyu
 *Creation Date: 2014/12/11
 *
 *参考了邓老师课件中的代码
*/
#include <cstddef>
#include <cstdio>
#define INICAP 4
typedef int Rank;

template <typename T>
inline T& max(T& a, T& b){
    return a>b? a:b;
}
template <typename T>
inline T& min(T& a, T& b){
    return a<b? a:b;
}

template <typename T>
class Vector{
public:
    Vector(Rank cap = INICAP){
        _data = new T[_cap = cap];
        _count = 0;
    };
    Vector(Rank cap, T const* inid){
    	_data = new T[_cap = cap];
    	for(Rank i=0; i<cap; i++)
    		_data[i] = inid[i];
    	_count = cap;
    };
    Vector(T const* in, Rank lo, Rank hi){
        copyFrom(in, lo, hi);
    };
    Vector(Vector<T> const& V){
        copyFrom(V._data, 0, V.size);
    }
    Vector(Vector<T> const& V, Rank lo, Rank hi){
        copyFrom(V._data, lo, hi);
    };
    ~Vector(){
        delete[] _data;
    };

    T& operator[](Rank r) const{
        return _data[r];
    };

    long long int size() const {return _count;};
    bool empty() const {return _count==0;};
    /* 
    virtual Rank search(T const& e, Rank lo, Rank hi) const{
        //搜索, 用于有序向量
        //使用二分查找, 返回大于它的最小元素的秩
        while(lo < hi){
            Rank mi = (lo + hi)/2;
            (e < _data[mi])? hi=mi : lo=mi+1;
        }
        return lo;
    };
    virtual Rank search(T const& e) const{
        return search(e, 0, _count);
    };

    virtual Rank find(T const& e, Rank lo, Rank hi) const{
        //查找, 用于无序向量
        //多个匹配时返回秩最大的, 无匹配时返回-1
        for(Rank i = hi-1; i >= lo; i--)
            if(e == _data[i])
                return i;
        return -1;
    };
    virtual Rank find(T const& e) const{
        return find(e, 0, _count);
    }
    */ 

    Rank insert(Rank r, T const& e){
        //插入元素, 使得插入的元素秩为r
        expand();
        for(Rank i=_count; i>r; i--)
            _data[i] = _data[i-1];
        _data[r] = e;
        _count++;
        return r;
    };
    Rank insert(T const& e){
        expand();
        _data[_count++] = e;
        return _count-1;
    }
    int remove(Rank lo, Rank hi){
        //删除[lo,hi)之间的元素
        if(lo >= hi) return 0;
        while(hi < _count)
            _data[lo++] = _data[hi++];
        _count = lo;
        shrink();
        return hi-lo;
    };
    T remove(Rank r){
        //删除秩r的元素
        T e = _data[r];
        remove(r,r+1);
        return e;
    };

    //virtual void sort(){};
/* 
    virtual int uniquify(){
        //剔除重复元素, 返回剔除元素个数
        //用于有序向量
        Rank i=0, j=0;
        while(++j < _count)
            if(_data[i] != _data[j])
                _data[++i] = _data[j];
        _count = ++i;
        shrink();
        return j-i;
    }*/ 

protected:
    void copyFrom(T const* in, Rank lo, Rank hi){
        _data = new T[_cap = 2*(hi-lo)];
        _count = 0;
        while(lo < hi)
            _data[_count++] = in[lo++];
    };
    void expand(){
        if(_count < _cap)
            return;
        _cap = _cap>INICAP?_cap:INICAP;
        T* oldData = _data;
        _data = new T[_cap *= 2];
        for(Rank i=0; i<_count; i++)
            _data[i] = oldData[i];
        delete[] oldData;
    }
    void shrink(){
        if(_cap < INICAP*2)
            return;
        if(_count*4 > _cap)
            return;
        T* oldData = _data;
        _data = new T[_cap *= 2];
        for(Rank i=0; i<_count; i++)
            _data[i] = oldData[i];
        delete[] oldData;
    };

private:
    T* _data;
    long long int _count;
    long long int _cap;
};
#endif

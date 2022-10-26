#include <stdlib.h>
#define DEFAULT_CAPACITY 50

template <typename Obj> class Vector
{
private:
    Obj* _elem;
    int _size, _capacity; 
protected:
    void swap(Obj& A, Obj& B);
    void copyFrom ( const Obj* A, int lo, int hi ); //复制数组区间A[lo, hi)
    void expand(); //拓展空间
    void shrink();//缩小空间
    bool bubble( int lo, int hi ); //扫描交换
    void bubbleSort ( int lo, int hi ){while( !bubble(lo, hi) );}
    int maxItem ( int lo, int hi ); //选取最大元素
    void selectionSort ( int lo, int hi ); //选择排序算法
    void merge ( int lo, int mi, int hi ); //归并算法
    void mergeSort( int lo, int hi); //归并排序
    void heapSort ( int lo, int hi ); //堆排序（稍后结合完全堆讲解）
    void quickSort( int lo, int hi); //快排序
    void shellSort( int lo, int hi); //希尔排序
    int partition(  int lo, int hi); //轴点构造算法
public:
    Vector ( int c = DEFAULT_CAPACITY, int s = 0, Obj v = 0 ) //容量为c、规模为s、所有元素初始为v
    { _elem = new Obj[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); } //s<=c
    Vector ( Obj const* A, int n ) { copyFrom ( A, 0, n ); } //数组整体复制
    Vector ( Obj const* A, int lo, int hi ) { copyFrom ( A, lo, hi ); } //区间
    Vector ( Vector<Obj> const& V ) {  copyFrom (V._elem, 0, V._size ); } //向量整体复制
    Vector ( Vector<Obj> const& V, int lo, int hi ) { copyFrom ( V._elem, lo, hi ); } //区间
 // 析构函数
    ~Vector() { delete [] _elem; } //释放内部空间
 // 只读访问接口
    int size() const { return _size; } //规模
    bool empty() const { return !_size; } //判空
    int find ( Obj const& e ) const { return find ( e, 0, _size ); } //无序向量整体查找
    int find ( Obj const& e, int lo, int hi ) const; //无序向量区间查找
    int search ( Obj const& e ) const //有序向量整体查找
    { return ( 0 >= _size ) ? -1 : search ( e, 0, _size ); }
    int search ( Obj const& e, int lo, int hi ) const; //有序向量区间查找
 // 可写访问接口
    Obj& operator[] ( int r ); //重载下标操作符，可以类似于数组形式引用各元素
    const Obj& operator[] ( int r ) const; //仅限于做右值的重载版本
    Vector<Obj> & operator= ( Vector<Obj> const& ); //重载赋值操作符，以便直接克隆向量
    Obj remove ( int r ); //删除秩为r的元素
    int remove ( int lo, int hi ); //删除秩在区间[lo, hi)之内的元素
    int insert ( int r, Obj const& e ); //插入元素
    int insert ( Obj const& e ) { return insert ( _size, e ); } //默认作为末元素插入
    void sort ( int lo, int hi ); //对[lo, hi)排序
    void sort() { sort ( 0, _size ); } //整体排序
    void unsort ( int lo, int hi ); //对[lo, hi)置乱
    void unsort() { unsort ( 0, _size ); } //整体置乱
    int deduplicate(); //无序去重
    int uniquify(); //有序去重
 // 遍历
    //void traverse ( void (* ) ( Obj& ) ); //遍历（使用函数指针，只读或局部性修改）
    template <typename VST> void traverse ( VST& ); //遍历（使用函数对象，可全局性修改） 
};

template <typename Obj> void Vector<Obj>::copyFrom( const Obj* A, int lo, int hi )
{
   _elem = new Obj[_capacity=2*(hi-lo)]; _size=0;
   while (lo<hi)
      _elem[_size++]=A[lo++];
}
//重定向=
template <typename Obj> Vector<Obj>& Vector<Obj>::operator=( const Vector<Obj>& A )
{
   if(_elem) 
      delete [] _elem;
   copyFrom(A._elem, 0, A._size);
   return *this; //为了支持链式赋值
}
//重定向[]
template <typename Obj> Obj& Vector<Obj>::operator[]( int r )
{
   return _elem[r];
}
template <typename Obj> const Obj& Vector<Obj>::operator[]( int r ) const
{
   return _elem[r];
}
//动态容量管理
template <typename Obj> void Vector<Obj>::expand()
{
   if(_capacity<DEFAULT_CAPACITY)
      _capacity=DEFAULT_CAPACITY;
   if(_size<_capacity)
      return;
   Obj* oldElem = _elem;
   _elem = new Obj[_capacity<<1];
   for(int i=0; i<_size; i++)
      _elem[i]=oldElem[i];
   delete [] oldElem;
}
template <typename Obj> void Vector<Obj>::shrink()
{
   if(_capacity<DEFAULT_CAPACITY)
      return;
   if(_size<<2>_capacity)
      return;
   Obj* oldElem = _elem;
   _elem = new Obj[_capacity>>1];
   for(int i=0; i<_size; i++)
      _elem[i]=oldElem[i];
   delete [] oldElem;
}

template <typename Obj> void Vector<Obj>::swap( Obj& A, Obj& B )
{
   Obj temp=A;A=B;B=temp;
}

template <typename Obj> void Vector<Obj>::unsort( int lo, int hi ) 
{
   Obj* temp=_elem+lo;
   for(int i=hi-lo; i>0; i--){
      swap(temp[i-1], temp[rand()%i]);
   }
}

// 一般向量
template<typename Obj> int Vector<Obj>::find(const Obj& e, int lo, int hi) const
{
   while (lo<hi-- && _elem[hi]!=e);
   return hi; //如果没有找到,返回lo-1
}

template<typename Obj> int Vector<Obj>::insert ( int r, Obj const& e )
{
   expand(); //必要时扩容
   for(int i=_size; i>r;i--)
      _elem[i]=_elem[i-1];
   _elem[r]=e;
   _size++;
   return 0;
}

template<typename Obj> int Vector<Obj>::remove ( int lo, int hi )
{
   if( lo==hi ) return 0;
   while (hi<_size)
      _elem[lo++]=_elem[hi++];
   _size=lo;
   shrink(); //有必要缩容量
   return hi-lo;
}

template<typename Obj> Obj Vector<Obj>::remove( int r )
{
   Obj e=_elem[r];
   remove(r, r+1);
   return e;
}

template<typename Obj> int Vector<Obj>::deduplicate()
{
   int Oldsize=_size;
   int i=1;
   while (i<_size)
      find(_elem[i], 0, i)>=0 ? remove(i) : i++; //遍历如果元素之前出现过删除元素
   return Oldsize-_size;
}

template<typename Obj> template<typename funT> void Vector<Obj>::traverse (funT &visit)
{
   for(int i=0; i<_size; i++)
      visit(_elem[i]);
}

//有序向量
template<typename Obj> int Vector<Obj>::search ( Obj const& e, int lo, int hi ) const
{
   //改进binSearch 一次判断
   while (lo<hi)
   {
      int mid=(lo+hi)>>1; //向右移动一位
      e<_elem[mid] ? hi=mid : lo=++mid;
   }
   return --lo;
}

template<typename Obj> bool Vector<Obj>::bubble( int lo, int hi )
{
   bool sorted=true;
   while (++lo<hi)
      if(_elem[lo-1]>_elem[lo]){
         swap(_elem[lo-1], _elem[lo]);
         sorted=false;
      }
   return sorted;
}

template<typename Obj> void Vector<Obj>::mergeSort( int lo, int hi )
{
   if(hi==lo+1) return; //特殊情况
   int mid=(lo+hi)>>1;
   mergeSort(lo, mid); mergeSort(mid,hi);
   merge(lo, mid, hi);
}

template<typename Obj> void Vector<Obj>::merge( int lo, int mid, int hi )
{
   Obj* A=_elem+lo; Obj* B=new Obj[mid-lo]; Obj* C=_elem+mid;
   int i,j,k; i=j=k=0;
   int la=hi-lo, lb=mid-lo, lc=hi-mid;
   while (lo+j<mid)
      B[j++]=_elem[lo+j];
   j=0;
   //while (i<la)
   while(j<lb||k<lc)
      //(j<lb && (!k<lc || B[j]<=C[k])) ? A[i++]=B[j++] : A[i++]=C[k++];
      (j<lb && (!(k<lc) || B[j]<=C[k])) ? A[i++]=B[j++] : A[i++]=C[k++];//!的优先级很高
   delete []B;
}

template<typename Obj> void Vector<Obj>::sort(int lo, int hi)
{
   mergeSort(lo, hi);
}
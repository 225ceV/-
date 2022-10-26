#include "listNode.h" //引入列表节点类
template <typename T> class List { //列表模板类

private:
    int _size; ListNodePosiT header, trailer; //规模、头哨兵、尾哨兵

protected:
    void init(); //列表创建时的初始化
    int clear(); //清除所有节点
    void copyNodes ( ListNodePosiT, int ); //复制列表中自位置p起的n项
    ListNodePosiT merge ( ListNodePosiT, int, List<T> &, ListNodePosiT, int ); //归并
    void mergeSort ( ListNodePosiT &, int ); //对从p开始连续的n个节点归并排序
    void selectionSort ( ListNodePosiT, int ); //对从p开始连续的n个节点选择排序
    void insertionSort ( ListNodePosiT, int ); //对从p开始连续的n个节点插入排序
    void radixSort(ListNodePosiT, int); //对从p开始连续的n个节点基数排序

public:
// 构造函数
    List() { init(); } //默认
    List ( List<T> const& L ){copyNodes(L.first(), List.size());} //整体复制列表L
    List ( List<T> const& L, int r, int n ){copyNodes(L[r], n);} //复制列表L中自第r项起的n项
    List ( ListNodePosiT p, int n ){copyNodes(p, n);} //复制列表中自位置p起的n项
// 析构函数
    ~List(); //释放（包含头、尾哨兵在内的）所有节点
// 只读访问接口
    int size() const { return _size; } //规模
    bool empty() const { return _size <= 0; } //判空
    T& operator[] ( int r ) const; //重载，支持循秩访问（效率低）
    ListNodePosiT first() const { return header->succ; } //首节点位置
    ListNodePosiT last() const { return trailer->pred; } //末节点位置
    bool valid ( ListNodePosiT p ) //判断位置p是否对外合法
    { return p && ( trailer != p ) && ( header != p ); } //将头、尾节点等同于NULL
    ListNodePosiT find ( T const& e ) const //无序列表查找
    { return find ( e, _size, trailer ); }
    ListNodePosiT find ( T const& e, int n, ListNodePosiT p ) const; //无序区间查找
    ListNodePosiT search ( T const& e ) const //有序列表查找
    { return search ( e, _size, trailer ); }
    ListNodePosiT search ( T const& e, int n, ListNodePosiT p ) const; //有序区间查找
    ListNodePosiT selectMax ( ListNodePosiT p, int n ); //在p及其n-1个后继中选出最大者
    ListNodePosiT selectMax() { return selectMax ( header->succ, _size ); } //整体最大者
// 可写访问接口
    ListNodePosiT insertAsFirst ( T const& e ); //将e当作首节点插入
    ListNodePosiT insertAsLast ( T const& e ); //将e当作末节点插入
    ListNodePosiT insert ( ListNodePosiT p, T const& e ); //将e当作p的后继插入
    ListNodePosiT insert ( T const& e, ListNodePosiT p ); //将e当作p的前驱插入
    T remove ( ListNodePosiT p ); //删除合法位置p处的节点,返回被删除节点
    void merge ( List<T> & L ) { merge ( header->succ, _size, L, L.header->succ, L._size ); } //全列表归并
    void sort ( ListNodePosiT p, int n ); //列表区间排序
    void sort() { sort ( first(), _size ); } //列表整体排序
    int deduplicate(); //无序去重
    int uniquify(); //有序去重
    void reverse(); //前后倒置（习题）
// 遍历
    void traverse ( void (* ) ( T& ) ); //遍历，依次实施visit操作（函数指针，只读或局部性修改）
    template <typename VST> //操作器
    void traverse ( VST& ); //遍历，依次实施visit操作（函数对象，可全局性修改）
}; //List

template <typename T> void List<T>::init()
{
    header=new ListNode<T>; trailer=new ListNode<T>;
    header->Pred=nullptr; header->Succ=trailer;
    trailer->Pred=header; trailer->Succ=nullptr;
    _size=0;
}

template <typename T> T& List<T>::operator[](int r) const
{
    ListNodePosiT p=first();
    while (r-->0) p=p->Succ;
    return p->data;
}

template <typename T> ListNodePosiT List<T>::find(T const &e, int n, ListNodePosiT p) const
{
    while (p->data!=e && n-->0) p=p->Pred;
    if(n==0) return nullptr;
    return p;
}

template <typename T> ListNodePosiT List<T>::insertAsFirst(T const &e)
{
    _size++;
    return header->insertAsSucc(e);
}

template <typename T> ListNodePosiT List<T>::insertAsLast(T const &e)
{   _size++; return trailer->insertAsPerd(e);}

template <typename T> ListNodePosiT List<T>::insert( ListNodePosiT p, T const &e )
{   _size++; return p->insertAsSucc(e);}

template <typename T> ListNodePosiT List<T>::insert( T const &e, ListNodePosiT p )
{   _size++; return p->insertAsPred(e);}

template <typename T> void List<T>::copyNodes( ListNodePosiT p, int n ) //指向第一个元素, 至少有n-1个后继节点
{
    init();
    while (n--)
    {
        insertAsLast(p->data);
        p=p->Succ;
    }
}

template <typename T> T List<T>::remove( ListNodePosiT p )
{
    T e = p->data;
    p->Pred->Succ=p->Succ;
    p->Succ->Pred=p->Pred;
    delete p; _size--;
    return e;
}

template <typename T> int List<T>::clear()
{
    oldSize=_size;
    while (_size) remove(header->Succ);
    return oldSize;
}


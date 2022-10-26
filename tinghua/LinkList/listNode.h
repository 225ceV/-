#define ListNodePosiT ListNode<T>* 
template <typename T> struct ListNode
{
    T data; ListNodePosiT Pred; ListNodePosiT Succ;
    ListNode() {}
    ListNode(T e, ListNodePosiT p=nullptr, ListNodePosiT s=nullptr)
        :data(e), Pred(p), Succ(s){}
    
    ListNodePosiT insertAsPerd(T const &e);
    ListNodePosiT insertAsSucc(T const &e);
};

template <typename T> ListNodePosiT ListNode<T>::insertAsSucc(T const &e)
{
    p = new ListNode(e, this, Succ);
    Succ->Pred=p;
    Succ=p;
    return p;
}

template <typename T> ListNodePosiT ListNode<T>::insertAsPerd(T const &e)
{
    p=new ListNode(e, Pred, this);
    Pred->Succ=p;
    Pred=p;
    return p;
}
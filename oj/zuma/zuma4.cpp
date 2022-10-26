#include <cstdio>
struct node
{
    char data;
    node* nxt;
    node* pre;
    node() {} //用于list的初始化
    node(char color, node* pre=nullptr, node* nxt=nullptr)
        :data(color), pre(pre), nxt(nxt){}
    node* insertAsPre(char e);
};
node* node::insertAsPre(char e)
{
    node* p=new node(e, pre, this);
    pre->nxt=p;
    pre=p;
    return p;
}
class zumaList //双向链表
{
protected:
    void copy_from_arr(char* arr);
public:
    int _size; node* header; node* trailer;
    char deleteNode(node* p);
    node* insert(char e, node* p) {_size++; return p->insertAsPre(e);}
    node* insert(char e, int r);
    zumaList(char* arr);
    ~zumaList();
    void print();
};
zumaList::zumaList(char* arr)
{
    _size=0; 
    header=new node(0); trailer=new node(0);
    header->nxt=trailer; trailer->pre=header;
    copy_from_arr(arr);
}
zumaList::~zumaList()
{
    node *q, *p;
    p=header->nxt;
    while (p!=trailer)
    {
        q=p->nxt;
        deleteNode(p);
        p=q;
    }
}
void zumaList::copy_from_arr(char* arr)
{
    int i=0;
    while (arr[i]<='Z'&&arr[i]>='A'){
        insert(arr[i], trailer); //io
        i++;
    } 
}
char zumaList::deleteNode(node* p)
{
    char e=p->data;
    p->pre->nxt=p->nxt;
    p->nxt->pre=p->pre;
    delete p; _size--;
    return e;
}
node* zumaList::insert(char e, int r)
{
    node* p=header->nxt; 
    while(r--) p=p->nxt; 
    return insert(e, p);
}
void zumaList::print()
{
    node* p=header->nxt;
    if(_size==0) {printf("-\n"); return;}
    while (p!=trailer){
        printf("%c", p->data);
        p=p->nxt;
    }
    printf("\n");
}
node* epos=nullptr;
bool proc(zumaList& z)
{
    node *lo=epos, *hi=epos;
    int note=0;
    while(lo->data==epos->data && lo!=z.header) {lo=lo->pre; note++;}
    lo=lo->nxt;
    while(hi->data==epos->data && hi!=z.trailer) {hi=hi->nxt; note++;}
    if(note>3){
        lo->pre->nxt=hi;
        hi->pre=lo->pre;
        epos=hi;
        z._size=z._size-note+1;
        return true;
    }
    return false;
}
int main(int argc, char const *argv[])
{
    setvbuf(stdin,  new char[1<<20], _IOFBF, 1<<20);
    setvbuf(stdout, new char[1<<20], _IOFBF, 1<<20);
    char st[20001];
    fgets(st, 20001, stdin);
    zumaList zlst(st);

    int n; scanf("%d", &n);  //输入操作
    int* rank=new int[n]; char* cl=new char[n];
    for(int i=0; i<n; i++) {scanf("%d %c", rank+i, cl+i);}

    for(int i=0; i<n; i++){
        epos=zlst.insert(cl[i], rank[i]);
        while(proc(zlst)); //epos
        zlst.print();
    }
    return 0;
}

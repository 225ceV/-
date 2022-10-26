#include <cstdio>
//递归
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
private:
    int _size; node* header; node* trailer;
protected:
    void copy_from_arr(char* arr);
    node* pop(node* pop_posi);
    bool need_pop(node* pop_posi);
    void near_check(node* pop_posi);
public:
    char deleteNode(node* p);
    node* insert(char e, node* p) {_size++; return p->insertAsPre(e);}
    node* insert(char e, int r);
    zumaList(char* arr);
    ~zumaList();
    int process();
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
    while (arr[i]!=0) insert(arr[i++], trailer);
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

node* zumaList::pop(node* pop_posi) //返回消去后的前一个地址
{
    node* pop_pre=pop_posi->pre;
    char pop_color=pop_posi->data;
    while (pop_posi->data==pop_color){
        node* pop_next=pop_posi->nxt;
        deleteNode(pop_posi);
        pop_posi=pop_next;
    }
    return pop_pre;
}

bool zumaList::need_pop(node* pop_posi)
{
    if(pop_posi->data!=pop_posi->nxt->data) return false;
    if(pop_posi->nxt->data!=pop_posi->nxt->nxt->data) return false;
    return true;
}

void zumaList::near_check(node* pop_posi)
{
    if(_size<3) return;
    if(need_pop(pop_posi->pre)){
        near_check(pop(pop_posi->pre)); 
        return;
    }
    if(_size>3 && need_pop(pop_posi)){
        near_check(pop(pop_posi));
    }
}

int zumaList::process()
{
    int oldSize=_size;
    node* p=header->nxt;
    for(int i=0; i<_size-2; i++){
        if(need_pop(p)){
            p=pop(p);
            near_check(p);
            break;
        }
        p=p->nxt;
    }
    return oldSize-_size;
}

void zumaList::print()
{
    if(_size==0) {printf("-\n"); return;}
    node* p=header->nxt;
    while (p!=trailer){
        printf("%c", p->data);
        p=p->nxt;
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    char *st=new char[10000]; //store inital state
    scanf("%s", st);
    zumaList zlst(st);
    delete [] st;

    int n; scanf("%d", &n);  //输入操作
    int* rank=new int[n]; char* cl=new char[n];
    for(int i=0; i<n; i++) {scanf("%d %c", rank+i, cl+i);}

    for(int i=0; i<n; i++){
        zlst.insert(cl[i], rank[i]);
        zlst.process();
        zlst.print();
    }
    return 0;
}

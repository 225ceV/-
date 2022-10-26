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
private:
    int _size; node* header; node* trailer;
protected:
    void copy_from_arr(char* arr);
    node* near_check(node* pop_posi);
    node* first_check(node* pop_posi);
    node* pop(node* pop_posi);
    bool need_pop(node* pop_posi);
public:
    char deleteNode(node* p);
    node* insert(char e, node* p) {_size++; return p->insertAsPre(e);}
    node* insert(char e, int r);
    zumaList(char* arr);
    ~zumaList();
    void process(node* p);

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
    if(pop_posi==nullptr) return nullptr;
    node* pop_pre=pop_posi->pre;
    char pop_color=pop_posi->data;
    while (pop_posi->data==pop_color){
        node* pop_next=pop_posi->nxt;
        deleteNode(pop_posi);
        pop_posi=pop_next;
    }
    if (pop_pre==header) return nullptr;
    return pop_pre;
}

bool zumaList::need_pop(node* pop_posi)
{
    if(pop_posi->nxt==trailer || pop_posi->nxt->nxt==trailer) return false;
    if(pop_posi->data!=pop_posi->nxt->data) return false;
    if(pop_posi->nxt->data!=pop_posi->nxt->nxt->data) return false;
    return true;
}

node* zumaList::near_check(node* pop_posi)
{
    if(pop_posi==nullptr) return nullptr;
    if(need_pop(pop_posi->pre)) return pop_posi->pre;
    if(need_pop(pop_posi)) return pop_posi;
    return nullptr;
}

node* zumaList::first_check(node* insert_posi)
{
    if(need_pop(insert_posi)) {return insert_posi;}
    insert_posi=insert_posi->pre; if(insert_posi==header) return nullptr;
    if(need_pop(insert_posi)) {return insert_posi;}
    insert_posi=insert_posi->pre; if(insert_posi==header) return nullptr;
    if(need_pop(insert_posi)) {return insert_posi;}
    return nullptr;
}

void zumaList::process(node* p)
{
    p=first_check(p);
    p=pop(p);
    while (p!=nullptr)
    {
        p=near_check(p);
        p=pop(p);
    }
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
        node* p=zlst.insert(cl[i], rank[i]);
        zlst.process(p);
        zlst.print();
    }
    return 0;
}

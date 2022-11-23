#define MAXNUM 100001
#define Null -1
#include<cstdio>
typedef int rank;
struct LinkNode
{
    int data;
    rank nxt;
};
typedef LinkNode* List;
void readL(List& L, int n);     //List没有头节点List[MAXNUM-1]
rank reversek(List& L, rank p, int k);  //返回第k项的地址
bool can(const List& L, rank p, int k); //判断是否可以做调换
void printL(const List& L, rank head);
int main(int argc, char const *argv[])
{
    rank first, head=MAXNUM-1;
    int n, k;
    scanf("%d %d %d", &first, &n, &k);
    List ls=new LinkNode[MAXNUM];
    ls[head].nxt=first;
    readL(ls, n);
    rank p=head;
    while (can(ls, p, k))
    {
        p=reversek(ls, p, k);
    }
    printL(ls, head);
    
    return 0;
}
void readL(List& L, int n)
{
    while (n--)
    {
        int a,b,c;
        scanf("%d %d %d\n", &a, &b, &c);
        L[a].data=b;
        L[a].nxt=c;       
    }

}
void printL(const List& L, rank head)
{
    rank p=L[head].nxt;
    while (L[p].nxt!=Null)
    {
        printf("%05d %d %05d\n", p, L[p].data, L[p].nxt); //地址补0五位
        p=L[p].nxt;
    }
    printf("%05d %d %d\n", p, L[p].data, Null);  //地址-1单独输出
    
}
bool can(const List& L, rank p, int k)
{
    bool flag=true;
    for(int cnt=0; cnt<k; cnt++){
        p=L[p].nxt;
        if(p==Null){
            flag=false;
            break;
        }
    }
    return flag;
}
rank reversek(List& L, rank p, int k)
{
    if(k<2) return L[p].nxt;
    rank p1, p2, p3;
    p1=p;
    p2=L[p1].nxt;
    for(int i=0; i<k; i++){
        p3=L[p2].nxt;
        //反向p2和p3之间的箭头 即改L[p2].nxt;
        L[p2].nxt=p1;
        //更新p1,p2
        p1=p2; p2=p3;
    }
    //两头
    rank pk=L[p].nxt; //原来第一个元素是第k个
    L[pk].nxt=p2;
    L[p].nxt=p1;
    return pk;
}
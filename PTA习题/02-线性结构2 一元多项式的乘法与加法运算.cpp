#include <cstdio>
struct term
{
    int ratio;
    int index;
    bool deleted;
    term()
        :deleted(false){}
};
typedef term *poly;
void swap(term &a, term &b)
{
    term c=a;
    a=b;
    b=c;
}
int simplify(poly &p3, int n3)
{
    //排序
    bool bubbled=false;
    while (!bubbled)
    {
        bubbled=true;
        for(int i=0; i<n3-1; i++)
            if(p3[i].index<p3[i+1].index){
                swap(p3[i], p3[i+1]);
                bubbled=false;
            }
    }
    //合并同类项
    int n=n3;
    int j=-1; //指示第一个同类项
    for(int i=0; i<n3-1; i++)
        if(p3[i].index==p3[i+1].index){
            if(j==-1) j=i; 
            p3[j].ratio+=p3[i+1].ratio;
            p3[i+1].deleted=true; n--;
        }else j=-1;
    //去除0项
    for(int i=0; i<n3; i++)
        if(p3[i].ratio==0){
            p3[i].deleted=true; n--;
        }
    return n;
}
void printploy(const poly &p4, int n4, int n4new)
{
    if(n4new==0){
        printf("0 0\n");
        return;
    }
    int j=1;
    for(int i=0; i<n4; i++){
        if(p4[i].deleted==false){
            if(j==n4new){
                printf("%d ", p4[i].ratio);
                printf("%d", p4[i].index);
            }else{
                printf("%d ", p4[i].ratio);
                printf("%d ", p4[i].index);             
            }
            j++;
        }
    }
    printf("\n");
}
int main(int argc, char const *argv[])
{
    //输入
    int n1, n2;
    scanf("%d", &n1);
    poly p1=new term[n1];
    for(int i=0; i<n1*2; i++){
        if(i%2==0) scanf("%d", &p1[i>>1].ratio); 
        else scanf("%d", &p1[i>>1].index);
    }
    scanf("%d", &n2);
    poly p2=new term[n2];
    for(int i=0; i<n2*2; i++){
        if(i%2==0) scanf("%d", &p2[i>>1].ratio); 
        else scanf("%d", &p2[i>>1].index);
    }
    //交叉乘
    int n3=n1*n2;
    poly p3=new term[n3];
    int k=0;
    for(int i=0; i<n1; i++)
        for(int j=0; j<n2; j++, k++){
            p3[k].ratio=p1[i].ratio*p2[j].ratio;
            p3[k].index=p1[i].index+p2[j].index;
        }
    int n3new=simplify(p3, n3);
    //多项式相加
    int n4=n1+n2;
    poly p4=new term[n4];
    for(int i=0; i<n1; i++){
        p4[i].index=p1[i].index;
        p4[i].ratio=p1[i].ratio;
    }
    for(int i=0; i<n2; i++){
        p4[n1+i].index=p2[i].index;
        p4[n1+i].ratio=p2[i].ratio;
    }
    int n4new=simplify(p4, n4);
    //输出
    printploy(p3, n3, n3new);
    printploy(p4, n4, n4new);
    return 0;
}

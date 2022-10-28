#include<cstdio>
#define Max_Size 1<<22
class stack
{
private:

    int _size;
public:
    int* data;
    int size(){return _size;}
    stack():_size(0), data(new int[Max_Size]){}
    int top(){return data[_size-1];}
    int pop(){return data[--_size];}
    void push(int e){data[_size++]=e;}
};
int main(int argc, char const *argv[])
{
    stack A, S;
    int n, m;
    scanf("%d %d", &n, &m);
    int B[n];
    for(int i=0; i<n; i++) scanf("%d", B+i);
    enum headle{push, pop}; headle pp[n];
    for(int i=n; i>0; i--) A.push(i);
    int hnum=0, i=0;
    while (A.size()||S.size())
    {
        if (S.size()==m) break;
        if (A.size()) {S.push(A.pop()); pp[hnum++]=push;}
        if (S.top()==B[i]){
            S.pop(); pp[hnum++]=pop;
            i++;
            continue;
        }
        else if (!A.size()) break;
    }
    if(i==n)
        for(int j=0; j<hnum; j++) 
            printf("%s\n", pp[j]==push ? "push":"pop");
    else printf("No\n");
    
    return 0;
}

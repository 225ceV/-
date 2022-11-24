#include<cstdio>
void readarr(int *arr, int n);
bool ispops(int *arr, int n, int m);
int main(int argc, char const *argv[])
{
    int m, n, k;
    scanf("%d %d %d\n", &m, &n, &k);
    int *arr=new int[n];
    while (k--)
    {
        readarr(arr, n);
        printf("%s\n", ispops(arr, n, m)?"YES":"NO");
    }
    
    return 0;
}
void readarr(int *arr, int n)
{
    for(int i=0; i<n; i++)
        scanf("%d", arr+i);
}
bool ispops(int *arr, int n, int m)
{
    int *stack=new int[m+1];
    int top=-1, cnt=0;
    int sp=0;
    while(cnt<n)
    {
        stack[++top]=++cnt;
        if(top==m) return false;
        while(top>=0&&stack[top]==arr[sp]){
            stack[top]=0;
            top--;
            sp++;
        }
    }

    if(sp==n) return true;
    else return false;
}
#include <cstdio>

int main(int argc, char const *argv[])
{
    int num;
    int *arr=new int[num];
    scanf("%d\n", &num);
    for(int i=0; i<num; i++) scanf("%d", arr+i);
    int max=0, i=0, sum=0;
    while (i<num)
    {
        sum+=arr[i++];
        if(sum<0) sum=0;
        else if(sum>max) max=sum;
    }
    
    printf("%d\n", max);
    
    return 0;
}

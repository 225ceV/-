#include <cstdio>

int main(int argc, char const *argv[])
{
    int num;
    int *arr=new int[num];
    scanf("%d\n", &num);
    for(int i=0; i<num; i++) scanf("%d", arr+i);
    int max=0, lo=0, loi=0, hi=0, i=0, sum=0; //max:[lo, hi]
    while (i<num)
    {
        sum+=arr[i++];
        if(sum<0){
            sum=0; 
            loi=i;
        }
        else if(sum>max){
            max=sum;
            hi=i-1;
            lo=loi;
        } 
    }
    if(max==0){
        int keyfor0=-1;
        for(int i=0; i<num; i++)
            if(arr[i]==0){
                keyfor0=i;
                break;
            }

        if(keyfor0<0){
            lo=0;hi=num-1;
        }else{
            lo=hi=keyfor0;
        }
        
    }
    printf("%d %d %d\n", max, arr[lo], arr[hi]);
}

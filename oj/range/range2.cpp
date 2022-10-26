#include <iostream>
#include <cstdio> 
using namespace std;
int get_count(int begin, int end, int lower, int upper, int *arr)
{
    if(arr[end]<lower)
        return 0;
    if(arr[begin]>upper)
        return 0;
    if(arr[end]<=upper && arr[begin]>=lower)
        return end-begin+1;
    return get_count(begin, (begin+end)/2, lower, upper, arr)+get_count((begin+end)/2+1, end, lower, upper, arr);
}

int find(int begin, int end, int aim, int* arr, bool& isfind)
{
    //hi在数组后方多留了一个位置
    int mid, lo=begin, hi=end;
    isfind=false;
    while (hi>lo)
    {
        mid=(hi+lo)>>1;
        if(aim<arr[mid]){
            hi=mid;
        }else if(aim>arr[mid]){
            lo=mid+1;
        }else{
            hi=lo=mid;
            isfind=true;
        }
    }
    return mid;
}
void sort(int begin, int end, int* arr)
{
    int temp;
    for(int i=begin; i<end; i++){
        for(int j=begin; j<end-i-1; j++){
            if(arr[j]>arr[j+1]){
                temp=arr[j];
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}
int main(int argc, char const *argv[])
{
    /* code */
    //input 
    int n, m;
    scanf("%d %d", &n, &m);
    int arr[n];
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    int lower[m], upper[m];
    for(int i=0; i<m; i++){ 
        scanf("%d %d", &lower[i], &upper[i]);
    }




    sort(0, n, arr);
    int count[m]={0}, loweri;
    bool lowercanfind;
    for(int i=0; i<m; i++){ 
        loweri=find(0, n, lower[i], arr, lowercanfind);
        if(!lowercanfind)
            loweri++;
        count[i]=find(0, n, upper[i], arr, lowercanfind)-loweri+1;
        cout<<count[i]<<endl;
    }
    return 0;
}

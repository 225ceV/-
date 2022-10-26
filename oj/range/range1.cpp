#include <iostream>
#include <cstdio> 
using namespace std;
int main(int argc, char const *argv[])
{
    /* code */
    int n, m;
    scanf("%d %d", &n, &m);
    int arr[n];
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
        //cout<<arr[i]<<endl;
    }
    int lower[m], upper[m];
    for(int i=0; i<m; i++){ 
        scanf("%d %d", &lower[i], &upper[i]);
    }
    int count[m]={0};
    for(int i=0; i<m; i++){ 
        for(int j=0; j<n; j++){
            if(arr[j]<=upper[i] && arr[j]>=lower[i]){
                count[i]++;
            }
        }
        cout<<count[i]<<endl;
    }
    return 0;
}

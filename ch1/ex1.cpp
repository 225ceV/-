#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

void generate(int num, int* arr)
{
    for(int i=0; i<num; i++){
        arr[i] = int(rand()%100);
    }
}
void sort(int* temp, int N){
    int t;
    for(int i=0; i<N-1; i++){
        for(int j=0; j<N-i-1; j++){
            if(temp[j]>temp[j+1]){
                t=temp[j];
                temp[j]=temp[j+1];
                temp[j+1]=t;
            }
        }
    }
}

int pick(int* arr, int* temp,int k, int N){
    for(int i=0; i<k; i++){
        temp[i]=arr[i];
    }
    /* sort the first k number */
    sort(temp, k);
    /* pick from rest */

/*     for(int i=k+1; i<N; i++){
        if(arr[i]<temp[k-1]){
            temp[k-1]=arr[i];
            sort(temp, k);
        }
    } */

    for(int i=k; i<N; i++){
        if(arr[i]<temp[k-1]){
            int j;
            for(j=k-1; j>0; j--){
                if(temp[j-1]>arr[i]){
                    temp[j]=temp[j-1];
                }else{
                    temp[j]=arr[i];
                    break;
                }
            }
            if(j==0)
                temp[0]=arr[i];
        }
    }
    
    return temp[k-1];
}



int main(int argc, char const *argv[])
{
    /* code */
    int N=200;
    int k=100;
    int arr[N], temp[k];
    clock_t start, end;
    generate(N, arr);
    for(int i=0; i<N; i++){
        cout<<arr[i]<<",";
        if(i%10==9)
            cout<<endl;
    }
    start=clock();
    cout<<"the kth number is: "<<pick(arr, temp, k, N)<<endl;
    end=clock();
    cout<<"taking: "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<endl;
    int sorted[N];
    for(int i=0; i<N; i++){
        sorted[i]=arr[i];
    }
    start=clock();
    sort(sorted,N);

    cout<<"the kth number is: "<<sorted[k-1]<<endl;
    end=clock();
    double sTime=double(end-start)/CLOCKS_PER_SEC;
    cout<<"taking: "<<sTime<<"s"<<endl;

    /* time table */
    double pTime[200];
    for(k=1; k<=N; k++){
        start=clock();
        pick(arr, temp, k, N);
        end=clock();
        pTime[k-1]=double(end-start)/CLOCKS_PER_SEC;
    }
    for(int i=0; i<N; i++){
        cout<<"picking time: "<<pTime[i]<<", sorting time"<<sTime<<endl;
    }

    /* debug */
    /* for(int i=0; i<N; i++){
        cout<<sorted[i]<<",";
        if(i%10==9)
            cout<<endl;
    }
    for(int i=0; i<k; i++){
        cout<<temp[i]<<",";
        if(i%10==9)
            cout<<endl;
    } */
    return 0;
}


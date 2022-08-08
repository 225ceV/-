#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;
template<typename Obj>
/* need operator< */
int pick(const vector<Obj> & arr, int k)
{
    int N = arr.size();
    vector<Obj> temp(arr.begin(), arr.begin()+k);
    sort(temp.begin(), temp.end());
    /* picking from the rest */
    int j;
    for(int i=k; i<N; i++){
        if(arr[i]<temp[k-1]){            
            
            for(j=0; j<k-1; j++){
                if(temp[k-2-j]<arr[i]){
                    temp.insert(temp.begin()+k-j-1, arr[i]);
                    break;
                }
            }
            if(j==k-1)
                temp.insert(temp.begin(), arr[i]);

        }
        /* debug */
        /* for(int i=0; i<k; i++)
            cout<<temp[i]<<",";
        cout<<endl; */
    }
    
    return temp[k-1];
}

int main(int argc, char const *argv[])
{
    /*ex1 with vector */
    int N=200, k=100;
    clock_t start, end;
    // generate arr
    vector<int> arr(N);
    for(int i=0; i<N; i++){
        arr[i]=rand()%100;
        cout<<arr[i]<<",";
        if(i%10==9)
            cout<<endl;
    }
    start=clock();
    int x=pick(arr, k);
    end=clock();
    cout<<"the kth number is: "<<x<<endl;
    cout<<"taking "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<endl;

    return 0;
}


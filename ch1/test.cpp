#include <iostream>
#include <vector>
using namespace std;

void fun_t1(vector<int> arr, int x)
{
    cout<<"fun1:"<<endl<<&arr<<endl<<arr[0]<<endl<<x<<endl<<&x<<endl;
}

void fun_t2(const vector<int> & arr, int & x)
{
    vector<int> y = arr;
    cout<<&y<<endl<<&arr<<endl;
    //cout<<"fun2:"<<endl<<&arr<<endl<<arr[0]<<endl<<x<<endl<<&x<<endl;
}

void fun_t3(int * arr, int * x)
{
    //cout<<"fun2:"<<endl<<&arr<<endl<<*arr<<endl<<*x<<endl<<&x<<endl;
    printf("fun3\n%p\n%d\n%p\n%d\n", arr, *(arr+1), x, *x);
}

int main(int argc, char const *argv[])
{
    /* date 2022.08.04 */
    /* int arr1[2]={0,1};
    int *arr2 = new int[10];
    arr1[1]=2;
    cout<<arr1[0]<<endl<<arr1[1]<<endl;

    //vector<vector<int> > m(5, vector<int>(6));
    vector<vector<int> > m(5);
    for(int i=0; i<5; i++){
        m[i].resize(6);
    }
    cout<<m[0][0]<<endl; */

    /* date 2022.08.06 */
    vector<int> x(3, 2);
    /* vector<int> y(x.begin(), x.begin()+2);
    cout<<x.size()<<endl<<y.size()<<endl; */
    int z=6;
    fun_t2(x, z);

    return 0;
}


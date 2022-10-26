#include "Vector.h"
#include <iostream>
using namespace std;
class printd
{
public:
    void operator() (int x){
        printf("%d\n", x);
    }
};
int main(int argc, char const *argv[])
{
    int arr[6]={6,5,4,3,2,1};
    Vector<int> v(arr, 6);
    printd print;
    v.traverse(print);
    v.sort();
    v.traverse(print);
    return 0;
}

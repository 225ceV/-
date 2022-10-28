#include <cstdio>

class trainStock
{
private:
    int *_arr, _size;
public:
    trainStock(int max_size);
    ~trainStock(){}
    int pop();
    int top();
    void push(int );
    int size() {return _size;}
};

trainStock::trainStock(int max_size)
{
    _arr=new int[max_size];
    _size=0;
}
int trainStock::top()
{
    return _arr[_size-1];
}
int trainStock::pop()
{
    int temp=top();
    _size--;
    return temp;
}
void trainStock::push(int e)
{
    _arr[_size]=e;
    _size++;
}

int main(int argc, char const *argv[])
{
    int n, m;
    scanf("%d %d", &n, &m);
    int B[n]; trainStock A(n), S(n<<1);
    for(int i=0; i<n; i++) 
        scanf("%d", B+i);
    for(int i=n; i>0; i--) 
        A.push(i);
    enum headle{push, pop}; headle pp[n];
    int ppN=0, BN=0;
    S.push(A.pop()); pp[ppN++]=push; //push 
    while (BN<n)
    {
        if ( B[BN]==S.top() ) {
            //pop
            S.pop(); pp[ppN++]=pop;
            BN++;
        } else if ( A.size() ){
            S.push(A.pop()); pp[ppN++]=push; //push 
            if ( S.size()>m ) break; 
        } else break;
    }
    if(BN==n) 
        for(int i=0; i<ppN; i++)
            printf("%s\n", pp[i]==push?"push":"pop");
    else printf("No");
    return 0;
}

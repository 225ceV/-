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
    trainStock S(n+1); int Av=1, Bv;
    enum headle{push, pop}; headle pp[n];
    int ppN=0, BN;
    S.push(Av++); pp[ppN++]=push; //push 
    scanf("%d", &Bv); BN=0;
    while (BN<n)
    {
        if ( Bv==S.top() ) {
            //pop
            S.pop(); pp[ppN++]=pop;
            if ( ++BN!=n ) scanf("%d", &Bv);  // next B
        } else if ( Av<=n ){
            S.push(Av++); pp[ppN++]=push; //push 
            if ( S.size()>m ) break; 
        } else break;
    }
    if(BN==n) 
        for(int i=0; i<ppN; i++)
            printf("%s\n", pp[i]==push?"push":"pop");
    else printf("No");
    return 0;
}

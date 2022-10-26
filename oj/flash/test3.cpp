#include <cstdio>
bool equaled(int &a, int &b)
{
    if(a==b) return true;
    a>b ? a=a-b : b=b-a;
    return false;
}

int main(int argc, char const *argv[])
{
    int a,b;
    scanf("%d %d", &a, &b);
    while (!equaled(a, b));
    printf("%d\n", a);
    return 0;
}

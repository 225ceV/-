#include <cstdio>
int main(int argc, char const *argv[])
{
    setvbuf(stdin, new char[1<<20], _IOFBF, 1<<20);
    setvbuf(stdout, new char[1<<20], _IOFBF, 1<<20);
    int n;
    scanf("%d", &n);
    int a, b;
    while (n-->0)
    {
        scanf("%d %d", &a, &b);
        printf("%d\n", a+b);
    }
    
    return 0;
}

#include <cstdio>
int main(int argc, char const *argv[])
{
    char* s=new char[90];
    scanf("%s", s);
    for(int i=0; i<90; i++){
        printf("%d ", s[i]);
    }
    return 0;
}

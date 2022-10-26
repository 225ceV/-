#include <cstdio>
int main(int argc, char const *argv[])
{
    int hh, mm, ss;
    int h2, m2, s2;
    int time;
    scanf("%d:%d:%d", &hh, &mm, &ss);
    scanf("%d:%d:%d", &h2, &m2, &s2);
    time=(h2-hh)*3600+(m2-mm)*60+(s2-ss);
    printf("%d\n", time<0 ? 24*3600+time : time);
    return 0;
}

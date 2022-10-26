#include <iostream>
#include <stdio.h>
#define STR_LEN 4096
#include<string>
using namespace std;
bool count_a(char ch, int *arr)
{
    if ((int)ch==0) return false; 
    if (ch<='Z' && ch>='A') arr[ch-(int)('A')]++;
    if (ch<='z' && ch>='a') arr[ch-(int)('a')]++;
    return true;
}
int main(int argc, char const *argv[])
{
    char s[STR_LEN+1];
    int num[26]={0};
    cin.getline(s, STR_LEN);
    //fgets(s, STR_LEN);
    int i=0;
    while (count_a(s[i++], num));
    for(i=0; i<26; i++){
        if(num[i]>0) printf("%c: %d\n", i+'A', num[i]);
    }
    return 0;
}

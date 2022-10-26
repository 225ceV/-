#include <cstdio>
#include <cstring>
 
const int SZ = 1<<20;  //快速io
struct fastio{
    char inbuf[SZ];
    char outbuf[SZ];
    fastio(){
        setvbuf(stdin,inbuf,_IOFBF,SZ);
        setvbuf(stdout,outbuf,_IOFBF,SZ);
    }
}io;
 
char ch[20001];
char temp[20001];
int size=0,pos;
 
 
int res(int a)
{
	int head = a,last = a;
	char elem;
	
	elem = ch[a];
	while(ch[head] == elem && head) head--;
	if(head || ch[head] != elem) head++;
	while(ch[last] == elem && last < size) last++;
	if(last - head > 2)
	{
		strcpy(temp,ch + last);
		strcpy(ch + head, temp);
		size = size + head - last;
		pos = head;
		return 1;
	}
	else
	return 0;
}
 
int main()
{
	int i = 0;
	int n;
	char e;
	
	fgets(ch, 20001, stdin);
	while(ch[size] >= 'A' && ch[size] <= 'Z')size++;
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d %c",&pos,&e);
		strcpy(temp, ch + pos);
		strcpy(ch + pos + 1, temp);
		ch[pos] = e;size++;
		while(res(pos) && size);
		if(size)
		printf("%s", ch);
		else
		printf("-\n");
	}
	return 0;
}
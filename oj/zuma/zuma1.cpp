#include <cstdio>
#include <list>
using namespace std;



// int need_disappear(list<char>::iterator it) //0完全相同 1后两个相同 -1其他
// {
//     char color=*it;
//     if(color==*(++it)){
//         color=*it;
//         if(color==*(++it)) return 0;
//     }else{
//         color=*it;
//         if(color==*(++it)) return 1;
//     }
//     return -1;
// }
bool need_disappear(list<char>::iterator it)
{
    char color=*it;
    if(*(++it)!=color) return false;
    if(*(++it)!=color) return false;
    return true;
}

list<char>::iterator disappear(list<char>& lst, list<char>::iterator it) //数量不一定是3
{
    char disappear_color=*it;
    if(it==lst.begin()){
        while (*it == disappear_color) 
            lst.erase(it++);
        return lst.begin();
    }
    list<char>::iterator prev=--it;
    it++;
    while (*it == disappear_color)
        lst.erase(it++);
    return prev;
}

int near_check(list<char>& lst, list<char>::iterator it)
{
    int i;
    list<char>::iterator check_end=--(--(lst.end()));
    if (need_disappear(--it)){
        it=disappear(lst, it);
        near_check(lst, it);
        return ++i;
    }
    if (need_disappear(++it)){
        it=disappear(lst, it);
        near_check(lst, it);
        return ++i;
    }
    return i;
}

void check(list<char>& lst)
{
    list<char>::iterator it=lst.begin();
    list<char>::iterator check_end=--(--(lst.end()));
    while (it!=check_end){
        if(need_disappear(it)){
            it=disappear(lst, it);
            near_check(lst, it);
            break;
        }
        it++; 
    }
    
}

int main(int argc, char const *argv[])
{
    list<char> zumaState;
    char *st=new char[10000];
    scanf("%s", st);
    int i=0;
    while (st[i]>0) zumaState.emplace_back(st[i++]);
    delete [] st;
    int n; scanf("%d", &n);
    int* rank=new int[n]; char* cl=new char[n];
    for(i=0; i<n; i++) {scanf("%d %c", rank+i, cl+i);}

    list<char>::iterator it; int j;
    for(i=0; i<n; i++){
        for(it=zumaState.begin(), j=0; j<rank[i]; j++, it++);
        zumaState.insert(it, cl[i]);
        check(zumaState);
        for(it=zumaState.begin(); it!=zumaState.end(); it++) printf("%c", *it);
        if(zumaState.size()==0) printf("-");
        printf("\n");
    }
    
    
    return 0;
}


// stl库局限,near_check.
// 输出:
// ACCBA
// 5
// 1 B
// 0 A
// 2 B
// 4 C
// 0 A
// ABCCBA
// AABCCBA
// AABBCCBA
// double free or corruption (out)
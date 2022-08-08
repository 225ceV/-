#include <iostream>
using namespace std;

void permute(const string & str){
    cout<<"this is function A."<<endl;
}
void permute(const string & str, int low, int high){
    cout<<"this is function B."<<endl;
}
int main(int argc, char const *argv[])
{
    string s="ohhhh";
    permute(s);
    permute(s, 9, 89);
    return 0;
}

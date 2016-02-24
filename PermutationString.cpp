// Example program
#include <iostream>
#include <string>
using namespace std;
void myswap(string &s,int a,int b){
    char c=s[a];
    s[a]=s[b];
    s[b]=c;
}
void perm_s(string &s,int x,int y){
    if(x==y)
        cout<<s<<endl;
    else{
        for(int i=x;i<=y;++i){
            myswap(s,x,i);
            perm_s(s,x+1,y);
            myswap(s,x,i);
        }
    }
}
int main()
{
    string s="ABCD";
    perm_s(s,0,s.length()-1);
}

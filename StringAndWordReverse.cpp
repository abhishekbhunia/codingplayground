// Example program
#include <iostream>
#include <string>
using namespace std;
void str_reverse(string &s){
    if(s.length()<=0)
        return;
    for(int i=0;i<s.length()/2;++i){
        char t=s[i];
        s[i]=s[s.length()-1-i];
        s[s.length()-1-i] = t;
    }
}
void s_rev_rec(string &s,int b,int e){
    if(b<e){
        //pre-order swap
        char t=s[b];
        s[b]=s[e];
        s[e]=t;
        //recurse on slen=n-1
        s_rev_rec(s,b+1,e-1);
    }
}
void w_rev_rec(string &s,int b,int e){
    //reverse entire string
    s_rev_rec(s,b,e);   
    //reverse each word
    int i=0;
    int start=i,end=i;
    while(s[i]){
        if(s[i]==' '){
            end=i-1;
            s_rev_rec(s,start,end);
            start=i+1;
        }
        i++;
    }
    s_rev_rec(s,start,s.length()-1);
   
}
int main()
{
    string s="";
    cout<<s<<endl;
    w_rev_rec(s,0,s.length()-1);
    cout<<s<<endl;
}

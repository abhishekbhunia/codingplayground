// Mnemonic - Recursion
#include <array>
#include <iostream>
#include <string>

using namespace std;

const array <string,10> M={{"0","1","ABC","DEF","GHI","JKL","MNO","PQRS","TUV","WXYZ"}};
void mnemonic_foo(string num,int start,string ans){
    if(start==ans.size())//base case
        cout<<ans<<endl;
    else{//recurse
        for(const char &c:M[num[start]-'0']){
            ans[start]=c;
            mnemonic_foo(num,start+1,ans);
        }
        
    }
}
int main()
{
    string num;
    cin>>num;
    string ans(num.size(),0);
    mnemonic_foo(num,0,ans);
    cin>>num;
    return 0;
}

// Example program
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
using namespace std;
int main()
{
    //pattern = "abba", str = "dog cat cat dog" should return true.
    //pattern = "abba", str = "dog cat cat fish" should return false.
    //pattern = "aaaa", str = "dog cat cat dog" should return false.
    //pattern = "abba", str = "dog dog dog dog" should return false.
    string s="dog dog dog dog";
    
    stringstream ss;
    ss<<s;
    string pat="abba";
    vector<string> vs;
    string s3;
    while(getline(ss,s3,' ')){
        vs.push_back(s3);
    }
    cout<<vs.size()<<" "<<pat.length()<<endl;
    unordered_map<char,string> mp;
    bool ok=true;
    int pos=0;
    for(char c:pat){
        auto it=mp.find(c);
        if(it==mp.end())
        {
            for(auto it2=mp.begin();it2!=mp.end();++it2){
                //cout<<it2->first<<endl;
                if(it2->second==vs[pos]){
                    //cout<<"string: "<<vs[pos]<<" was matched with "<<it2->first<<", cant match it with "<<c<<endl;
                    ok=false;
                    break;
                }
            }
            if(!ok)
                break;
            //cout<<"not found:"<<c<<" entering:"<<vs[pos]<<endl;            
            mp[c]=vs[pos++];
            
        }
            
        else{
            if(it->second!=vs[pos]){
                //cout<<"Mismatch:"<<c<<" should be:"<<it->second<<" found:"<<vs[pos]<<" pos:"<<pos<<endl;
                ok=false;
                break;
            }
            pos++;
        }            
    }
    
    
    cout<<"Result:"<<ok<<endl;
}

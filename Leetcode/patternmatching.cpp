#include<string>
#include<vector>
#include<unordered_map>
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        //string s="dog dog dog dog";
        stringstream ss;
        ss<<str;
        //string pat="abba";
        vector<string> vs;
        string s3;
        while(getline(ss,s3,' ')){
            vs.push_back(s3);
        }
        //cout<<vs.size()<<" "<<pat.length()<<endl;
        unordered_map<char,string> mp;
        bool ok=true;
        int pos=0;
        for(char c:pattern){
            auto it=mp.find(c);
            if(it==mp.end())
            {
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
        
        return ok;
        //cout<<"Result:"<<ok<<endl;
    }
};
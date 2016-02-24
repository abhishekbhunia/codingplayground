// Example program
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
using namespace std;
int main(){

	//pattern = "abba", str = "dog cat cat dog" should return true.
    //pattern = "abba", str = "dog cat cat fish" should return false.
    //pattern = "aaaa", str = "dog cat cat dog" should return false.
    //pattern = "abba", str = "dog dog dog dog" should return false.
    string s="dog cat cat dog";    
    stringstream ss;
    ss<<s;
    string pattern="aaaa";

    unordered_map<char,string> charstrmap;
    unordered_map<string,char> strcharmap;
    vector<string> vs;
    string str;
    while(getline(ss,str,' ')){
    	vs.push_back(str);
    }

    bool ok=true;

    if(pattern.length()==vs.size()){
    	for(int i=0;i<pattern.length();++i){
    		auto it=charstrmap.find(pattern[i]);
    		cout<<"Pattern[i]:"<<pattern[i]<<" Str[i]:"<<vs[i]<<endl;
    		if(it==charstrmap.end()){//new pattern char
    			auto it2=strcharmap.find(vs[i]);
    			cout<<pattern[i]<<" (char)not found in charstr"<<endl;
    			if(it2==strcharmap.end()){
    				cout<<vs[i]<<" (str)not found in strchar"<<endl;
    				charstrmap[pattern[i]]=vs[i];
    				strcharmap[vs[i]]=pattern[i];
    			}
    			//else new pattern char, 
    			else{
    				cout<<vs[i]<<" registered with different pattern char"<<endl;
    				ok=false;
    				break;
    			}
    		}
    		else{//for existing pattern char
    			cout<<pattern[i]<<" (char) found in charstr"<<endl;
    		    auto it3=strcharmap.find(vs[i]);// do not use it->second
    			if(it3!=strcharmap.end()&&it3->second==it->first)//check double mapping
    			{
    				cout<<vs[i]<<" (str) found in strchar and cross matched"<<endl;
    				continue;//ok=true;
    			}
    			else{
    				cout<<vs[i]<<" (str) found in strchar and no match"<<endl;
    				ok=false;
    				break;
    			}
    		}

    	}
    }


    cout<<"Result:"<<ok<<endl;

	return 0;
}
// Example program
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
int bsearch_max_less2(vector<int> v, int l, int r, int key){//max elem < key
    int ret = -1;
    while (l<=r){
        int m = l + ((r - l) >> 1);
        if (key <= v[m])
            r = m - 1;
        else{
            l = m + 1;
            ret = m;
        }
    }
    return ret;
}
int bsearch_min_more2(vector<int> v, int l, int r, int key){//max elem < key
    int ret = -1;
    while (l<=r){
        int m = l + ((r - l) >> 1);
        if (key < v[m]) {
            ret = m;
            r = m - 1;
        }
        else{
            l = m + 1;
        }
    }
    return ret;
}
int bsearch_max_less(vector<int> v, int l, int r, int key){//max elem < key
    int ret = -1;
    while (l<r){
        int m = l + ((r - l) >> 1);
        if (key <= v[m])
            r = m;
        else{
            l = m + 1;
            ret = m;
        }
    }
    return ret;
}
int bsearch_min_more(vector<int> v, int l, int r, int key){//max elem < key
    int ret = -1;
    while (l<r){
        int m = l + ((r - l) >> 1);
        if (key < v[m]) {
            ret = m;
            r = m;
        }
        else{
            if (key == v[m])
                ret = r;
            l = m + 1;
        }
    }
    return ret;
}
int BSR(vector<int> v,int val,int l,int r){
    if(l>r)
        return -1;
    int m=l+((r-l)>>1);
    if(v[m]==val)
        return m;
    else if(val<v[m])
        return BSR(v,val,l,m-1);
    else
        return BSR(v,val,m+1,r);
}
int BS(vector<int> v,int val){
    int l=0,r=v.size()-1,res=-1;
    while(l<=r){
        int m=l+((r-l)>>1);
        if(v[m]==val)
            return m;
        else if(val<v[m])
            r=m-1;
        else 
            l=m+1;
    }
    return res;
}
int firstKPBS(vector<int> v,int val){
    int l=0,r=v.size()-1,res=-1;
    while(l<=r){
        int m=l+((r-l)>>1);
        if(val==v[m])
            l=m+1;
        else if(val<v[m]){
            res=m;
            r=m-1;
        }
        else//val>v[m]
            l=m+1;          
        
    }
    return res;
}
int firstKBS(vector<int> v, int val){
    int l=0,r=v.size()-1,res=-1;
    while(l<=r){
        int m=l+((r-l)>>1);
        if(val==v[m]){
            res=m;
            r=m-1;
        }
        else if(val<v[m])
            r=m-1;
        else//val>v[m]
            l=m+1;
    }
    return res;
}
int findSmallestRotSortUniq(vector<int> v){
    int l=0,r=v.size()-1;
    while(l<r){
       int m=l+((r-l)>>1);
       if(v[m]>v[r])
            l=m+1;
        else 
            r=m;
    }
    return l;
}
int findSmallestRotSortGen(vector<int> v,int l,int r){
    if(l==r)
        return l;
    int m=l+((r-l)>>1);
    
    if(v[m]>v[r])
        return findSmallestRotSortGen(v,m+1,r);
    else if(v[m]<v[r])
        return findSmallestRotSortGen(v,l,m);
    else{
        int lv=findSmallestRotSortGen(v,l,m);
        int rv=findSmallestRotSortGen(v,m+1,r);
        return (lv<rv)?lv:rv;
    }
}
int findAiIsi(vector<int> v){
    int l=0,r=v.size()-1,res=-1;
    while(l<=r){
        int m=l+((r-l)>>1);
        int val=v[m]-m;
        if(val==0){
            return m;
        } 
        else if(val>0)
            r=m-1;         
        
        else
            l=m+1;
    }
    return res;
}
vector<int> findCommonInSortedArrays(vector<int> a,vector<int> b){
    int i=0,j=0;
    vector<int> ret;
    while(i<a.size()&&j<b.size()){
        if(a[i]==b[j]&&((a[i]!=a[i-1])||i==0)){
            ret.push_back(a[i]);
            i++;j++;
        }
        else if(a[i]<b[j])
            i++;
        else
            j++;
    }
    return ret;
}
vector<int> findCommonInSortedArraysBS(vector<int> a,vector<int> b){
    int res;
    vector<int> ret;
    for(int i=0;i<a.size();++i){
        res=BSR(b,a[i],0,b.size()-1);
        //res=BS(b,a[i]);
        
        /*if(res!=-1){
            cout<<"a:res:"<<a[res]<<endl;
            if((a[i]!=a[i-1])||i==0)
                ret.push_back(b[res]);
        }*/
        if(((res=BSR(b,a[i],0,b.size()-1))!=-1)&&((a[i]!=a[i-1])||i==0))
            ret.push_back(b[res]);
    }
    return ret;
    
}
void testBinarySearch(){
    vector<int> v;
    for(int i=0;i<10;++i)
        v.push_back(rand()%25+i*i);
    sort(v.begin(),v.end());
    copy(v.begin(),v.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
    cout<<BSR(v,100,0,v.size()-1)<<endl;
    v.insert(v.begin(),{1,3,5,5,5,5,6,7,7,7,8,8,8,8});
    copy(v.begin(),v.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
    cout<<firstKBS(v,7)<<endl;
    cout<<firstKPBS(v,104)<<endl;
    vector<int> v1{4,5,6,7,8,9,1,2,3};
    copy(v1.begin(),v1.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
    cout<<findSmallestRotSortUniq(v1)<<endl;
    v1.clear();
    v1.insert(v1.begin(),{8,9,1,2,3,4,5,6,7});
    copy(v1.begin(),v1.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
    cout<<findSmallestRotSortUniq(v1)<<endl;
    
    vector<int> v2{2,3,4,5,6,7,8,9,1,1,1,1};
    copy(v2.begin(),v2.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
    cout<<findSmallestRotSortGen(v2,0,v2.size()-1)<<endl;
    v2.clear();
    v2.insert(v2.begin(),{1,1,1,1,1,2,3,4,5,6,7,8,9});
    copy(v2.begin(),v2.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
    cout<<findSmallestRotSortGen(v2,0,v2.size()-1)<<endl;
    v2.clear();
    v2.insert(v2.begin(),{6,7,8,9,1,1,1,1,1,2,3,4,5});
    copy(v2.begin(),v2.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
    cout<<findSmallestRotSortGen(v2,0,v2.size()-1)<<endl;
    
    vector<int> v3{-10,-5,-3,0,4,7,8,9};
    copy(v3.begin(),v3.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
    cout<<findAiIsi(v3)<<endl;
    
    vector<int> a{1,2,3,4,5,6,7,8,9};
    vector<int> b{4,5,6,7,8,9,10,11,12};
    vector<int> ret=findCommonInSortedArrays(a,b);
    copy(ret.begin(),ret.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
    ret.clear();
     ret=findCommonInSortedArraysBS(a,b);
    copy(ret.begin(),ret.end(),ostream_iterator<int>(cout," "));
    cout<<endl;
    
}
int main()
{
    testBinarySearch();
    return 0;
}

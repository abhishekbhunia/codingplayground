//find k 'closest' (exclusive) elements in a sorted array with 'unique' elements O(logn + k)
#include <iostream>
#include <vector>
using namespace std;
int findCrossOverBS(vector<int> v, int low, int high, int x){
    if(x<v[low])
        return low;
    if(x>=v[high])
        return high;
    int mid = low + ((high-low)>>1);
    if(v[mid]<=x && v[mid+1]>x)
        return mid;
    else if(v[mid]<x)
        return findCrossOverBS(v,mid+1,high,x);
    else
        return findCrossOverBS(v,low,mid-1,x);
}
void findCrossOver(vector<int> v, int k, int x){
    int l=findCrossOverBS(v, 0, v.size()-1, x);
    int r=l+1;
    if(v[l]==x)
        l--;
    int count=0;
    while(l>=0 && r<v.size() && count<k){
        if( x-v[l] < v[r]-x )
            cout<<v[l--]<<" ";
        else
            cout<<v[r++]<<" ";
        count++;            
    }
    while(count<k && l>=0)
        cout<<v[l--]<<" ";
    while(count<k && r<v.size())
        cout<<v[r++]<<" ";
}
int main(){
    vector<int> v{12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56};
    int k=4, x=35;
    findCrossOver(v,k,x);
    
}
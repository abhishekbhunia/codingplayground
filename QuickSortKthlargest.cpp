//returns the index of kth largest element in an array of unique elements
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
template <typename T>
void vSwap(vector<T> &v,T a,T b){
	T x=v[a];
	v[a]=v[b];
	v[b]=x;
}
void printvector(vector<int> v){
    for(int i=0;i<v.size();++i)
        cout<<v[i]<<" ";
    cout<<endl;
}
int partition3(vector<int> &v,int low,int high){
	int pivot=low+rand()%(high-low+1);
	vSwap(v,pivot,high);
	int small=low-1;
	for(int i=low;i<high;++i){
		if(v[i]>v[high]){
			small++;
			if(small!=i)
				vSwap(v,small,i);
		}
	}
	small++;
	if(small!=high)
		vSwap(v,small,high);
	return small;
}
int partition(vector<int> &v,int low,int high){
	int pivot=low+rand()%(high-low+1);
	cout<<"pivot:"<<pivot<<" low:"<<low<<" high:"<<high<<endl;
	cout<<"Before Swap: ";printvector(v);
	vSwap(v,pivot,high);
	cout<<"After Swap: ";printvector(v);
	int small=low-1;
	for(int i=low;i<high;++i){
		if(v[i]<v[high]){
			small++;
			if(small!=i)
				vSwap(v,small,i);
		}
	}
	small++;
	if(small!=high)
		vSwap(v,small,high);
	cout<<"End of loop: ";printvector(v);cout<<"s:"<<small<<endl;
	return small;
}
void quicksort(vector<int> &v,int low,int high){
	if(low<high){
		int p=partition(v,low,high);
		quicksort(v,low,p);
		quicksort(v,p+1,high);
	}
}

int partition2(vector<int> &v,int low,int high){
	int pivot=low+rand()%(high-low+1);
	cout<<"pivot:"<<pivot<<" low:"<<low<<" high:"<<high<<endl;
	cout<<"Before Swap: ";printvector(v);
	vSwap(v,pivot,high);
	cout<<"After Swap: ";printvector(v);
	int highend=low;
	for(int i=low;i<high;++i){	
	    //cout<<"highend b4:"<<highend<<endl;
		if(v[i]>v[high]){
		    //cout<<"v["<<i<<"]("<<v[i]<<")>v["<<high<<"]("<<v[high]<<")"<<endl;
		    vSwap(v,highend++,i);	
		    //cout<<"highend after:"<<highend<<endl;
		}
		//cout<<"highend end:"<<highend<<endl;
		printvector(v);
	}
	vSwap(v,high,highend);
	cout<<"End of loop: ";printvector(v);cout<<"s:"<<highend<<endl;
	return highend;
}
int findKthLargest(vector<int> &v,int k,int l,int r){
	while(l<=r){
	    int p=partition2(v,l,r);
	    if(p==k-1)
	        return v[p];
	    else if(p>k-1)
	        r=p-1;
	    else
	        l=p+1;
	}
	
	/*int p=partition2(v,l,r);
	if(p==k-1)
		return v[p];
	else if(p>k-1)
		return findKthLargest(v,k,l,p-1);
	else
		return findKthLargest(v,k,p+1,r);*/
}
int main(void)
{
	vector<int> v;
	for (int i = 0; i < 10; ++i)
		v.push_back(rand() % 100 - 30);
	vector<int> v2(v);
	//simple quicksort for v2
	/*printvector(v2);
	quicksort(v2,0,v2.size()-1);	 
	printvector(v2);
	cout<<endl<<endl<<endl;*/
	
	//kth largest for v
	printvector(v);
	cout<<findKthLargest(v,5,0,v.size()-1)<<endl;
	printvector(v);
	int inp;
	cin>>inp;
	return 0;
}
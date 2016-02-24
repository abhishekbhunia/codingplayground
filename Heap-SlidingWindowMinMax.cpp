#include<iostream>
#include<queue>
#include<algorithm>
#include<iterator>
using namespace std;

void vint(vector<int> &v){
	for(int i=0;i<10;++i){		 
		v.push_back((rand()%50)-25);		 
	}
	
}
void pvint(vector<int> v){
	copy(v.begin(),v.end(),ostream_iterator<int>(cout," "));
	cout<<endl;
}
class cmpmin{
public:
    bool operator()(pair<int,int> a,pair<int,int> b)const{
        return a.first>b.first;
    }
};
//greater<pair<int,int>>
void pheap(priority_queue<pair<int,int>,vector<pair<int,int>>,cmpmin> pq){
    cout<<"Heap Contents:";
    while(!pq.empty()){
        cout<<pq.top().first<<" ";
        pq.pop();
    }
    cout<<endl;
}
void slidingwindowmin(vector<int> v,int wsize){
   priority_queue<pair<int,int>,vector<pair<int,int>>,cmpmin> pq;
   cout<<"Window Size:"<<wsize<<endl;
   for(int i=0;i<v.size();i++){
       cout<<"on :v["<<i<<"]="<<v[i]<<":min is:";
       pq.push(make_pair(v[i],i));
       //cout<<"Before ";pheap(pq);
       //what is the staring index for a window that ends at i? i-wsize+1
       while(pq.top().second<i-wsize+1){//
           pq.pop();
           //cout<<"After ";pheap(pq);
       }
        
       cout<<pq.top().first<<endl;
   }
}
int main(void){
	vector<int> v;
	vint(v);
	pvint(v);
	slidingwindowmin(v,3);

}

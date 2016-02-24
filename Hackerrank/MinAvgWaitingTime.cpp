#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
//need a mean-heap with a comparison function eqv to greater<T>; lower cooking time gets more priority
class pizza{
    public:
        int t,l;//arrival time, cokking time
        pizza(){}
        pizza(int a,int b):t(a),l(b){}
        bool operator<(pizza y){
                return t<y.t;
        }
        
};

class cmp{
    public:
        bool operator()(pizza a,pizza b){
            return a.l>b.l;
        }
};
int main(void){
    vector<pizza> pv;
    priority_queue<pizza,vector<pizza>,cmp> pq;
    long long cur_t=0,tot_wt=0;
    int nextid=0;
    
    int n;
    cin>>n;
    for(int i=0;i<n;++i){
        int t,l;
        cin>>t>>l;
        pv.push_back(pizza(t,l));
    }
    sort(pv.begin(),pv.end());
    
    while(1){
        int i;
        for(i=nextid;i<n;++i){
            if(pv[i].t<=cur_t)
                pq.push(pv[i]);
            else{
                nextid=i;
                break;
            }
        }
        if(i==n)
            nextid=n;
        if(!pq.empty()){
            pizza x=pq.top();
            tot_wt+=cur_t+x.l-x.t;
            cur_t+=x.l;
            pq.pop();
        }
        else{//pq is empty=>waiting for next worder=>advance clock
            if(nextid!=n)
                cur_t=pv[nextid].t;
        }
        if(nextid==n&&pq.empty())
            break;
        
    }
    cout<<tot_wt/n<<endl;
    return 0;
}
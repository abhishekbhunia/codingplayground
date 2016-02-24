// Example program
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iterator>
using namespace std;
class myComp{
public:
    bool operator()(pair<int, int> a, pair<int, int> b){
        return a.first>b.first;
    }
};
vector<int> mergeKarr(vector<vector<int>> s){
    priority_queue<pair<int, int>, vector<pair<int, int>>, myComp> pq;
    vector<int> sid(s.size(), 0);
    for (int i = 0; i<s.size(); ++i){
        pq.push({ s[i][0], i });
        sid[i] = 1;
    }
    vector<int> ret;
    while (!pq.empty()){
        pair<int, int> small = pq.top();
        if (sid[small.second]<s[small.second].size()){
            pq.push({ s[small.second][sid[small.second]++], small.second });
        }
        ret.push_back(small.first);
        pq.pop();
    }
    return ret;
}
vector<int> mergeIncDec(vector<int> v){
    vector<vector<int>> s;
    bool increasing = true;
    int start = 0;
    for (int i = 1; i<=v.size(); ++i){
        if ((i == v.size())||((v[i - 1] >= v[i]) && increasing) || ((v[i - 1]<v[i]) && !increasing)){
            if (increasing)
                s.emplace_back(v.begin() + start, v.begin() + i);
            else
                s.emplace_back(v.rbegin() + v.size() - i, v.rbegin() + v.size() - start);
            start = i;
            increasing = !increasing;
        }

    }
    /*if (start<v.size()){
        if (increasing)
            s.emplace_back(v.begin() + start, v.end());
        else
            s.emplace_back(v.rbegin(), v.rbegin() + v.size() - start);
    }*/

    //cout<<s.size()<<endl;
    for (int i = 0; i<s.size(); ++i){
        copy(s[i].begin(), s[i].end(), ostream_iterator<int>(cout, " "));
        cout << endl << s[i].size() << endl;
    }
    //return {};
    return mergeKarr(s);
}
int main()
{
    vector<int> v{ 1, 2, 3, 6, 5, 4, 7, 8, 9, 12, 11, 10 };
    /*vector<vector<int>> x;
    cout<<*(v.rbegin()+8-6)<<endl;
    x.emplace_back(v.begin(),v.begin()+4);
    copy(x[0].begin(),x[0].end(),ostream_iterator<int>(cout," "));*/

    vector<int> res = mergeIncDec(v);
    copy(res.begin(), res.end(), ostream_iterator<int>(cout, " "));

    int in;
    cin >> in;
    return 0;
}

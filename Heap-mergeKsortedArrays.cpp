#include<iostream>
#include<queue>
#include<vector>
#include<iterator>
using namespace std;
class myComp{
public:
	bool operator()(pair<int, int> a, pair<int, int> b){
		return a.first>b.first;//priority q uses max_heap as a default.the sorting orderis counter intuitive, Why?
	}
};

vector<int> mergeKsortedArrays(vector<vector<int>> &v){

	//pair<a,b> a=actual value, b=arr index.
	priority_queue<pair<int, int>, vector<pair<int, int>>, myComp> min_heap;
	vector<int> arr_id(v.size(), 0), ret;
	for (int i = 0; i<v.size(); ++i){
		if (v[i].size()>0){
			min_heap.push({ v[i][0], i });
			arr_id[i] = 1;
		}
	}

	while (!min_heap.empty()){
		pair<int,int> cur_min = min_heap.top();
		ret.push_back(cur_min.first);
		if (arr_id[cur_min.second]<v[cur_min.second].size()){
			min_heap.push({ v[cur_min.second][arr_id[cur_min.second]++], cur_min.second });
		}
		min_heap.pop();
	}
	return ret;
}
int main(void){

	vector<vector<int>> v(3, vector<int>());
	int k = 0;
	for (int i = 0; i<3; ++i){
		for (int j = 0; j<5; ++j){
			v[i].push_back(k);
			k += 5;
		}
	}
	for (int i = 0; i<3; ++i){
		for (int j = 0; j<5; ++j){
			cout << v[i][j] << " ";
		}
		cout << endl;
	}
	vector<int> res = mergeKsortedArrays(v);
	copy(res.begin(), res.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	/*for (int i = 0; i<3; ++i){
	for (int j = 0; j<5; ++j){
	cout << v[i][j] << " ";
	}
	cout << endl;
	}*/
	/*
	priority_queue<int, vector<int>, myComp> pq;
	vector<int> m{ 432, 655, 231, 98, 32, 8098, 324, 4 };
	for (int i = 0; i < m.size(); ++i)
	pq.push(m[i]);
	while (!pq.empty()){
	cout << pq.top() << " ";
	pq.pop();
	}*/





	int in;
	cin >> in;
	return 0;
}
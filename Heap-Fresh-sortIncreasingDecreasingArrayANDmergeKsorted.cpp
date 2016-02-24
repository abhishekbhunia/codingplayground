#include<iostream>
#include<vector>
#include<queue>
#include<functional>
#include<iterator>
#include<algorithm>
using namespace std;
class cmp{
public:
	bool operator()(pair<int, int> a, pair<int, int> b) const{
		return a.first > b.first;
	}
};

vector<int> mergeKsorted(vector<vector<int>> v){
	vector<int> ret,pos(v.size());
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> min_heap;//1st elem:actual value, 2nd:array it belongs to
	for (int i = 0; i < v.size(); ++i){
		min_heap.push(make_pair(v[i][0], i));
		pos[i] = 0;
	}
	
	while (!min_heap.empty()){
		pair<int, int> top = min_heap.top();		
		ret.push_back(top.first);
		min_heap.pop();		
		if (pos[top.second] < v[top.second].size() - 1){
			min_heap.push(make_pair(v[top.second][++pos[top.second]], top.second));
		}		
	}
	return ret;
}

vector<int> sortIncreasingDecreasing(vector<int> v){
	vector<vector<int>> v_2d;
	int beg = 0;
	bool increasing = true;
	for (int i = 1; i <= v.size(); ++i){
		
		if ((i == v.size()) || (increasing&&v[i] <= v[i - 1]) || (!increasing&&v[i] > v[i - 1])){
			if (increasing)
				v_2d.emplace_back(v.begin() + beg, v.begin() + i);
			else
				v_2d.emplace_back(v.rbegin() + v.size() - i, v.rbegin() + v.size() - beg);
			increasing = !increasing;
			beg = i;
		}
	}
	cout << endl;
	for (int i = 0; i < v_2d.size(); ++i){
		cout << "splitted array:" << i << " size:" << v_2d[i].size()<<endl;
		for (int j = 0; j < v_2d[i].size(); ++j)
			cout << v_2d[i][j] << " ";
		cout << endl;
	}
	return mergeKsorted(v_2d);
}
vector<int> test_mergeKsorted(){
	vector<vector<int>> v;
	v.insert(v.begin(), { 1, 3, 5, 7 });
	v.insert(v.begin(), { 2, 4, 6, 8 });
	v.insert(v.end(), { 1, 4, 7, 10 });
	v.insert(v.end(), { 2, 5, 8, 11 });
	cout << "Input:" << endl;
	for (int i = 0; i < v.size(); ++i){
		for (int j = 0; j < v[i].size(); ++j)
			cout << v[i][j] << " ";
		cout << endl;
	}
	return mergeKsorted(v);
}

vector<int> test_SortIncreasingDecreasing(){
	vector<int> v{ 1, 2, 3, 4, 8, 7, 6, 5, 9, 10, 11, 12, 4, 3, 2, 1 };
	cout << "Input:" << endl;
	copy(v.begin(), v.end(), ostream_iterator<int>(cout," "));
	return sortIncreasingDecreasing(v);
}
int main(void){
	cout << "1. MergeKSorted"<<endl;
	vector<int> ret = test_mergeKsorted();
	copy(ret.begin(), ret.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	
	cout << "2. SortIncreasingDecreasing" << endl;
	ret = test_SortIncreasingDecreasing();
	copy(ret.begin(), ret.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	int inp;
	cin >> inp;
	return 0;
}

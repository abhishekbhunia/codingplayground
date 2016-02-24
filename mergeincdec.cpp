// Example program
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iterator>
#include <queue>
#include <functional>
using namespace std;
//merge n-sorted arrays

class cmp{
public:
	bool operator()(pair<int, int> a, pair<int, int> b) const{
		return a.first > b.first;
	}
};
vector<int> mergeNsorted(vector<vector<int>> v){
	priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> min_heap;
	vector<int> ref(v.size(), -1), ret;
	for (int i = 0; i<v.size(); ++i){
		min_heap.push(make_pair( v[i][0], i ));
		ref[i] = 0;
	}
	while (!min_heap.empty()){
		pair<int, int> t = min_heap.top();
		ret.push_back(t.first);

		min_heap.pop();
		if (ref[t.second]<v[t.second].size() - 1)
			min_heap.push(make_pair( v[t.second][++ref[t.second]], t.second ));


	}
	return ret;
}
vector<int> mergeIncreasingDecreasing(vector<vector<int>> v){
	vector<int> init;
	vector<vector<int>> v2;
	for (int i = 0; i < v.size(); ++i){
		for (int j = 0; j < v[i].size; ++j)
			init.push_back(v[i][j]);
	}
	bool increasing = true;
	int beg = 0;
	for (int i = 1; i < init.size(); ++i){
		if (init[i] < init[i - 1] && increasing)
			v2.emplace_back(init.begin() + beg, init.begin() + i);
		
		if (init[i] >= init[i - 1] && !increasing) 
			v2.emplace_back(init.rbegin() + init.size() - i, init.rbegin() + init.size() - beg);

		beg = i;
		increasing = !increasing;
	}
}
void testMergeIncreasingDecreasing(){

}
void testMergeKSorted(){
	vector<vector<int>> v(4);
	v[0] = { 2, 4, 6, 8 };
	v[1] = { 1, 3, 5, 7 };
	v[2] = { 0, 3, 6, 9 };
	v[3] = { 2, 5, 8, 10 };
	vector<int> ret = mergeNsorted(v);
	cout << "Input:" << endl;
	copy(v[0].begin(), v[0].end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	copy(v[1].begin(), v[1].end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	copy(v[2].begin(), v[2].end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	copy(v[3].begin(), v[3].end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	cout << endl << "Output:(MergeKSorted)" << endl;
	copy(ret.begin(), ret.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

}
int main()
{
	testMergeKSorted();

	 

	int inp;
	cin >> inp;
	return 0;
}

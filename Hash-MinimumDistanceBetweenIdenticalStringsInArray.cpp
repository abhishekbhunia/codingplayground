// Example program
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iterator>
#include <unordered_map>
#include <algorithm>
using namespace std;
int main(void){
	vector<string> v{ "Aby", "Monty", "Carla", "Aby", "Carla", "X", "Y", "Monty" };
	unordered_map<string, int> mp;
	int minv = numeric_limits<int>::max();
	string res;
	for (int i = 0; i < v.size();++i){
		auto it = mp.find(v[i]);
		if (it != mp.end()){
			//if block is extra/redundant code to store the result as well
			if (i - it->second < minv)
				res = v[i];
			minv = min(minv, i - it->second);
			
		}
		mp[v[i]] = i;//update the last occurance of each string
	}
	cout << minv << " " << res << endl;
	int inp;
	cin >> inp;
	return 0;
}
// Example program
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iterator>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <functional>
#include <iterator>
using namespace std;
vector<vector<string>> findAnagrams(vector<string> v){
	unordered_map<string, vector<string>> mp;
	vector<vector<string>> ret;
	for (int i = 0; i < v.size(); ++i){
		string str_sorted = v[i], str = v[i];
		sort(str_sorted.begin(), str_sorted.end());
		mp[str_sorted].push_back(str);		
	}
	for (const pair<string,vector<string>> &sv : mp){
		if (sv.second.size() >= 2){
			ret.emplace_back(sv.second.begin(), sv.second.end());
		}
	}
	return ret;
}
void test_findAnagrams(){
	vector<string> v{ "mia", "ami", "hotdog", "babe", "beba", "valid", "invalid", "yahoo", "hooya", "ooyah", "google" };
	copy(v.begin(), v.end(), ostream_iterator<string>(cout, " "));
	cout << endl;
	vector<vector<string>> ret = findAnagrams(v);
	for (int i = 0; i < ret.size(); ++i){
		for (int j = 0; j < ret[i].size(); ++j)
			cout << ret[i][j] << " ";
		cout << endl;
	}
}
int main(void){
	test_findAnagrams();

	int inp;
	cin >> inp;
	return 0;
}
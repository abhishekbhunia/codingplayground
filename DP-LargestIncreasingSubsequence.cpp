#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>> foo(vector<int> v){
	vector<vector<int>> L(v.size());
	L[0].push_back(v[0]);

	for (int i = 1; i<v.size(); ++i){
		for (int j = 0; j<i; ++j){
			if (v[j]<v[i] && L[i].size()<L[j].size() + 1)
				L[i] = L[j];
		}
		L[i].push_back(v[i]);
	}

	/*vector<vector<int>> res = L;
	for (int i = 0; i<res.size(); ++i){
		cout << "level:" << i << ": ";
		for (int j = 0; j<res[i].size(); ++j)
			cout << res[i][j] << " ";
		cout << endl;
	}*/
	int r = L[0].size();
	vector<vector<int>> ret;
	for (int i = 1; i < L.size(); ++i){
		L[i].size() >= r ? r = L[i].size() : r = r;
	}
	for (int i = 0; i < L.size(); ++i){
		if (L[i].size() == r)
			ret.push_back(L[i]);
	}
	return ret;
}

int main(void){
	vector<int> v{ 2, 1, 4, 3, 4, 5, 1, 2, 7, 5, 3, 4, 4, 5 };
	vector<vector<int>> res = foo(v);
	for (int i = 0; i<res.size(); ++i){
		cout << "string " << i+1 << ": ";
		for (int j = 0; j<res[i].size(); ++j)
			cout << res[i][j] << " ";
		cout << endl;
	}

	int inp;
	cin >> inp;
	return 0;
}
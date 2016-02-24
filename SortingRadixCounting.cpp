#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define pnl cout<<endl
void pv(vector<int> v){
	for (int i = 0; i < v.size(); ++i){
		cout << v[i] << " ";
	}
	pnl;
}
vector<int> countSort(vector<int> v){
	int maxV = 0, minV = 0;
	for (int &i : v){
		maxV = max(maxV, i);
		minV = min(minV, i);
	}
	int to_Add = 0;
	if (minV < 0){
		to_Add = -minV;
		maxV += to_Add;
	}
	
	vector<int> counts(maxV+1, 0);
	vector<int> op(v.size());
	for (int &i : v)
		counts[i + to_Add]++;
	for (int i = 1; i < counts.size(); ++i)
		counts[i] += counts[i - 1];
	for (int &i : v)
		op[(counts[i + to_Add]--) - 1] = i;
	for (int i = 0; i < v.size(); ++i)
		v[i] = op[i];
	return op;
}
void radixSortHelper(vector<int> &v, int exp){
	
	vector<int> counts(10, 0);
	vector<int> op(v.size());
	for (int &i : v)
		counts[(i / exp) % 10]++;
	
	for (int i = 1; i < 10; ++i)
		counts[i] += counts[i - 1];
	
	//IMP: Follwing loop must start from end, since count-- requires higher number from previous round is encountered
	//first in case of a tie in present round
	for (int i = v.size() - 1; i >= 0; --i){
		op[(counts[(v[i] / exp) % 10]--) - 1] = v[i];
	}
	 
	for (int i = 0; i < v.size(); ++i)
		v[i] = op[i];
	
}
void radixSort(vector<int> &v){
	int maxV = 0, minV = 0;
	for (int &i : v){		
		minV = min(minV, i);
	}
	
	if (minV < 0){
		for (int i = 0; i < v.size(); ++i)
			v[i] += (-minV);
	}
	for (int &i : v){
		maxV = max(maxV, i);		
	}
	vector<int> ret;
	for (int i = 1; maxV / i > 0; i *= 10){
		radixSortHelper(v, i);		
	}
	if (minV < 0){
		for (int i = 0; i < v.size(); ++i)
			v[i] -= (-minV);
	}
}
int main(){
	//COUNTING SORT
	vector<int> v{ 3, 1, -6, 6, 14, 0, -2, 8 };
	pv(v);
	auto ret = countSort(v);
	pv(ret);
	//RADIX SORT
	vector<int> v2{ -170, 45, 75, -90, 802, 24, -2, 66 };
	 
	pv(v2);
	radixSort(v2);
	pv(v2);
	getchar();
}
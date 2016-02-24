#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
using namespace std;

int merge(vector<int> &v, int low, int mid, int high){
	int alow = low, blow = mid;
	vector<int> v_sorted;
	int inv_count = 0;
	while (alow<mid&&blow<high){
		if (v[alow] <= v[blow])
			v_sorted.emplace_back(v[alow++]);
		else{
			v_sorted.emplace_back(v[blow++]);
			inv_count += mid - alow;//elements from v[alow:mid-1]
		}
	}
	copy(v.begin() + alow, v.begin() + mid, back_inserter(v_sorted));
	copy(v.begin() + blow, v.begin() + high, back_inserter(v_sorted));
	copy(v_sorted.begin(), v_sorted.end(), v.begin() + low);

	return inv_count;
}
int count_inversion(vector<int> &v, int low, int high){
	if (low<high - 1){
		int mid = low + ((high - low) >> 1);
		return count_inversion(v, low, mid) + count_inversion(v, mid, high) + merge(v, low, mid, high);
	}
	else
		return 0;//last index==first index=>no inversion
}
int main(void){
	vector<int> v{ 4, 3, 2, 1, 0 };//ans should be 10
	cout << count_inversion(v, 0, v.size()) << endl;
	int inp;
	cin >> inp;
	return 0;
}
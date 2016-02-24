#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
using namespace std;

template <typename X>
void xSwap(X &a, X &b){
	X t = a;
	a = b;
	b = t;
}

//largest sum subarray
pair<int, int> maxSumSubArr(vector<int> v){
	int cur_sum = v[0], max_sum = v[0], start = 0, end = 0;
	pair<int, int> ret{ -1, -1 };
	//The idea is to compare running sum + present term(A), present term (B); if A<B, discard A and B becomes new running sum
	for (int i = 1; i<v.size(); ++i){
		if (cur_sum + v[i]<v[i]){
			start = end = i;
			cur_sum = v[i];
		}
		else{
			end = i;
			cur_sum += v[i];
		}
		if (cur_sum>max_sum){
			max_sum = cur_sum;
			ret.first = start;
			ret.second = end;
		}
	}
	return ret;
}
int main(void){
	vector<int> v{ -4, 30, 22, -11, 12, -50, 90, -2, -20, 21, -25, -111, 0, 0, 0, 88, 45, 23, -22 };
	pair<int, int> r = maxSumSubArr(v);
	cout << r.first << " " << r.second << endl;
	copy(v.begin() + r.first, v.begin() + r.second + 1, ostream_iterator<int>(cout, " "));
	int sum = 0;
	for (int i = r.first; i <= r.second; ++i)
		sum += v[i];
	cout << endl << "Sum:" << sum << endl;


	int inp;
	cin >> inp;
	return 0;
}
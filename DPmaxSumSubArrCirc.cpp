// Example program
#include <iostream>
#include <string>
#include<deque>
#include<algorithm>
#include<vector>
using namespace std;
int max_sum_lin(vector<int> v){
	int cur_sum = v[0], max_sum = v[0], cur_b = 0, cur_e = 0, max_b = 0, max_e = 0;
	for (int i = 1; i < v.size(); ++i){
		if (cur_sum + v[i] < v[i]){//end of summation run
			cur_b = cur_e = i;//mark new beginings;
			cur_sum = v[i];
		}
		else{
			cur_sum += v[i];
			cur_e = i;
		}
		if (max_sum < cur_sum){
			max_sum = cur_sum;
			max_b = cur_b;
			max_e = cur_e;
		}

	}
	return max_sum;
}
int max_sum_cir(vector<int> v){
	int sum = v[0];
	vector<int> a(v.size());
	a[0]=sum;
	for (int i = 1; i < v.size(); ++i){
		sum += v[i];
		a[i]=max(sum, a[i-1]);
		//a[i] = max(sum, a[i - 1]);
	}
	vector<int> b(v.size());
	b.back()=0;
	sum = 0;
	for (int i = v.size() - 2; i >= 0; --i){
		sum += v[i+1];
		b[i] = max(sum, b[i + 1]);
	}
	int max_so_far = numeric_limits<int>::min();
	for (int i = 0; i < v.size(); ++i){
		max_so_far = max(max_so_far, a[i] + b[i]);
	}
	/*for (int i = 0; i < a.size(); ++i)
		cout << a[i] << " ";
	cout << endl;
	for (int i = 0; i < b.size(); ++i)
		cout << b[i] << " ";
	cout << endl;*/
	return max_so_far;
}

int main()
{
	vector<int> v{ 100, 200, -300, -300, -300, 1200, -1000, 400 };
	cout << "Lin MaxSum: " << max_sum_lin(v) << endl;
	cout << "Lin CirSum: " << max_sum_cir(v) << endl;
	cout << max(max_sum_cir(v), max_sum_lin(v)) << endl;
	int in;
	cin >> in;
	return 0;

}

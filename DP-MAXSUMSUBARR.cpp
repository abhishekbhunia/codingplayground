#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
#include<limits>
using namespace std;

//largest sum subarray
pair<int, int> maxSumSubArr(vector<int> v){
	int cur_sum = v[0], max_sum = v[0], start = 0, end = 0;
	pair<int, int> ret{ -1, -1 };
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
int maxSumLin(vector<int> &v){
	int maxSum = v[0], runSum = v[0];
	//cout << "runsum:" << runSum << " maxSum:" << maxSum << endl;
	for (int i = 1; i < v.size(); ++i){
		runSum = max(v[i], v[i] + runSum);

		maxSum = max(maxSum, runSum);
		//cout << "runsum:" << runSum << " maxSum:" << maxSum << endl;
	}
	return maxSum;
}
int maxSumCirc(vector<int> &v){
	vector<int> left;
	left.push_back(v[0]);
	int sumleft = v[0];
	cout << "left:" << left.back() << " ";
	for (int i = 1; i<v.size(); ++i){
		sumleft += v[i];
		left.push_back(max(sumleft, left.back()));
		cout << "left:" << left.back() << " ";
	}
	cout << endl;
	vector<int> right(v.size());
	right.back() = 0;
	int sumright = 0;
	cout << "right:" << right.back() << " ";
	for (int i = right.size() - 2; i >= 0; --i){
		sumright += v[i + 1];
		right[i] = max(right[i + 1], sumright);
		cout << "right:" << right[i] << " ";
	}
	cout << endl;
	int ret = numeric_limits<int>::min();
	for (int i = 0; i<v.size(); ++i){
		ret = max(ret, left[i] + right[i]);
		cout << "ret:" << ret << " ";
	}
	cout << endl;
	return ret;
}
int main(void){
	vector<int> v{ -4, 30, 22, -11, 12, -50, 90, -2, -20, 21, -25, -111, 0, 0, 0, 88, 45, 23, -22 };
	pair<int, int> r = maxSumSubArr(v);
	//cout << r.first << " " << r.second << endl;
	//copy(v.begin() + r.first, v.begin() + r.second + 1, ostream_iterator<int>(cout, " "));
	int sum = 0;
	for (int i = r.first; i <= r.second; ++i)
		sum += v[i];
	//cout << endl << "Sum:" << sum << endl;
	//cout << "LinSum:" << maxSumLin(v) << endl;

	vector<int> v2{ -11, 0, 0, -55,111, 0, 0, 44 };
	cout << maxSumCirc(v2) << endl;

	int inp;
	cin >> inp;
	return 0;
}
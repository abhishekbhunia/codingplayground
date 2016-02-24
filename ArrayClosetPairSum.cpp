#include<iostream>
#include<vector>
#include<functional>
#include<algorithm>
#include<map>
#include<stack>
using namespace std;
#define pnl cout<<endl
template<typename X>
void pv(vector<X> v){
	for (int i = 0; i < v.size(); ++i)
		cout << v[i] << " ";
	pnl;
}
//find 'pair sum' closest to x in a sorted array
pair<int,int> closePairSum(vector<int> v, int x){
	int diff = numeric_limits<int>::max();
	int res_l = -1, res_r = -1, l = 0, r = v.size() - 1;
	while (l < r){
		if (abs(v[l] + v[r] - x) < diff){
			res_l = l;
			res_r = r;
			diff = abs(v[l] + v[r] - x);
		}
		if (v[l] + v[r]>x)
			r--;
		else
			l++;
	}
	return{ res_l, res_r };
}
pair<int, int> closePairSumTwoArr(vector<int> v1, vector<int> v2, int x){
	int l = 0, r = v2.size() - 1;
	int res1 = -1, res2 = -1;
	int diff = numeric_limits<int>::max();
	while ( l<v1.size() && r>=0 ){
		if (abs(v1[l] + v2[r] - x) < diff){
			diff = abs(v1[l] + v2[r] - x);
			res1 = l;
			res2 = r;
		}
		if (v1[l] + v2[r] > x)
			r--;
		else
			l++;
	}
	return{ res1, res2 };
}

void merge(vector<int> a, vector<int> b, vector<int> &c, vector<bool> &vflag){
	int alow = 0, blow = 0, ahigh = a.size() - 1, bhigh = b.size() - 1;
	int i = 0;
	while (alow <= ahigh&&blow <= bhigh){
		if (a[alow] <= b[blow]){
			c[i] = a[alow++];
			vflag[i] = true;
			i++;
		}
		else{
			c[i] = b[blow++];
			vflag[i] = false;
			i++;
		}
	}
	while (alow <= ahigh){
		c[i] = a[alow++];
		vflag[i] = true;
		i++;
	}
	while (blow <= bhigh){
		c[i] = b[blow++];
		vflag[i] = false;
		i++;
	}
	pv(c);
}
int closePairSumTwoArrMerge(vector<int> v1, vector<int> v2, int x){
	//this one uses the merge procedure
	//bool *vflag = new bool[v1.size() + v2.size()];//true->v1,false->v2
	vector<bool> vflag(v1.size() + v2.size());
	vector<int> c(v1.size() + v2.size());
	merge(v1, v2, c, vflag);
	pv(vflag);
	int l = 0, r = c.size() - 1, ret_l=-1, ret_r=-1, diff=numeric_limits<int>::max();
	//binary search in merged array
	while (l<r){
		if ((abs(c[l] + c[r] - x) < diff) && ((vflag[l] && !vflag[r]) || (!vflag[l] && vflag[r]))){
			ret_l = l;
			ret_r = r;
			diff = abs(c[l] + c[r] - x);
		}
		if (c[l] + c[r] > x)
			r--;
		else
			l++;
	}
	if (ret_l != -1 && ret_r != -1)
		return c[ret_l] + c[ret_r];
	else
		return numeric_limits<int>::min();
}
int main(){
	vector<int> v{ 10, 22, 28, 29, 30, 40 };
	auto ret = closePairSum(v, 54);
	if (ret.first != -1)
		cout << "Index 1:" << ret.first << " Index 2:" << ret.second << " Sum:" << v[ret.first] + v[ret.second] << endl;

	vector<int> v1{ 1, 4, 5, 7 };
	vector<int> v2{ 10, 20, 30, 40 };
	ret = closePairSumTwoArr(v1, v2, 38);
	if (ret.first!=-1&&ret.second!=-1)
		cout << "Index 1(v1):" << ret.first << " Index 2(v2):" << ret.second << " Sum:" << v1[ret.first] + v2[ret.second] << endl;
	cout << "Using Merge:" << endl;

	vector<int> v3{ 1, 4, 20, 30 };
	vector<int> v4{ 5, 7, 10, 40 };
	int sum=closePairSumTwoArrMerge(v3, v4, 38);
	cout << " Sum:" << sum << endl;

	getchar();
}
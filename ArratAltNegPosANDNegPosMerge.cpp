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
void rrotate(vector<int> &v, int l, int r){
	int tmp = v[r];
	for (int i = r; i > l; --i){
		v[i] = v[i - 1];
	}
	v[l] = tmp;
}
void altNegPosStable(vector<int> &v){
	//O(n^2), O(1) storage, stable->maintains original order
	//1. even index = negative number, odd index = +ve number
	//2. for out of place index get the next element that's out of place and single right rotate
	//works for sorted/unsorted
	int outOfPlace = -1;
	for (int i = 0; i < v.size(); ++i){
		
		if (outOfPlace == -1){
			//if i is odd & v[i] is negative (and vice versa) mark out of place index and call rrotate
			if (((i & 1) && (v[i] < 0)) || (!(i & 1) && (v[i] >= 0))){
				outOfPlace = i;
			}
		}
		
		else{
			//rotate on first element with opposite sign
			if ((v[i] < 0 && v[outOfPlace] >= 0) || (v[i] >= 0 && v[outOfPlace] < 0)){
				rrotate(v, outOfPlace, i);
				if (i - outOfPlace > 2)
					outOfPlace += 2;
				else
					outOfPlace = -1;
			}			
		}
	}
}
void altNegPos(vector<int> &v){
	//this algorithm is not stable, +ve elements get re-ordered by partition
	//IDEA: Quicksort partition around 0, then swap with +ve half
	//O(n)
	int pivot = 0;
	int small = -1;
	for (int i = 0; i < v.size() && v.size()>1; ++i){
		if (v[i] < 0){
			small++;
			if (small != i){
				swap(v[i], v[small]);
			}
		}
	}
	if (small == -1 || small == v.size() - 1)
		return;
	int pos_s = small + 1, small_e = small, pos_e = v.size() - 1;
	//cout << "neg start:" << 0 << " neg end:" << small << " pos start:" << small + 1 << " pos end:" << v.size() - 1 << endl;
	//pv(v);
	for (int i = 0,j = pos_s; v[i]<0 && j<=pos_e; i+=2,++j){
		swap(v[i], v[j]);
	}
}
void reverse(vector<int> &v, int l, int r){
	while (l < r)
		swap(v[l++], v[r--]);
}
void merge(vector<int> &v, int l, int m, int r){
	int left=l,right=m+1;
	///int left_neg_end = l, right_neg_end = m+1;
	while (left <= m&&v[left] < 0){
		left++;
	}
	while (right <= r&&v[right] < 0){
		right++;
	}
	reverse(v, left, m);
	reverse(v, m + 1, right - 1);
	reverse(v, left, right - 1);
	
}
void altNegPosMergeHelper(vector<int> &v,int l,int r){
	if (l < r){
		int m = l + ((r - l) >> 1);
		altNegPosMergeHelper(v, l, m);
		altNegPosMergeHelper(v, m + 1, r);
		merge(v, l, m, r);
		//cout << "After Merge:"; pv(v);
	}
}
void NegPosMergeInPlace(vector<int> &v){
	if (v.size() <= 1)
		return;
	altNegPosMergeHelper(v, 0, v.size() - 1);
	//now v is stably partitioned into negatives followed by positives
	//TRY: alt neg-pos, stable, in place from here

}
void testAltNegPos(){
	vector<int> v1{ -1, 2, -3, 4, 5, 6, -7, 8, 9 };
	vector<int> v2{ -1, -2, -3, -4, -5, -6, -7, -8, -9 };
	vector<int> v3{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector<int> v4;
	
	cout << "-------TESTING ALT NEG-POS IN PLACE USING PARTITION(UNSTABLE)-----" << endl;
	cout << "Input Array:"; pv(v1);
	vector<int> v(v1.begin(), v1.end());
	altNegPos(v);
	cout << "Output Array:"; pv(v);
	v.clear();

	cout << "Input Array:"; pv(v2);
	v.insert(v.begin(),v2.begin(), v2.end());
	altNegPos(v);
	cout << "Output Array:"; pv(v);
	v.clear();

	cout << "Input Array:"; pv(v3);
	v.insert(v.begin(),v3.begin(), v3.end());
	altNegPos(v);
	cout << "Output Array:"; pv(v);
	v.clear();

	cout << "Input Array:"; pv(v4);
	v.insert(v.begin(),v4.begin(), v4.end());
	altNegPos(v);
	cout << "Output Array:"; pv(v);
	v.clear();
	
	//altNegPosStable
	cout << "-------TESTING ALT NEG-POS IN PLACE USING STABLE ROTATE-----" << endl;
	cout << "Input Array:"; pv(v1);
	v.insert(v.begin(), v1.begin(), v1.end());
	altNegPosStable(v);
	cout << "Output Array:"; pv(v);
	v.clear();

	cout << "Input Array:"; pv(v2);
	v.insert(v.begin(), v2.begin(), v2.end());
	altNegPosStable(v);
	cout << "Output Array:"; pv(v);
	v.clear();

	cout << "Input Array:"; pv(v3);
	v.insert(v.begin(), v3.begin(), v3.end());
	altNegPosStable(v);
	cout << "Output Array:"; pv(v);
	v.clear();

	cout << "Input Array:"; pv(v4);
	v.insert(v.begin(), v4.begin(), v4.end());
	altNegPosStable(v);
	cout << "Output Array:"; pv(v);
	v.clear();
}
void testNegPos(){
	vector<int> v1{ -1, 2, -3, 4, 5, 6, -7, 8, 9 };
	vector<int> v2{ -1, -2, -3, -4, -5, -6, -7, -8, -9 };
	vector<int> v3{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector<int> v4;
	
	cout << "-------TESTING NEG|POS IN PLACE USING MERGE-----" << endl;
	cout << "Input Array:"; pv(v1);
	vector<int> v(v1.begin(), v1.end());
	NegPosMergeInPlace(v);
	cout << "Output Array:"; pv(v);
	v.clear();

	cout << "Input Array:"; pv(v2);
	v.insert(v.begin(), v2.begin(), v2.end());
	NegPosMergeInPlace(v);
	cout << "Output Array:"; pv(v);
	v.clear();

	cout << "Input Array:"; pv(v3);
	v.insert(v.begin(), v3.begin(), v3.end());
	NegPosMergeInPlace(v);
	cout << "Output Array:"; pv(v);
	v.clear();

	cout << "Input Array:"; pv(v4);
	v.insert(v.begin(), v4.begin(), v4.end());
	NegPosMergeInPlace(v);
	cout << "Output Array:"; pv(v);
	v.clear();
}
int main(){
	//testNegPos();
	testAltNegPos();
	getchar();
}
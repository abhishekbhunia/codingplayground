// Length of LIS nlogn
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
int bsearch_max_less(vector<int> v, int l, int r, int key){//max elem < key
	int ret = -1;
	while (l<r){
		int m = l + ((r - l) >> 1);
		if (key <= v[m])
			r = m;
		else{
			l = m + 1;
			ret = m;
		}
	}
	return ret;
}
int bsearch_min_more(vector<int> v, int l, int r, int key){//max elem < key
	int ret = -1;
	while (l<r){
		int m = l + ((r - l) >> 1);
		if (key < v[m]) {
			ret = m;
			r = m;
		}
		else{
			if (key == v[m])
				ret = r;
			l = m + 1;
		}
	}
	return ret;
}

void pv(vector<int> v){
	for (int i = 0; i<v.size(); ++i)
		cout << v[i] << " ";
	cout << endl;
}
int LIS(vector<int> v){
	vector<int> temp(v.size(), 0);//each index stores the end of the LIS of length==index+1
	int nextfree = 1;
	temp[0] = v[0];
	for (int i = 1; i < v.size(); ++i){
		if (v[i] < temp[0]){
			temp[0] = v[i];
			cout << "case 1: v[" << i << "](" << v[i] << ") < temp[0](" << temp[0] << ")" << endl;
			pv(temp);
		}
			
		else if (v[i] > temp[nextfree - 1]){
			cout << "case 2: v[" << i << "](" << v[i] << ") > temp[nextfree-1](" << temp[nextfree-1] << ")" << endl;
			temp[nextfree++] = v[i];
			pv(temp);
		}
			
		else{
			cout << "case 3: searching " << v[i] << endl;
			pv(temp);
			
			int max_less = bsearch_max_less(temp, 0, nextfree - 1, v[i]);
			cout << "returned index:" << max_less << endl;
			temp[max_less+1] = v[i];
			pv(temp);
		}
	}
	
	return nextfree;
}
int main()
{
	vector<int> v{ 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 }; 
	vector<int> v2{ 2, 5, 3, 7, 11, 8, 10, 13, 6 };
	cout << LIS(v)<<endl<<LIS(v2);
	getchar();
}

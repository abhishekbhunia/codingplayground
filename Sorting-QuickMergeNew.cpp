//1. Mergesort with inversion count

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
void merge(vector<int> &v, int l, int m, int r, int &invcount){
	int alow = l, ahigh = m, blow = m + 1, bhigh = r;
	
	vector<int> temp(r - l + 1);
	//cout << "alow:" << alow << " ahigh:" << ahigh << " blow:" << blow << " bhigh:" << bhigh << " tsize:"<<temp.size()<<endl;
	int start = 0;
	while (alow <= ahigh&&blow <= bhigh){
		if (v[alow] <= v[blow]){
			temp[start++] = v[alow++];
		}
		else{//inversion: v[alow]>v[blow]
			invcount += (ahigh - alow + 1);
			temp[start++] = v[blow++];
		}
	}
	
	while (alow <= ahigh){
		temp[start++] = v[alow++];
	}
	
	while (blow <= bhigh){
		temp[start++] = v[blow++];
	}

	//cout << "temp:"; pv(temp);
	alow = l, start = 0;
	while (alow <= bhigh)
		v[alow++] = temp[start++];
	//cout << "v:"; pv(v);
}
void mergesort(vector<int> &v, int l, int r, int &invcount){
	if (l < r){
		int m = l + ((r - l) >> 1);
		mergesort(v, l, m, invcount);
		mergesort(v, m+1, r, invcount);
		merge(v, l, m, r, invcount);
	}
}
int main(){
	vector<int> v1{ 1, 20, 6, 4, 5 };
	vector<int> v2{ 3, 4, 6, 1, 2, 5 };
	int invcount = 0, invcount2 = 0;
	pv(v1);
	mergesort(v1, 0, v1.size()-1, invcount);
	pv(v1);
	cout << "Inversions(v1):" << invcount; pnl;

	pv(v2);
	mergesort(v2, 0, v2.size() - 1, invcount2);
	pv(v2);
	cout << "Inversions(v2):" << invcount2; pnl;
	getchar();
}
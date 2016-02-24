#include<iostream>
#include<vector>
using namespace std;

int bsearch(vector<int> M, vector<int> v, int i, int L){
	//M has sorted end indeces of A, of sorted prefix length j
	//search for 'highest' M index(<=L obvious) which gives an A index and A[index]<=A[i]
	//highest because we are interested in increasing prefix length

	//v[M[i]] will be sorted because M is extended in that way
	int l = 0, r = L - 1;
	while (l <= r){
		int m = l + ((r - l) >> 1);
		if (v[M[m]] <= v[i]){
			l = m + 1;
		}
		else
			r = m - 1;
	}
	return r;
}
int linsearch(vector<int> M, vector<int> v, int i, int L){
	int l=0, r = L-1;
	int ret = -1;
	for(int x=l;x<=r;++x){
		if(v[M[x]]<=v[i])
			ret = x;
	}
	return ret;
}
void pv(vector<int> v){
	for (int i = 0; i<v.size(); ++i)
		cout << v[i] << " ";
	cout << endl;
}
vector<int> LIS(vector<int> v){
	vector<int> M(v.size());
	vector<int> P(v.size());
	M[0] = 0;
	P[0] = -1;
	int L = 1;

	for (int i = 1; i<v.size(); ++i){
		//binary search for largest index j in M such that A[M[j]]<A[i]
		int j = bsearch(M, v, i, L);
		int j2 = linsearch(M, v, i, L);
		cout<<"j:"<<j<<" j2:"<<j2<<endl;
		//set Predecessor index
		if (j != -1)
			P[i] = M[j];
		else
			P[i] = -1;//this happens when all elements are > A[i]
		//update M
		if (j == L - 1 || v[i]<v[M[j + 1]]){//second condition is for storing minimum end value
			M[j + 1] = i;
			if (j + 2>L)
				L = j + 2;
		}
	}
	//construct LIS
	vector<int> ret(L);

	int pred = M[L - 1];
	for (int i = L - 1; i >= 0; --i){
		ret[i] = v[pred];
		pred = P[pred];
	}
	cout << "LIS size:" << ret.size() << endl;
	return ret;
}
int main(){
	vector<int> v{ 2, 5, 3, 7, 11, 8, 10, 13, 6 };
	pv(LIS(v));	
	getchar();
}
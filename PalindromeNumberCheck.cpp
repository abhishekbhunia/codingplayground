#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define pnl cout<<endl

bool cnpRecurHelper(int num, int &ref){
	if (num >= 0 && num <= 9) 
		return (num == ref % 10);
	
	if (!cnpRecurHelper(num/10, ref))
		return false;
	ref /= 10;
	return (num % 10 == ref % 10);
}
bool cnpRecur(int num){
	if (num < 0)
		num = -num;
	int ref = num;
	return cnpRecurHelper(num, ref);
}
bool cnpIter(int num){
	if (num == 0)
		return true;

	if (num < 0)
		num = -num;
	int tnum = num;
	int ret = 0;
	while (num > 0){
		ret = ret * 10 + num % 10;
		num /= 10;		
	}
	
	return (ret == tnum);
}
int main(){
	vector<int> v{ 1221, 0, 432, -456654, 88889, 8 };//1,1,0,1,0,1
	for (int &i : v)
		cout << cnpIter(i) << " ";
	pnl;
	for (int &i : v)
		cout << cnpRecur(i) << " ";
	getchar();
}
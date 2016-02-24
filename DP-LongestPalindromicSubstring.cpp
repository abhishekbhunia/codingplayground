//longest palindromic string
#include<iostream>
#include<string>
#include<vector>
using namespace std;
string pp(string s){//TIme,Spce: N^2
	int len = s.length();
	vector<vector<bool>> lookup;
	int longestbegin = 0, maxlen = 1;
	for (int i=0; i < len; ++i){
		lookup.push_back(vector<bool>(len, false));
	}
	
	//strings of lengthh 1 are palindrome
	for (int i = 0; i < len; ++i)
		lookup[i][i] = true;

	//setting true palindromes for length 2
	for (int i = 0; i < len - 1; ++i){
		if (s[i] == s[i + 1]){
			longestbegin = i;
			maxlen = 2;
			lookup[i][i + 1] = true;
		}			
	}
	//for palindromes of length>=3
	for (int k = 3; k <= len; ++k){
		//for a palindrome length k, how many contiguous subarrays are possible?
		for (int i = 0; i < len - k + 1; ++i){
			//set the end index
			int j = i + k - 1;
			if (s[i] == s[j] && lookup[i + 1][j - 1]){
				lookup[i][j] = true;
				maxlen = k;// j - i + 1;
				longestbegin = i;
			}				
		}
	}
	return s.substr(longestbegin, maxlen);
}
string expand(string s, int l, int h){
	while (l >= 0 && h <= s.length() - 1 && s[l] == s[h]){
		l--;
		h++;
	}
	return s.substr(l + 1, h - l - 1);
}
string pp2(string s){//TIme: N^2, Space: 1
	if (s.length() <= 0)
		return "";
	string longest = s.substr(0, 1);
	int len = s.length();
	for (int i = 0; i < len - 1; ++i){
		string s1 = expand(s, i, i);//palidrome centre is an element(odd length)
		longest = (s1.length() > longest.length()) ? s1 : longest;

		string s2 = expand(s, i, i + 1);//palindrome centre is between two elements(even length)
		longest = (s2.length() > longest.length()) ? s2 : longest;
	}
	return longest;
}
int main(void){
	cout<<pp("engrgnpopnobhthbonl")<<endl;
	cout << pp2("engrgnpopnobhthbonl") << endl;
	
	int inp;
	cin >> inp;
	return 0;
}

 
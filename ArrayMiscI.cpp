//1.
//intersection of three sorted arrays TC=O(n1+n2+n3)
//chain binary search is only useful if L(a1)<<<L(a2)<<<L(a3)
void intersection3sorted(vector<int> v1, vector<int> v2, vector<int> v3, vector<int> &ret){
	int e1 = v1.size() - 1, e2 = v2.size() - 1, e3 = v3.size() - 1;
	int b1 = 0, b2 = 0, b3 = 0;
	
	while (b1 <= e1&&b2 <= e2&&b3 <= e3){
		if (v1[b1] == v2[b2] && v2[b2] == v3[b3]){
			ret.push_back(v1[b1]);
			b1++; b2++; b3++;
		}
		else if (v1[b1] < v2[b2])
			b1++;
		else if (v2[b2] < v3[b3])
			b2++;
		else b3++;
	}
}
//2. TwoSum in an array
bool twoSumArr1(vector<int> v, int x){
	//uses hash_table, doesn't need sorted array
	//O(n) time and space
	unordered_map<int, int> mp;
	int res = -1, ok = false;
	//x=13, 8->5, 5->8
	for (int i = 0; i < v.size(); ++i){
		if (x - v[i] > 0){
			auto it = mp.find(x - v[i]);
			if (it == mp.end())
				mp[v[i]] = v[i];
			else{
				ok = true;
				res = v[i];
				break;
			}
		}
		
	}
	if (ok){
		cout << "TwoSum(HT) found: " << res << " " << x - res << endl;
	}
	else
		cout << "TwoSum(HT) NOT found" << endl;
	return ok;
}
bool twoSumArr2(vector<int> v, int x){
	//assumes sorted array O(n) time O(1) space
	int l = 0, r = v.size() - 1;
	bool ok = false;
	int n1 = -1, n2 = -1;
	while (l < r){
		if (v[l] + v[r] == x){
			ok = true;
			break;
		}
		else if (v[l] + v[r] > x)
			r--;
		else
			l++;
	}
	if (ok)
		cout << "TwoSum(Sorted, Search from two ends) found: " << v[l] << " " << v[r] << endl;
	else
		cout << "TwoSum(Sorted, Search from two ends) NOT found" << endl;
	return ok;
}
void test_twoSumArr(){
	vector<int> v{ 1, 4, -6, 6, 10, 8 };
	twoSumArr1(v,16);
	sort(v.begin(), v.end());
	twoSumArr2(v,16);
}
//3. Add two numbers in digit representation
void addTwoNum(){
	//vector<int> v{ 1, 2, 3 }, v2{ 9, 5, 9 };
	//vector<int> v{ 9,9,9 }, v2{  };
	vector<int> v{ 9,9,9 }, v2{ 1 };
	int size1 = v.size(), size2 = v2.size();
	vector<int> res;
	int carry = 0, i, j;
	for (i = size1-1, j = size2-1; i >= 0 && j >= 0; i--, j--){
		
		int sum = (v[i] + v2[j] + carry)%10;		
		carry = (v[i] + v2[j] + carry) / 10;		
		res.insert(res.begin(), sum);
	}
	while (i >= 0){
		int sum = (carry + v[i])%10;
		carry = (carry + v[i]) / 10;
		res.insert(res.begin(), sum);
		i--;
	}
	while (j >= 0){
		int sum = (carry + v[j]) % 10;
		carry = (carry + v[j]) / 10;
		res.insert(res.begin(), sum);
		j--;
	}
	if (carry)
		res.insert(res.begin(), carry);
	pv(v); pv(v2); pv(res);
}
//4. Wave Sort(2 methods)
void arrInWave(){
	//O(n) time
	vector<int> v{ 10, 90, 49, 2, 1, 5, 23 };
	pv(v);
	for (int i = 0; i < v.size(); i += 2){
		if (i>0 && v[i] < v[i - 1])
			swap(v[i], v[i - 1]);
		if (i < v.size() - 1 && v[i] < v[i + 1])
			swap(v[i], v[i + 1]);
	}
	pv(v);
}
void arrInWaveSort(){
	//TC O(nlogn) for sorting [ O(n) for traversing and swapping ]
	//Not good, simple wave is much better O(n)
	vector<int> v{ 10, 90, 49, 2, 1, 5, 23 };
	pv(v);
	sort(v.begin(), v.end());
	
	for (int i = 0; i < v.size() - 1 ; i+=2){
		swap(v[i], v[i + 1]);
	}
	pv(v);
}
//5. Search in a 2D matrix sorted by row and column
pair<int,int> searchIn2DsortedMat(vector<vector<int>> v,int key){
	//TC: O(n)
    int i=0, j=v[0].size()-1;
    while(j>=0&&i<v[0].size()){
        if(v[i][j]==key)
            return {i,j};
        else if(v[i][j]>key)
            j--;
        else
            i++;
    }
    return {-1,-1};
}
test_2dsortMatsearch(){
    vector<vector<int>> v;
    v.insert(v.end(),{10, 20, 30, 40});
    v.insert(v.end(),{15, 25, 35, 45});
    v.insert(v.end(),{27, 29, 37, 48});
    v.insert(v.end(),{32, 33, 39, 50});
     
    pair<int,int> ret{-1,-1};
    int key=29;
    ret=searchIn2DsortedMat(v,29);
    cout<<ret.first<<" "<<ret.second<<endl;
}
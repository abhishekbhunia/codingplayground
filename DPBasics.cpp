//0. Edit Distance - the easiest
int editDistRec(string src, string dst, int slen, int dlen){
	if (slen == 0)
		return dlen;
	if (dlen == 0)
		return slen;
	if (src[slen-1] == dst[dlen-1])
		return editDistRec(src, dst, slen - 1, dlen - 1);
	return 1 + min(editDistRec(src, dst, slen, dlen - 1), min(editDistRec(src, dst, slen - 1, dlen), editDistRec(src, dst, slen - 1, dlen - 1)));
}
int editDistDP(string src, string dst, int slen, int dlen){
	vector<vector<int>> dp(slen + 1, vector<int>(dlen + 1));
	for (int i = 0; i <= slen; ++i){
		for (int j = 0; j <= dlen; ++j){
			if (i == 0)
				dp[i][j] = j;
			else if (j == 0)
				dp[i][j] = i;
			else if (src[i - 1] == dst[j - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else
				dp[i][j] = 1 + min(dp[i][j - 1], min(dp[i - 1][j], dp[i - 1][j - 1]));
		}
	}
	return dp[slen][dlen];
}
void test_editDist(){
	string s1 = "sunday", s2 = "saturday";
	cout << "Rec:" << editDistRec(s1, s2, s1.length(), s2.length()) << " DP:" << editDistDP(s1, s2, s1.length(), s2.length()) << endl;
}
//1. 0/1 Knapsack
int knapsack_rec(int n, int w, int *val, int *wt){
	if (n == 0 || w == 0)
		return 0;
	if (w < wt[n - 1])
		return knapsack_rec(n - 1, w, val, wt);
	else
		return max(val[n - 1] + knapsack_rec(n - 1, w - wt[n - 1], val, wt), knapsack_rec(n - 1, w, val, wt));
}
int knapsack_dp(int n, int w, int *val, int *wt){
	//item 0 and w 0 adds one more dimension
	vector<vector<int>> dpv(n + 1, vector<int>(w + 1));
	for (int i = 0; i <= n; ++i){
		for (int j = 0; j <= w; ++j){
			if (i == 0 || j == 0)
				dpv[i][j] = 0; 
			else if (wt[i - 1]>w)//if weight of this item is grater than required, drop it
				dpv[i][j] = dpv[i - 1][j];
			else//else take the max of including and excluding it
				dpv[i][j] = max(val[i - 1] + dpv[i - 1][w - wt[i - 1]], dpv[i - 1][j]);
		}
	}
	/*for (int i = 0; i <= n; ++i){
		for (int j = 0; j <= w; ++j)
			cout << dpv[i][j] << " ";
		cout << endl;
	}*/
	return dpv[n][w];
}
void test_knapsack(){
	int val[] = { 60, 100, 120 };
	int wt[] = { 10, 20, 30 };
	int W = 30, N = 3;	
	cout << "Recursive:"<< knapsack_rec(N, W, val, wt) << " DP:"<<knapsack_dp(N,W,val,wt);

}
//2. Binomial Coefficient
int binco_rec(int n, int m){
	if (m == n || m == 0)
		return 1;
	return binco_rec(n - 1, m - 1) + binco_rec(n - 1, m);
}
int binco_dp(int n, int m){
	vector<vector<int>> dp(n+1, vector<int>(m+1));
	for (int i = 0; i <= n; ++i){
		for (int j = 0; j <= m && j <= i; ++j){
			if (i == j || j == 0 )
				dp[i][j] = 1;
			else
				dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
		}
	}
	return dp[n][m];
}
void test_binco(){
	//recurrance: C(n,m) = C(n-1,m-1) + C(n-1,m)
	//base case: C(n,n) = C(n,0) = 1
	int n = 4, m = 2;
	cout << "Recursive:" << binco_rec(n, m) << " DP:" << binco_dp(n, m) << endl;
}
//3. Rod Cutting TOUGH
int rodCut(vector<int> &price, int n){
	if (n == 0)
		return 0;
	int maxV = numeric_limits<int>::min();
	for (int i = 0; i < n; ++i){		
		maxV = max(maxV, price[i] + rodCut(price, n - i - 1));
	}
	return maxV;
}
int rodCutDP(vector<int> &price, int n){
	vector<int> dp(price.size() + 1);
	dp[0] = 0;//price of len 0 is 0
	for (int i = 1; i <= n; ++i){
		int maxV = numeric_limits<int>::min();
		for (int j = 0; j < i; ++j){
			maxV = max(maxV, price[j] + dp[i - j - 1]);
		}
		dp[i] = maxV;
	}
	return dp[n];
}
void test_rodCut(){
	vector<int> price{ 1, 5, 8, 9, 10, 17, 17, 20 };
	cout << "Recursive:" << rodCut(price, price.size()) << " DP:" << rodCutDP(price, price.size());
}
//4. Coin Change Easy
int coinChangeRec(int amt, int index, vector<int> &val){
	if (amt == 0)
		return 1;
	if (amt<0)
		return 0;
	if (amt >= 1 && index <= 0)
		return 0;
	return coinChangeRec(amt - val[index - 1], index, val) + coinChangeRec(amt, index - 1, val);
}
int coinChangeDP(int amt, int index, vector<int> &val){
    vector<vector<int>> dp(amt+1,vector<int>(index));
    for(int i=0;i<index;++i)
        dp[0][i]=1;
    
    for(int i=1;i<=amt;++i){
        int x,y;
        for(int j=0;j<index;++j){
            //count included
            x=(i>=val[j])?dp[i-val[j]][j]:0;
            //count excluded
            y=(j>=1)?dp[i][j-1]:0;
            
            dp[i][j]=x+y;
        }
        
    }
    
    return dp[amt][index-1];
}
void test_coinChange(){
	vector<int> denom{ 2, 5, 3, 6 };
	int change = 10;
	cout << coinChangeRec(change, denom.size(), denom) << endl;
	cout << coinChangeDP(change, denom.size(), denom) << endl;
}
//5. Longest Palindromic Subsequence
int lps_dp(string &s){
	int n = s.length();
	vector<vector<int>> dp(n, vector<int>(n));
	cout << s << endl;
	for (int i = 0; i < n; ++i){		
			dp[i][i] = 1;
	}
	//loop is a bit different and intuitive
	for (int col = 2; col <= n; ++col){
		for (int i = 0; i < n-col+1; ++i){
			int j = i + col - 1;
			
			if (s[i] == s[j] && j == i + 1)
				dp[i][j] = 2;
			else if (s[i] == s[j])
				dp[i][j] = dp[i + 1][j - 1] + 2;
			else
				dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
		}
	}
	
	return dp[0][n-1];
}
int lps_rec(string &s, int low, int high){
	if (low == high)
		return 1;
	if (s[low] == s[high] && high - low == 1)
		return 2;
	if (s[low] == s[high])
		return lps_rec(s, low + 1, high - 1) + 2;
	return max(lps_rec(s, low, high - 1), lps_rec(s, low + 1, high));
}
void test_longest_pal_sub(){
	string s = "GEEKSFORGEEKS";
	cout << "Recursive:" << lps_rec(s, 0, s.size()-1) << " DP:" << lps_dp(s) << endl;
}
//6. Subset Sum
bool subsetSumRec(vector<int> &v, int index, int sum){
	if (sum == 0)
		return true;
	if (index == 0 && sum != 0)
		return false;
	if (v[index - 1]>sum)
		return subsetSumRec(v, index - 1, sum);
	return subsetSumRec(v, index - 1, sum - v[index - 1]) || subsetSumRec(v, index - 1, sum);
}
bool subsetSumDP(vector<int> &v, int sum, int len){
	vector<vector<bool>> dp(sum + 1, vector<bool>(len + 1));
	for (int i = 0; i <= len; ++i)
		dp[0][i] = true;
	for (int i = 0; i <= sum; ++i)
		dp[i][0] = false;
	for (int i = 1; i <= sum; ++i){
		for (int j = 1; j <= len; ++j){
			if (v[j - 1] > i)
				dp[i][j] = dp[i][j - 1];
			else
				dp[i][j] = dp[i - v[j - 1]][j - 1] || dp[i][j - 1];
		}
	}
	return dp[sum][len];
}
void test_subsetSum(){
	vector<int> v{ 3, 34, 4, 12, 5, 2 };
	int sum = 9;
	cout << "Rec: " << subsetSumRec(v, v.size(), sum) << " DP:" << subsetSumDP(v, sum, v.size()) << endl;
}
//7. LIS
int liss_rec(vector<int> &v, int last_ind, int *gmax){
	if (last_ind == 0)
		return 1;
	int local_max = 1, ret_max;

	for (int i = 0; i < last_ind; ++i){
		ret_max = liss_rec(v, i, gmax);
		if (v[i]<v[last_ind] && ret_max + 1>local_max)
			local_max = ret_max + 1;
	}
	*gmax = max(*gmax, local_max);
	return local_max;
}
int liss_dp(vector<int> &v){
	vector<int> dp(v.size(), 1);
	for (int i = 0; i < v.size(); ++i){
		for (int j = 0; j < i; ++j){
			if (v[j]<v[i] && dp[j] + 1>dp[i])
				dp[i] = dp[j] + 1;
		}
	}
	pv(dp);
	int dpmax = 0;
	for (int i = 0; i < dp.size(); ++i){
		dpmax = max(dpmax, dp[i]);
	}
	/*-------FOR RECONSTRUCTING INCREASING SUBSEQUENCE--------------*/
	vector<int> ind;
	int tmp = dpmax;
	for (int i = dp.size() - 1; i >= 0; --i){
		if (dp[i] == tmp){
			ind.insert(ind.begin(), i);
			tmp--;
		}
			
	}
	cout << "ind size:" << ind.size() << endl;
	for (int &i : ind)
		cout << v[i] << " ";
	pnl;
	/*-------FOR RECONSTRUCTING INCREASING SUBSEQUENCE--------------*/
	return dpmax;
}
void test_LISsimple(){
	vector<int> v{ 10, 22, 9, 33, 21, 50, 41, 60 };
	int gmax = 1;
	//liss_rec(v, v.size() - 1, &gmax);
	//cout <<  gmax << endl;
	cout << liss_dp(v) << endl;
}

//8. Minimum Path Cost in 2D Matrix
int mincost2dRec(vector<vector<int>> &v, int row, int col){
	if (row <= 0 || col <= 0)
		return numeric_limits<int>::max();
	if (row == 1 && col == 1)
		return v[0][0];
	return v[row-1][col-1] + min(mincost2dRec(v, row, col - 1), min(mincost2dRec(v, row - 1, col - 1), mincost2dRec(v, row - 1, col)));
}
int mincost2dDP(vector<vector<int>> &v, int row, int col){
	vector<vector<int>> dp(row+1,vector<int>(col+1));
	for (int i = 0; i <= row; ++i)
		dp[i][0] = numeric_limits<int>::max();
	for (int i = 0; i <= col; ++i)
		dp[0][i] = numeric_limits<int>::max();
	for (int i = 1; i <= row; ++i){
		for (int j = 1; j <= col; ++j){
			if (i == 1 && j == 1)
				dp[i][j] = v[i - 1][j - 1];
			else
				dp[i][j] = v[i-1][j-1] + min(dp[i][j - 1], min(dp[i - 1][j - 1], dp[i - 1][j]));
		}
	}
	//cout << "DPARR:\n"; pv2d(dp);
	return dp[row][col];
}
void test_MinCost2D(){
	vector<vector<int>> v;
	v.insert(v.end(), { 1, 2, 3 });
	v.insert(v.end(), { 4, 8, 2 });
	v.insert(v.end(), { 1, 5, 3 });
	//cout << "Original:\n"; pv2d(v);
	cout << "Rec:" << mincost2dRec(v, v.size(), v.size()) << " DP:"<<mincost2dDP(v,v.size(),v.size())<<endl;
}

//1. Number of Islands

//A) Long Solution
bool isSafe(int xpos, int ypos, int vsize, vector<vector<int>> v){
	if ((xpos>=0 && xpos<vsize) && (ypos>=0 && ypos < vsize) && v[xpos][ypos] )
		return true;
	return false;
}
void dfsIsland(vector<vector<int>> v, vector<vector<bool>> &visited, int i, int j){
	static int xmove[8] = {-1,0,1,-1,1,-1,0,1};
	static int ymove[8] = {-1,-1,-1,0,0,1,1,1};
	visited[i][j] = true;
	for (int p = 0; p < 8; ++p){
		int newxp = i + xmove[p];
		int newyp = j + ymove[p];
		if (isSafe(newxp, newyp, v.size(), v) && !visited[newxp][newyp])
			dfsIsland(v, visited, newxp, newyp);
	}
}
int numIslands(vector<vector<int>> v, vector<vector<bool>> &visited){
	int cnt = 0;
	for (int i = 0; i < v.size(); ++i){
		for (int j = 0; j < v[i].size(); ++j){
			if (!visited[i][j]&&v[i][j]){
				cnt++;
				dfsIsland(v, visited, i, j);
			}
		}
	}
	return cnt++;
}
void test_numIslands(){
	vector<vector<int>> v;
	v.insert(v.end(), { 1, 1, 0, 0, 0 });
	v.insert(v.end(), { 0, 1, 0, 0, 1 });
	v.insert(v.end(), { 1, 0, 0, 1, 1 });
	v.insert(v.end(), { 0, 0, 0, 0, 0 });
	v.insert(v.end(), { 1, 0, 1, 0, 1 });
	vector<vector<bool>> visited(v.size(), vector<bool>(v.size(), false));
	pv2d(v);
	cout << numIslands(v,visited) << endl;
}
//B Short Solution
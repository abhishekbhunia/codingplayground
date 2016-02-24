#define N 8

void p2da(int arr[N][N]){
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j)
			cout << arr[i][j] << " ";
		cout << endl;
	}
}
bool isSafe(int maze[N][N], int x, int y){
	return ((x >= 0 && x < N && y >= 0 && y < N) && maze[x][y] == -1);
}
bool knightMoves(int sol[N][N], int start_x, int start_y, int newMoveNum, int xM[N], int yM[N]){
	//all it says is i have decided on sol for i with start_x/y now recurse/attempt for sol i+1
	//so get a safe next possible pos to store (i+1) and recurse till you need next possible move
	//that extends the solution space limit(base case)
	if (newMoveNum == N*N)
		return true;
		
	for (int k = 0; k < N; ++k){
		int next_x = start_x + xM[k];
		int next_y = start_y + yM[k];
		if (isSafe(sol, next_x, next_y)){
			//IMP
			sol[next_x][next_y] = newMoveNum;
			if (knightMoves(sol, next_x, next_y, newMoveNum + 1, xM, yM))
				return true;
			else
				sol[next_x][next_y] = -1;//IMP: DO NOT RETURN, try all recursive calls from this level
		}
	}
	
	return false;
}
void test_knightMoves(){
	int sol[N][N];
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j)
			sol[i][j] = -1;
	}
	
	sol[0][0] = 0;
	int xMove[N] = { 2, 1, -1, -2, -2, -1, 1, 2 };
	int yMove[N] = { 1, 2, 2, 1, -1, -2, -2, -1 };

	//all it says is i have decided on sol for i and recurse/attempt for sol i+1
	if (knightMoves(sol, 0, 0, 1, xMove, yMove)){
		cout << "Solution space found:" << endl;
		p2da(sol);
	}
	else
		cout << "dang!" << endl;
}
int main(){
	test_knightMoves();
	getchar();
}
#define N 4

void p2da(int arr[N][N]){
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j)
			cout << arr[i][j] << " ";
		cout << endl;
	}
}
bool isSafe(int maze[N][N], int x, int y){
	return ((x >= 0 && x < N && y >= 0 && y < N) && maze[x][y] == 1);
}
bool ratInMaze(int maze[N][N], int sol[N][N], int start_x, int start_y){
	if (start_x == N - 1 && start_y == N - 1){
		sol[start_x][start_y] = 1;
		return true;
	}
	if (isSafe(maze, start_x, start_y)){
		sol[start_x][start_y] = 1;
		if (ratInMaze(maze, sol, start_x + 1, start_y))
			return true;
		if (ratInMaze(maze, sol, start_x, start_y +1))
			return true;
		sol[start_x][start_y] = 0;
		return false;
	}
	return false;
		
}
void test_ratInMaze(){
	int maze[N][N] = { { 1, 0, 0, 0 },
						{ 1, 1, 0, 1 },
						{ 0, 1, 0, 0 },
						{ 1, 1, 1, 1 }
					};
	int sol[N][N] = { { 0, 0, 0, 0 },
						{ 0, 0, 0, 0 },
						{ 0, 0, 0, 0 },
						{ 0, 0, 0, 0 }
						};
	cout << "Maze:" << endl;
	p2da(maze);
	if (ratInMaze(maze, sol, 0, 0)){
		cout << "Rat Lives:" << endl;
		p2da(sol);
	}
		
	else
		cout << "The rat dies!" << endl;
}
int main(){
	test_ratInMaze();
	getchar();
}
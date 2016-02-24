//DFS, BFS, TopoSort, Cycle Detection
#include<iostream>
#include<vector>
#include<deque>
#include<algorithm>
#include<map>
#include<stack>
using namespace std;
#define pnl cout<<endl
void pv(vector<int> v){
	for (int i = 0; i < v.size(); ++i)
		cout << v[i] << " ";
	pnl;
}
struct graph{
	int vnum;
	bool *visited;
	vector<vector<int>> adj;
	graph(){}
	graph(int num) :vnum(num){
		visited = new bool[vnum];
		for (int i = 0; i < vnum; ++i)
			visited[i] = false;
		adj.resize(vnum);
	}
	void addEdge(int src, int dst){
		adj[src].push_back(dst);
	}
	void dfsUtil(int i){
		visited[i] = true;
		cout << "DFS visiting:" << i << endl;
		for (auto it = adj[i].begin(); it != adj[i].end(); ++it){
			if (!visited[*it])
				dfsUtil(*it);
		}
	}
	void dfs(){
		cout << "<---------------------DFS--------------------->" << endl;
		for (int i = 0; i < vnum; ++i){
			if (!visited[i])
				dfsUtil(i);
		}
		for (int i = 0; i < vnum; ++i)
			visited[i] = false;
	}
	void bfsUtil(int i){
		//set visited when inserting into queue (and print at the same time)
		deque<int> q;
		q.push_back(i);
		visited[i] = true;
		cout << "BFS visiting:" << i <<endl;
		while (!q.empty()){
			int front = q.front();
			for (auto it = adj[front].begin(); it != adj[front].end(); ++it){
				if (!visited[*it]){
					q.push_back(*it);
					visited[*it] = true;
					cout << "BFS visiting:" << *it << endl;
				}
			}
			q.pop_front();
		}
	}
	void bfs(){
		cout << "<---------------------BFS--------------------->" << endl;
		for (int i = 0; i < vnum; ++i){
			if (!visited[i])
				bfsUtil(i);
		}
		for (int i = 0; i < vnum; ++i)
			visited[i] = false;
	}
	void topoSortUtil(int i, stack<int> &s){
		visited[i] = true;
		for (auto it = adj[i].begin(); it != adj[i].end(); ++it){
			if (!visited[*it])
				topoSortUtil(*it, s);
		}
		//post-order push to stack
		s.push(i);
	}
	void topoSort(){
		cout << "<---------------------TOPOSORT--------------------->" << endl;
		stack<int> s;
		for (int i = 0; i < vnum; ++i){
			if (!visited[i])
				topoSortUtil(i, s);
		}
		for (int i = 0; i < vnum; ++i)
			visited[i] = false;
		cout << "TopoSort:";
		while (!s.empty()){
			cout << s.top() << " ";
			s.pop();
		}
		pnl;
	}
	bool isCycleHelper(int i, bool *trace){
		visited[i] = true;
		trace[i] = true;
		for (auto it = adj[i].begin(); it != adj[i].end(); ++it){
			if (!visited[*it] && isCycleHelper(*it, trace))
				return true;
			//if neighbour has exited dfs, trace[*it] should be false(due to post order trace reset); however if the neighbor
			//has ongoing dfs and this vertex is visiting the neighbor in its own dfs and finds that
			//the neighbor's trace is still on it means there is a back edge; if the neighbor truly exited 
			//dfs it should have unset the trace bit(1st statement after this for block)
			if (trace[*it])
				return true;
		}
		//post order reset trace
		trace[i] = false;
		return false;
	}
	bool isCycle(){
		bool *trace = new bool[vnum];
		bool cycle = false;
		for (int i = 0; i < vnum; ++i)
			trace[i] = false;
		for (int i = 0; i < vnum; ++i){
			if (isCycleHelper(i, trace)){
				cycle = true;
				break;
			}
		}
		for (int i = 0; i < vnum; ++i)
			visited[i] = false;
		return cycle;
	}
};
int main(){
	graph g1(6);
	g1.addEdge(5, 0);
	g1.addEdge(5, 2);
	g1.addEdge(4, 0);
	g1.addEdge(4, 1);
	g1.addEdge(2, 3);
	g1.addEdge(3, 1);

	g1.dfs();
	g1.bfs();
	g1.topoSort();
	cout << "\nCycle Present:" << g1.isCycle() << endl;

	//cycle detection
	graph g2(4);
	g2.addEdge(0, 1);
	g2.addEdge(0, 2);
	g2.addEdge(1, 2);
	g2.addEdge(2, 0);
	g2.addEdge(2, 3);
	g2.addEdge(3, 3);
	g2.dfs();
	cout << "\nCycle Present:" << g2.isCycle() << endl;

	getchar();
}
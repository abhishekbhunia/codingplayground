//1. Cycle in undirected graph using union find
struct Graph{
	int V, E;
	vector<pair<int, int>> edges;
	vector<int> roots;
	Graph(){}
	Graph(int v, int e) :V(v), E(e){
		edges.resize(e);
		roots.insert(roots.begin(), V, -1);
	}
	int g_find(int node){
		if (roots[node] == -1)
			return node;
		return g_find(roots[node]);
	}
	void g_union(int src, int dst){
		int src_r = g_find(src);
		int dst_r = g_find(dst);
		roots[src_r] = dst_r;
	}
	bool isCycle(){
		for (int i = 0; i < E; ++i){
			int s_r = g_find(edges[i].first);
			int d_r = g_find(edges[i].second);
			cout << "Before: "; pv(roots);
			cout << "src:" << edges[i].first << " dst:" << edges[i].second << " s_r:" << s_r << " d_r:" << d_r << endl;
			if (s_r == d_r)
				return true;
			//root of destination becomes root of 'root of source': src----->dst
			g_union(s_r, d_r);
			cout << "After Union: "; pv(roots); pnl;
		}
		return false;
	}
};
void test_unionfindCycle(){
	Graph g(3, 3);
	g.edges[0].first = 0;
	g.edges[0].second = 1;
	g.edges[1].first = 1;
	g.edges[1].second = 2;
	g.edges[2].first = 2;
	g.edges[2].second = 0;

	cout << g.isCycle() << endl;
	
}
//2. Kruskal's MST
struct edgeKr{
	int src, dst, weight;
};
struct subset{
	int parent, rank;
};
class cmp{
public:
	bool operator()(edgeKr a, edgeKr b){
		return a.weight < b.weight;
	}
};
struct graphKr{
	int V, E;
	vector<edgeKr> edges;
	vector<subset> subsets;
	vector<edgeKr> mst;
	graphKr(){}
	graphKr(int v, int e):V(v),E(e){
		edges.resize(E);
		subsets.resize(V);
		for (int i = 0; i < V; ++i){
			subsets[i].parent = i;
			subsets[i].rank = 0;
		}
			
	}
	int find_Kr(int i){
		if (subsets[i].parent != i)
			subsets[i].parent = find_Kr(subsets[i].parent);
		return subsets[i].parent;
	}
	void union_Kr(int x, int y){
		int x_r = find_Kr(subsets[x].parent);
		int y_r = find_Kr(subsets[y].parent);
		//subset with higher rank shoulh house the other subset
		if (subsets[x_r].rank > subsets[y_r].rank)
			subsets[y_r].parent = x_r;
		else if (subsets[y_r].rank > subsets[x_r].rank)
			subsets[x_r].parent = y_r;
		else{
			subsets[x_r].parent = y_r;
			subsets[y_r].rank++;
		}
	}
	void pe(vector<edgeKr> v){
		for (int i = 0; i < v.size(); ++i)
			cout << "[Src:" << v[i].src << " Dst:" << v[i].dst << " Wt:" << v[i].weight << " ]" << endl;
		pnl;
	}
	void getMST(){
		cout << "Edges before sort:\n"; pe(edges);
		int e = 0, i = 0;
		sort(edges.begin(), edges.end(), cmp());
		cout << "Edges after sort:\n"; pe(edges);
		while (e < V - 1 ){//&& i<edges.size()){
			int x_r = find_Kr(edges[i].src);
			int y_r = find_Kr(edges[i].dst);
			if (x_r != y_r){
				mst.push_back(edges[i]);
				union_Kr(x_r, y_r);
				e++;
			}
			i++;
		}
		cout << "MST:\n"; pe(mst);
	}
};

void test_KruskalMST(){
	/* weighted undirected graph
	    10
	0--------1
	|  \     |
	6|   5\   |15
	|      \ |
	2--------3
	     4       */
	graphKr g(4, 5);

	g.edges[0].src = 0;
	g.edges[0].dst = 1;
	g.edges[0].weight = 10;

	g.edges[1].src = 0;
	g.edges[1].dst = 2;
	g.edges[1].weight = 6;

	g.edges[2].src = 0;
	g.edges[2].dst = 3;
	g.edges[2].weight = 5;

	g.edges[3].src = 1;
	g.edges[3].dst = 3;
	g.edges[3].weight = 15;

	g.edges[4].src = 2;
	g.edges[4].dst = 3;
	g.edges[4].weight = 4;

	g.getMST();
}
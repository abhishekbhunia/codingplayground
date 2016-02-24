//Prim's Minimum Spanning Tree
struct Graph_Pr{
	int V, E;
	vector<vector<pair<int, int>>> adj;//2nd element is 'edge cost', 1st element is dest vertex
	vector<int> parents;
	 
	multiset<pair<int, int>, prcmp> pqset;//1st elem: vertex numer, 2nd element in pair refers to 'prim's cost'
	Graph_Pr(){}
	Graph_Pr(int v, int e) :V(v), E(e){
		adj.resize(V);
		parents.insert(parents.begin(), V, -1);
		 
	}
	void addEdge(int v, int d, int c){
		adj[v].push_back(make_pair( d, c ));
		adj[d].push_back(make_pair(v, c));
	}
	void pradj(){
		for (int i = 0; i < adj.size(); ++i){
			cout << "Neighbors of:" << i << endl;
			for (int j = 0; j < adj[i].size(); ++j){
				cout << "{ " << adj[i][j].first << "," << adj[i][j].second << " }" << endl;
			}
		}
	}
	void primMST(){
		pqset.insert({ 0, 0 });
		for (int i = 1; i < V; ++i)
			pqset.insert({ i, numeric_limits<int>::max() });
		
		while (!pqset.empty()){ 
			
			int topvert = pqset.begin()->first;
			int topcost = pqset.begin()->second;
			 
			pqset.erase(pqset.begin());
			pnl;
			cout << "Deleted vertex:" << topvert << " with cost:" << topcost << endl;
			if (!pqset.empty())
				cout << "After Deletion top:" << pqset.begin()->first << " cost:" << pqset.begin()->second << endl;
			for (auto adjit = adj[topvert].begin(); adjit != adj[topvert].end(); ++adjit){
				//this loop inspects if this vertex has neighbors in the heap and updates prim's cost
				//adjit->first = adj vertex number of min,
				//adjit->second = adj edge cost from min,

				//1. 'it' points to adj vertex -> use it to find element in the set
				
				int ext = adjit->first;//ext = neighbour vertex i am trying to match
				cout << "Inspecting " << topvert << "'s neighbours in set" << endl;
				multiset<pair<int, int>, prcmp>::iterator setit = find_if(pqset.begin(), pqset.end(), [ext](pair<int, int> a)->bool{return a.first == ext; });
				
				if (setit != pqset.end() && setit->second > adjit->second){
					//since setit is constant iterator, we can't modify it, so just erase and add entry with changed values
					cout << "neighbor found with vertex:" << setit->first << " cost:" << setit->second << endl;
					parents[setit->first] = topvert;		
					
					pqset.insert({ setit->first, adjit->second });
					cout << "Inserted {" << setit->first << "," << adjit->second << " }" << endl;
					cout << "Deleted {" << setit->first << "," << setit->second << " }" << endl;
					 
					pqset.erase(setit);					 
				}
			}
		}
		//now print mst
		for (int i = 0; i < parents.size(); ++i){
			cout << i << " " << parents[i] << endl;
		}
	}
};
void test_primMST(){
	Graph_Pr g(9, 0);//not using edgenum

	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);

	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);

	g.addEdge(2, 3, 7);
	g.addEdge(2, 8, 2);
	g.addEdge(2, 5, 4);

	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);

	g.addEdge(4, 5, 10);
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 1);
	g.addEdge(6, 8, 6);
	g.addEdge(7, 8, 7);

	g.pradj();
	g.primMST();
}
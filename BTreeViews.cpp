#include<iostream>
#include<vector>
#include<map>
#include<deque>
using namespace std;
struct BTree{
	int val;
	BTree *left, *right;
	BTree(){ val = -1; left = nullptr; right = nullptr; }
	BTree(int x){ val = x; left = nullptr; right = nullptr; }
};
void inOrder(BTree *r){
	if (r){
		inOrder(r->left);
		cout << r->val << " ";
		inOrder(r->right);
	}
}
void printVert(BTree *r, int vline, int hd){
	if (r){
		if (vline == hd)
			cout << r->val << " ";
		printVert(r->left, vline, hd - 1);
		printVert(r->right, vline, hd + 1);
	}
}
void vertViewHelper(BTree *r, int *max, int *min, int hd){
	if (r){
		if (*max<hd)
			*max = hd;
		if (*min>hd)
			*min = hd;
		vertViewHelper(r->left, max, min, hd - 1);
		vertViewHelper(r->right, max, min, hd + 1);
	}
}
void vertView(BTree *r){
	int max = 0, min = 0;
	//set max & min
	vertViewHelper(r, &max, &min, 0);
	for (int vline = min; vline <= max; ++vline){
		printVert(r, vline, 0);
		cout << endl;
	}
}
void vertView_2_helper(BTree *r, map<int, vector<int>> &m, int hd){
	if (r){
		m[hd].push_back(r->val);
		vertView_2_helper(r->left, m, hd - 1);
		vertView_2_helper(r->right, m, hd + 1);
	}
}
void vertView_2(BTree *r)
{
	map<int, vector<int>> m;
	vertView_2_helper(r, m, 0);
	map<int, vector<int>>::iterator it = m.begin();
	for (; it != m.end(); ++it){
		//1. VERTICAL ORDER
		for (int i = 0; i<it->second.size(); ++i)
			cout << it->second[i] << " ";
		//2. TOP VIEW
		//cout << it->second[0];
		cout << endl;
	}
}
struct QBT{
	BTree *node;
	int col;
	QBT(BTree *r, int x) :node(r), col(x){}
};
void topViewQ(BTree *r){
	if (r){
		deque<QBT> q;
		q.push_back(QBT(r, 0));
		map<int, int> m;
		while (!q.empty()){
			QBT x = q.front();
			if (m.find(x.col) == m.end()){//for bottom view, comment this out
				m[x.col] = x.node->val;
				//cout << "AT: " << x.col << " Inserted: " << m[x.col] << endl;
			}//for bottom view, comment this out
			q.pop_front();
			if (x.node->left)
				q.push_back(QBT(x.node->left, x.col - 1));
			if (x.node->right)
				q.push_back(QBT(x.node->right, x.col + 1));		
		}
		for (map<int, int>::iterator it = m.begin(); it != m.end(); ++it){
			cout << it->second << " ";
		}
		cout << endl;
	}
}
int main(void){
	//									      25(0)
	//							17(-1)				       32(1)
	//					12(-2)			19(0)		30(0)			35(2)
	// bottom view: 12,17,30,32,35
	BTree *root = new BTree(25);
	root->left = new BTree(17);
	root->right = new BTree(32);
	root->left->left = new BTree(12);
	root->left->right = new BTree(19);
	root->right->left = new BTree(30);
	root->right->right = new BTree(35);
	inOrder(root);
	cout << endl;
	vertView(root);
	cout << endl;
	vertView_2(root);
	cout << endl;
	topViewQ(root);
	int in;
	cin >> in;
	return 0;
}


#include<iostream>
#include<typeinfo>
#include<deque>
#include<vector>
using namespace std;
class BST{
public:
	int val;
	BST *left, *right;
	BST(int x, BST* l=nullptr, BST *r=nullptr) : val(x), left(l), right(r){}
};
void printLevelOrder(BST *r){
	if (r){
		deque<BST*> cur{ r };
		deque<BST*> nxt;
		while (!cur.empty()){
			BST *tmp = cur.front();
			if (tmp){
				cout << tmp->val << " ";
				nxt.push_back(tmp->left);
				nxt.push_back(tmp->right);
			}
			cur.pop_front();
			if (cur.empty()){
				swap(cur, nxt);
				cout << endl;
			}
			
		}
	}
}
BST* BSTfromPre(vector<int> &pre, int &pre_id, int min, int max){
	if (pre_id == pre.size())
		return nullptr;
	int cur = pre[pre_id];
	cout << "cur: " << cur << " ,pre_id: " << pre_id << " ,min: " << min << " ,max: " << max << endl;
	if (cur<min || cur>max)
		return nullptr;
	pre_id++;
	auto lt = BSTfromPre(pre, pre_id, min, cur);
	auto rt = BSTfromPre(pre, pre_id, cur, max);
	return new BST(cur,lt , rt);
}
void inOrder(BST *r){
	if (r){
		inOrder(r->left);
		cout << r->val << " ";
		inOrder(r->right);
	}
}
int main(void){
	//									      25(0)
	//							17(-1)				       32(1)
	//					12(-2)			19(0)		30(0)			35(2)
	// bottom view: 12,17,30,32,35
	//vector<int> pre{ 25, 17, 12, 19, 32, 30, 35 };
	vector<int> pre{ 2,1,3 };
	int x = 0;
	BST *res=BSTfromPre(pre,x,numeric_limits<int>::min(),numeric_limits<int>::max());
	printLevelOrder(res);
	int in;
	cin >> in;
	return 0;
}
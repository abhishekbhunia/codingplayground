#include<iostream>
#include<typeinfo>
#include<deque>
using namespace std;
class BST{
public:
	int val;
	BST *left, *right;
	BST(int x) : val(x), left(nullptr), right(nullptr){}
};

pair<BST*, BST*> BSTtoDLL(BST *r){//pair returns head & tail of left/right lists

	if (r){

		auto l = BSTtoDLL(r->left);
		auto rt = BSTtoDLL(r->right);
		if (l.second)
			l.second->right = r;
		r->left = l.second;
		if (rt.first)
			rt.first->left = r;
		r->right = rt.first;
		return{ l.first ? l.first : r, rt.second ? rt.second : r };
	}
	return{ nullptr, nullptr };

}
BST* DLLtoBST(BST** L, int low, int high){
	if (low >= high)
		return nullptr;
	int mid = low + ((high - low) >> 1);
	BST* lt = DLLtoBST(L, low, mid);
	BST* cur_root = *L;
	*L = (*L)->right;
	cur_root->left = lt;
	cur_root->right = DLLtoBST(L, mid + 1, high);
	return cur_root;
}
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
int main(void){
	//									      25(0)
	//							17(-1)				       32(1)
	//					12(-2)			19(0)		30(0)			35(2)
	// bottom view: 12,17,30,32,35
	BST *root = new BST(25);
	root->left = new BST(17);
	root->right = new BST(32);
	root->left->left = new BST(12);
	root->left->right = new BST(19);
	root->right->left = new BST(30);
	root->right->right = new BST(35);
	printLevelOrder(root);
	cout << endl << endl;
	BST* temp = BSTtoDLL(root).first;
	BST* temp2 = temp;
	int sz = 0;
	cout << "LIST: ";
	if (temp){
		while (temp){
			cout << temp->val << " ";
			sz++;
			temp = temp->right;
		}
	}
	temp = temp2;
	
	BST* x=DLLtoBST(&temp, 0, sz);
	cout << endl << endl;
	printLevelOrder(x);
	int in;
	cin >> in;
	return 0;
}
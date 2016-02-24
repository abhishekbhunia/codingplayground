#include<iostream>
using namespace std;
class BST{
public:
	int val;
	BST *left, *right;
	BST(int x) : val(x), left(nullptr), right(nullptr){}
};
BST* BSTtoCircDLL(BST *r){
	if (!r)
		return nullptr;
	BST *l_head = BSTtoCircDLL(r->left);
	BST *r_head = BSTtoCircDLL(r->right);

	BST *l_tail = nullptr;
	if (l_head){
		l_tail = l_head->left;
		l_tail->right = r;
		r->left = l_tail;
		l_tail = r;
	}
	else
		l_head = l_tail = r;

	BST *r_tail = nullptr;
	if (r_head){
		r_tail = r_head->left;
		r_head->left = l_tail;
		l_tail->right = r_head;
	}
	else
		r_tail = l_tail;

	l_head->left = r_tail, r_tail->right = l_head;

	return l_head;
}
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
	//pair<BST*,BST*> res=BSTtoDLL(root);
	BST* temp = BSTtoDLL(root).first;
	if (temp){
		while (temp){
			cout << temp->val << " ";
			temp = temp->right;
		}
	}


	int in;
	cin >> in;
	return 0;
}
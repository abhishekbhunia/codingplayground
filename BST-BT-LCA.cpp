#include<iostream>
#include<deque>
using namespace std;
class BST{
public:
	int val;
	BST *left, *right;
	BST(int x, BST *l = nullptr, BST *r = nullptr) :val(x), left(l), right(r){}
};
BST* findLCABST(BST *r, BST *s, BST *b){//constraint: s<=b
	while (r->val<s->val || r->val>b->val){
		if (r->val < s->val)
			r = r->right;
		if (r->val > b->val)
			r = r->left;
	}
	return r;
}
BST* findLCABT(BST *r, BST *a, BST *b){
	if (!r)
		return nullptr;
	if (r == a || r == b)
		return r;
	auto l = findLCABT(r->left, a, b), rt = findLCABT(r->right, a, b);
	if (l&&rt)
		return r;
	return l ? l : rt;
}
int main(void){
	//									      25(0)
	//							17(-1)				       32(1)
	//					12(-2)			19(0)		30(0)			35(2)
	 
	BST *root=new BST(25,new BST(17,new BST(12),new BST(19)),new BST(32,new BST(30),new BST(35)));
	cout << findLCABT(root, root->left->left, root->right->left)->val << endl;
	cout << findLCABST(root, root->left->left, root->right->left)->val << endl;
	int in;
	cin >> in;
	return 0;

}
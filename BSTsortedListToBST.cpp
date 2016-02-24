//1. sorted linked list and array to bst
//2. first occurance of k
//3. first occurance of larger than k
#include<iostream>
#include<vector>
using namespace std;
class BST{
public:
	int val;
	BST *left,*right;
	BST(int x,BST *l=nullptr,BST *r=nullptr):val(x),left(l),right(r){}	
};
BST* largerK(BST *r, int k){
	BST *ret = nullptr;
	while (r){
		if (r->val>k){			
			ret = r;			 
			r = r->left;
		}
		else if (r->val == k){
			cout << "rval:" << r->val << endl;
			r = r->right;
		}
		else
			r = r->right;
	}
	return ret;
}
BST* firstK_recur(BST *r, int k){
	if (!r)
		return nullptr;
	if (r->val == k){
		BST *ret = firstK_recur(r->left, k);
		return ret ? ret : r;
	}
	else
		return (k<r->val) ? firstK_recur(r->left, k) : firstK_recur(r->right, k);
}
BST* firstK_iter(BST *r, int k){
	BST *ret = nullptr;
	while (r){
		if (k == r->val){
			ret = r;
			r = r->left;
		}
		else if (k>r->val)
			r = r->right;
		else
			r = r->left;
	}
	return ret;
}
BST* arrayToBST(vector<int> &v,int low,int high){
	if (low < high){
		int mid = low + (high - low) >> 1;
		return (new BST(v[mid], arrayToBST(v, low, mid), arrayToBST(v, mid + 1, high)));
	}
	return nullptr;
}
BST* dllToBST(vector<BST*> v,int low,int high){
	BST *ret=nullptr;
	if(low<high){
		int mid=low+((high-low)>>1);			
		ret->left=dllToBST(v,low,mid);
		ret->val=v->val;
		ret->right=dllToBST(v,mid+1,high);
	}
	return ret;
}
int main(void){
	//				 						108
	//						108								285
	//            -10            108                   285		290
	//		-14         2    										401   				
	vector<int> v{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	BST *root = new BST(108, new BST(108), new BST(285));
	root->left->left=new BST(-10, new BST(-14), new BST(2));
	root->left->right=new BST(108);
	root->right->left=new BST(285);
	root->right->right=new BST(290, nullptr, new BST(401));

	BST *res = firstK_iter(root,108);
	if (res)
		cout << res->val << endl;
	res = firstK_recur(root,108);
	if (res)
		cout << res->val << endl;
	res = largerK(root,108);
	if (res)
		cout << res->val << endl;
	int in;
	cin >> in;
	return 0;


}
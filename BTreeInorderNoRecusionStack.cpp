#include <iostream>
#include <memory>
using namespace std;
template <typename T>
struct BTree{
	T val;
	shared_ptr<BTree<T>> left,right;
};
template <typename T>
void inOrder(shared_ptr<BTree<T>> n){
//the idea is to change the right child link of every leaf to point to inorder successor and later undo it
//instead of printing left,root,right we will be printing leaf,successor
	while(n){
		//if left child/predecessor exists, go to rightmost child of left subtree and change the successor link to current node
		if(n->left){//go to immediate inorder predecessor
			shared_ptr<BTree<T>> pre=n->left;
			//and go to the rightmost child as long as it doesn't pointback to current node(reversal phase)
			while(pre->right&&pre->right!=n)
				pre=pre->right;
			//
			if(pre->right)//reversal/unlink phase, pre->right==n, have to unlink and switch to right subtree from current
			{
				pre->right=nullptr;
				cout<<n->val<<" ";
				n=n->right;
			}
			else //link phase
			{
				pre->right=n;
				n=n->left;//TRICKY: descend thorugh left subtree
			}
		}
		else{//we have reached a leaf node
			cout<<n->val<<" ";
			n=n->right;//follow the successor link from this leaf node
		}
	}
cout<<endl;
}
int main(void){
    //                  1
    //          2               3
    //      4       5       6       7       
	shared_ptr<BTree<int>> root=make_shared<BTree<int>>(BTree<int>{1,nullptr,nullptr});
	root->left=make_shared<BTree<int>>(BTree<int>{2,nullptr,nullptr});
	root->right=make_shared<BTree<int>>(BTree<int>{3,nullptr,nullptr});
	root->left->left=make_shared<BTree<int>>(BTree<int>{4,nullptr,nullptr});
	root->left->right=make_shared<BTree<int>>(BTree<int>{5,nullptr,nullptr});
	root->right->left=make_shared<BTree<int>>(BTree<int>{6,nullptr,nullptr});
	root->right->right=make_shared<BTree<int>>(BTree<int>{7,nullptr,nullptr});
	inOrder(root);
	int inp;
	cin>>inp;
	return 0;
}
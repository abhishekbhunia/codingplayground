//print a Binary Tree in level order without recursion
#include <iostream>
#include <queue>
#include <memory>
#include <algorithm>
using namespace std;
template <typename T>
struct BTree{
	T val;
	shared_ptr<BTree<T>> left,right;
};
template <typename T>
void printBTreeLevelwise(const shared_ptr<BTree<T>> &n)
{
	//this one prints a line break on wach level at the expense of an extra queue
	if(n){
		queue<shared_ptr<BTree<T>>> currentLevel,nextLevel;
		currentLevel.emplace(n);
		while(!currentLevel.empty()){
			shared_ptr<BTree<T>> temp=currentLevel.front();
			cout<<temp->val<<" ";
			currentLevel.pop();
			if(temp->left)
				nextLevel.emplace(temp->left);
			if(temp->right)
				nextLevel.emplace(temp->right);
			if(currentLevel.empty()){
				cout<<endl;
				swap(currentLevel,nextLevel);
			}
		}
	}
	cout<<endl;
}
template <typename T>
void printBTreeLevelwise2(const shared_ptr<BTree<T>> &n)
{
	if(n){
		queue<shared_ptr<BTree<T>>> q;
		q.emplace(n);
		while(!q.empty()){
			cout<<q.front()->val<<" ";
			if(q.front()->left)
				q.emplace(q.front()->left);
			if(q.front()->right)
				q.emplace(q.front()->right);
			q.pop();
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
	printBTreeLevelwise(root);
	printBTreeLevelwise2(root);
	int inp;
	cin>>inp;
	return 0;
}
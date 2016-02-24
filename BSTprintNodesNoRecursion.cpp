//use iteration(stack) to print all desendent nodes from n, in sorted order
#include <iostream>
#include <memory>
#include <stack>
#include <vector>
using namespace std;
template <typename T>
struct BST{
	T val;
	shared_ptr<BST<T>> left;
	shared_ptr<BST<T>> right;
};
template <typename T>
vector<T> printBSTfromN(const shared_ptr<BST<T>> &node)
{
	stack<shared_ptr<BST<T>>> s;//STACK OF NODE POINTERS
	vector<T> res;
	shared_ptr<BST<T>> n=node;
	while(!s.empty()||n){
		if(n){
			s.push(n);
			n=n->left;
		}
		else{
			n=s.top();//tricky
			res.push_back(n->val);//cout<<n->val<<" ";
			s.pop();
			n=n->right;//tricky
		}
	}
	return res;
}
int main(void)
{
	//        43
  //    23     47
  //      37      53
  //    29  41
  //     31
	shared_ptr<BST<int>> tree=make_shared<BST<int>>(BST<int>{43,nullptr,nullptr});
	tree->left=make_shared<BST<int>>(BST<int>{23,nullptr,nullptr});
	tree->left->right=make_shared<BST<int>>(BST<int>{37,nullptr,nullptr});
	tree->left->right->left=make_shared<BST<int>>(BST<int>{29,nullptr,nullptr});
	tree->left->right->right=make_shared<BST<int>>(BST<int>{41,nullptr,nullptr});
	tree->left->right->left->right=make_shared<BST<int>>(BST<int>{31,nullptr,nullptr});
	tree->right=make_shared<BST<int>>(BST<int>{47,nullptr,nullptr});
	tree->right->right=make_shared<BST<int>>(BST<int>{53,nullptr,nullptr});
	auto v=printBSTfromN(tree);
	for(auto it=v.begin();it!=v.end();++it)
		cout<<*it<<" ";
	cout<<endl;
	int inp;
	cin>>inp;
	return 0;

}
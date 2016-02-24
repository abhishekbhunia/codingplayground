#include<iostream>
#include<limits>
#include<memory>
#include<queue>
using namespace std;
template<typename T>
struct BTree{
	T val;
	shared_ptr<BTree<T>> left,right;
};
template<typename T>
bool isBSTHelper(shared_ptr<BTree<T>> r,T lower,T upper){
	if(!r)
		return true;
	else if(r->val<lower||r->val>upper)
		return false;
	else
		return isBSTHelper(r->left,lower,r->val)&&isBSTHelper(r->right,r->val,upper);
}
template<typename T>
bool isBST(shared_ptr<BTree<T>> r){
	return isBSTHelper(r,numeric_limits<T>::min(),numeric_limits<T>::max());
}
template<typename T>
bool isBST_2_2(shared_ptr<BTree<T>> r,T &low){//trying recursive
	if(!r){
		//if (low==numeric_limits<T>::min())

		return true;
	}
	bool l=isBST_2_2(r->left,low);
	low=(r->val>=low)?r->val:low;
	bool rt=(r->val==low)?isBST_2_2(r->right,low):false;
	return l&&rt;
}
template<typename T>
bool isBST_2(shared_ptr<BTree<T>> r){
	T last=numeric_limits<T>::min();
	bool res=true;
	while(r){
		if(r->left){
			shared_ptr<BTree<T>> pre=r->left;
			while(pre->right&&pre->right!=r){
				pre=pre->right;
			}
			if(pre->right){
				if(r->val<last)
					res=false;
				last=r->val;
				pre->right=nullptr;
				r=r->right;
			}
			else{
				pre->right=r;
				r=r->left;
			}
		}
		else{
			if(r->val<last){
				res=false;
			}
			last=r->val;
			r=r->right;
		}
	}
	return res;
}
template<typename T>
struct qnode{
	shared_ptr<BTree<T>> node;
	T low,high;
};
template<typename T>
bool isBST_3(shared_ptr<BTree<T>> r){
	queue<qnode<T>> q;
	q.emplace(qnode<T>{r,numeric_limits<T>::min(),numeric_limits<T>::max()});
	while(!q.empty()){
		if(q.front().node){//if front node is not null(q may contain series of null nodes, we don't want to push their children)
			//check limits
			if(q.front().node->val<q.front().low||q.front().node->val>q.front().high)
				return false;
			//push left
			q.emplace(qnode<T>{q.front().node->left,q.front().low,q.front().node->val});
			//push right
			q.emplace(qnode<T>{q.front().node->right,q.front().node->val,q.front().high});
		}
		q.pop();
	}
    return true;
}
int main(void){
	//         50
	//     48      52
	//  32   49   51  53
	int g_last=numeric_limits<int>::min();
	shared_ptr<BTree<int>> root=make_shared<BTree<int>>(BTree<int>{50,nullptr,nullptr});
	root->left=make_shared<BTree<int>>(BTree<int>{48,nullptr,nullptr});
	root->right=make_shared<BTree<int>>(BTree<int>{52,nullptr,nullptr});
	root->left->left=make_shared<BTree<int>>(BTree<int>{32,nullptr,nullptr});
	root->left->right=make_shared<BTree<int>>(BTree<int>{49,nullptr,nullptr});
	root->right->left=make_shared<BTree<int>>(BTree<int>{51,nullptr,nullptr});
	root->right->right=make_shared<BTree<int>>(BTree<int>{53,nullptr,nullptr});
	cout<<isBST(root)<<" "<<isBST_2(root)<<" "<<isBST_3(root)<<" "<<isBST_2_2(root,g_last)<<endl;
	int in;
	cin>>in;
	return 0;
}
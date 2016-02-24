//build a binary tree from inorder and preorder/postorder listing
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <typeinfo>
#include <stack>
using namespace std;
template <typename T>
struct BTree{
	T val;
	shared_ptr<BTree<T>> left,right;
};
template <typename T>
shared_ptr<BTree<T>> btbuilderHelper(const vector<T> &pre,const int &pre_s,const int &pre_e,const vector<T> &in,const int &in_s,const int &in_e){
	if(pre_e>pre_s&&in_e>in_s){
		//find the next root in inorder list
		auto it=find(in.cbegin()+in_s,in.cend()+in_e,pre[pre_s]);
		//calculate size of left subtree
		int ltsize=it-(in.cbegin()+in_s);

		return shared_ptr<BTree<T>>(new BTree<T>{
			pre[pre_s],
			btbuilderHelper(pre,pre_s+1,pre_s+1+ltsize,in,in_s,it-in.cbegin()),
			btbuilderHelper(pre,pre_s+1+ltsize,pre_e,in,(it-in.cbegin())+1,in_e)
		});
	}
    return nullptr;
}

template <typename T>
shared_ptr<BTree<T>> btbuilder(const vector<T> &pre,const vector<T> &in){
	return btbuilderHelper(pre,0,pre.size(),in,0,in.size());
}
template <typename T>
void printBTreeIn(shared_ptr<BTree<T>> r){
	if(r){
		printBTreeIn(r->left);
		cout<<r->val<<" ";
		printBTreeIn(r->right);
	}
}
template <typename T>
void printBTreePre(shared_ptr<BTree<T>> r){
	if(r){
		cout<<r->val<<" ";
		printBTreePre(r->left);
		printBTreePre(r->right);
	}
}
template <typename T>
void printBTreePost(shared_ptr<BTree<T>> r){
	if(r){
		printBTreePost(r->left);
		printBTreePost(r->right);
		cout<<r->val<<" ";
	}
}
template <typename T>
void printBTreeInIter(shared_ptr<BTree<T>> r){
    if(!r)
        return;
    stack<shared_ptr<BTree<T>>> s;
    while(r||!s.empty()){
        if(r){
            s.push(r);
            r=r->left;
        }
        else{
            r=s.top();
            cout<<r->val<<" ";
            s.pop();
            r=r->right;
        }
    }
    cout<<endl;
    return;
}
template <typename T>
void printBTreePreIter(shared_ptr<BTree<T>> r){
    if(!r)
        return;
    stack<shared_ptr<BTree<T>>> s;
    s.push(r);
    while(!s.empty()){
        shared_ptr<BTree<T>> r=s.top();
        s.pop();
        cout<<r->val<<" ";
        if(r->right)
            s.push(r->right);
        if(r->left)
            s.push(r->left);
    }
    cout<<endl;
    return;
}
template <typename T>
void printBTreePostIter(shared_ptr<BTree<T>> r){
    if(!r)
        return;
    stack<shared_ptr<BTree<T>>> s;
    shared_ptr<BTree<T>> prev=nullptr;
    s.push(r);
    while(!s.empty()){
        shared_ptr<BTree<T>> curr=s.top();
        if(((curr->left==nullptr) && (curr->right==nullptr))||curr->left==prev||curr->right==prev){
            cout<<curr->val<<" ";
            s.pop();
            prev=curr;
        }
        else{
            if(curr->right)
                s.push(curr->right);
            if(curr->left)
                s.push(curr->left);
        }
    }
    cout<<endl;
}
template <typename T>
void printBTreePostIter2(shared_ptr<BTree<T>> r){
    if(!r)
        return;
    stack<shared_ptr<BTree<T>>> s,res;
    s.push(r);
    while(!s.empty()){
    	shared_ptr<BTree<T>> curr=s.top();
    	s.pop();
    	if(curr->left)
    		s.push(curr->left);
    	if(curr->right)
    		s.push(curr->right);
    	res.push(curr);
    }
    while(!res.empty()){
    	cout<<res.top()->val<<" ";
    	res.pop();
    }
    cout<<endl;
}
template <typename T>
void printBTreePostIter3(shared_ptr<BTree<T>> r){
	if(!r)
		return;
	stack<shared_ptr<BTree<T>>> s;
	shared_ptr<BTree<T>> prev=nullptr;
	do{
        while(r!=nullptr){
            s.push(r);
            r=r->left;   
        }
        //cout<<"stack tooop:"<<s.top()->val<<endl;
        while(r==nullptr&&!s.empty()){
        	//cout<<"stack tp:"<<s.top()->val<<endl;
            r=s.top();
            if(r->right==nullptr||r->right==prev){
                cout<<r->val<<" ";
                s.pop();
                prev=r;
                r=nullptr;
            }
            else
                r=r->right;
        }
        
	}while(!s.empty());
}
int main(){
//				 34
//			  22    5
//          43  21 3  31
//In:43 22 21 34 3 5 31 Pre: 34 22 43 21 5 3 31 Post: 43 21 22 3 31 5 34
//                              57
//                      8                  9
//                3           6      2           1
//             11     n   n     20 n    77 90         n
//In:11 3 8 6 20 57 2 77 9 90 1 Pre: 57 8 3 11 6 20 9 2 77 1 90 Post: 11 3 20 6 8 77 2 90 1 9 57
    shared_ptr<BTree<int>> r=make_shared<BTree<int>>(BTree<int>{57,nullptr,nullptr});
    r->left=make_shared<BTree<int>>(BTree<int>{8,nullptr,nullptr});
    r->right=make_shared<BTree<int>>(BTree<int>{9,nullptr,nullptr});
    r->left->left=make_shared<BTree<int>>(BTree<int>{3,nullptr,nullptr});
    r->left->right=make_shared<BTree<int>>(BTree<int>{6,nullptr,nullptr});
    r->right->left=make_shared<BTree<int>>(BTree<int>{2,nullptr,nullptr});
    r->right->right=make_shared<BTree<int>>(BTree<int>{1,nullptr,nullptr});
    r->left->left->left=make_shared<BTree<int>>(BTree<int>{11,nullptr,nullptr});
    r->left->right->right=make_shared<BTree<int>>(BTree<int>{20,nullptr,nullptr});
    r->right->left->right=make_shared<BTree<int>>(BTree<int>{77,nullptr,nullptr});
    r->right->right->left=make_shared<BTree<int>>(BTree<int>{90,nullptr,nullptr});
	vector<int> in{43,22,21,34,3,5,31};
	vector<int> pre{34,22,43,21,5,3,31};
	vector<int> in2{11,3,20,6,8,77,2,90,1,9,57};
	vector<int> pre2{57,8,3,11,6,20,9,2,77,1,90};
	auto res=btbuilder(pre,in);
	//cout << res->val << " " <<res->left->val<<" "<<res->left->left->val<<" "<<res->left->right->val<<endl;
	printBTreeIn(r);
	cout<<endl;
	printBTreeInIter(r);
	printBTreePre(r);
	cout<<endl;
	printBTreePreIter(r);
	//cout<<endl;
	
	printBTreePost(r);
	cout<<endl;
	printBTreePostIter(r);
	printBTreePostIter2(r);
	printBTreePostIter3(r);
	//cout<<endl;
	int x;
	cin>>x;
	return 0;
}
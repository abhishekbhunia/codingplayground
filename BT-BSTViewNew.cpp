// Example program
#include <iostream>
#include <string>
#include <memory>
#include <deque>
#include <algorithm>
#include <map>
using namespace std;
struct bst{
    int val;
    shared_ptr<bst> left,right;
    bst(){}
    bst(int x,shared_ptr<bst> l,shared_ptr<bst> r):val(x),left(l),right(r){}
};
typedef shared_ptr<bst> sptr;
void levelorder1Q(sptr root){
    if(root){
        deque<sptr> dq;
        dq.push_back(root);
        while(!dq.empty()){
            sptr top=dq.front();
            cout<<top->val<<" ";
            if(top->left)
                dq.push_back(top->left);
            if(top->right)
                dq.push_back(top->right);
            dq.pop_front();
        }
        cout<<endl;
    }
}
void levelorder2Q(sptr root){
    if(root){
        deque<sptr> one,two;
        one.push_back(root);
        while(!one.empty()){
            sptr top=one.front();
            if(top->left)
                two.push_back(top->left);
            if(top->right)
                two.push_back(top->right);
            cout<<top->val<<" ";
            one.pop_front();
            if(one.empty()){
                swap(one,two);
                cout<<endl;
            }                
        }
    }
}
void inorder(sptr root){
    if(root){
        inorder(root->left);
        cout<<root->val<<" ";
        inorder(root->right);
    }
}
void preorder(sptr root){
    if(root){
        cout<<root->val<<" ";
        preorder(root->left);        
        preorder(root->right);
    }
}
void postorder(sptr root){
    if(root){        
        postorder(root->left);        
        postorder(root->right);
        cout<<root->val<<" ";
    }
}
void verticalview_helper(sptr root,int &min,int &max,int hd){
    if(root){
        if(hd>max)
            max=hd;
        if(hd<min)
            min=hd;
        verticalview_helper(root->left,min,max,hd-1);
        verticalview_helper(root->left,min,max,hd+1);
    }
}
void print_vertviewR(sptr root,int col,int hd){
    if(root){
        if(col==hd)
            cout<<root->val<<" ";
        print_vertviewR(root->left,col,hd-1);
        print_vertviewR(root->right,col,hd+1);
    }
}
void verticalviewR(sptr root){
    int min=0,max=0;
    verticalview_helper(root,min,max,0);
    for(int vline=min;vline<=max;++vline){
        print_vertviewR(root,vline,0);
    }
}
void topbottomviewQ(sptr root){
    if(root){
        deque<pair<sptr,int>> dq;//(nodeval,column)
        map<int,vector<int>> mp;//(column,nodeval)
        dq.push_back(make_pair(root,0));
        
        while(!dq.empty()){
            pair<sptr,int> front=dq.front();
            cout<<"dq front:"<<front.first->val<<" "<<front.second<<endl;
            mp[front.second].push_back(front.first->val);            
            if(front.first->left)
                dq.push_back(make_pair(front.first->left,front.second-1));
            if(front.first->right)
                dq.push_back(make_pair(front.first->right,front.second+1));
            dq.pop_front();
        }
        cout<<"Top View:"<<endl;
        for(auto it=mp.begin();it!=mp.end();++it){
            cout<<it->second.front()<<" ";
        }
        cout<<endl;
        cout<<"Bottom View:"<<endl;
        for(auto it=mp.begin();it!=mp.end();++it){
            cout<<it->second.back()<<" ";
        }
        cout<<endl;
    }
}
sptr getBST(){
    //                              20
    //                  10                      30
    //          8               12      28               32
    sptr root=make_shared<bst>(bst(20,make_shared<bst>(bst(10,nullptr,nullptr)),make_shared<bst>(bst(30,nullptr,nullptr))));
    root->left->left=make_shared<bst>(bst(8,nullptr,nullptr));
    root->left->right=make_shared<bst>(bst(12,nullptr,nullptr));
    root->right->left=make_shared<bst>(bst(28,nullptr,nullptr));
    root->right->right=make_shared<bst>(bst(32,nullptr,nullptr));
    return root;
}
void testSimpleTraversal(){
    sptr root=getBST();
    cout<<"Inorder:";inorder(root);cout<<endl;
    cout<<"Preorder:";preorder(root);cout<<endl;
    cout<<"Postorder:";postorder(root);cout<<endl;
    cout<<"Levelorder1Q:";levelorder1Q(root); 
    cout<<"Levelorder2Q:\n";levelorder2Q(root); 
}
void vertview(sptr root, map<int,vector<int>> &mp,int hd){
    if(root){
        mp[hd].push_back(root->val);
        vertview(root->left,mp,hd-1);
        vertview(root->right,mp,hd+1);
    }
}
void testView(){
    sptr root=getBST();
    cout<<"Testing Top/Bottom View using Queue:"<<endl;
    topbottomviewQ(root);
    cout<<"Vertical View using Recursion:"<<endl;
    verticalviewR(root);
    cout<<"\nVertical View using Recursion with Map:"<<endl;
    map<int,vector<int>> mp;
    vertview(root,mp,0);
    for(auto it=mp.begin();it!=mp.end();++it){        
        for(auto it2=it->second.begin();it2!=it->second.end();++it2)
            cout<<*it2<<" ";
        cout<<endl;
    }
}
int main()
{
    //testSimpleTraversal();
    testView();
}

// Example program
#include <iostream>
#include <string>
#include<deque>
//#include<algorithm>
using namespace std;
template<typename T>
void xswap(T &a,T &b){
    T t=a;
    a=b;
    b=t;
}
class bst{
    public:
    int val;
    bst *left,*right;
    bst(int x,bst *l=nullptr,bst *r=nullptr):val(x),left(l),right(r){}
};
void lvlorder(bst *r){
    if(!r)
        return;
    deque<bst*> cur{r},nxt;
    while(!cur.empty()){
        bst *tmp=cur.front();
        if(tmp){
            cout<<tmp->val<<" ";
            nxt.push_back(tmp->left);
            nxt.push_back(tmp->right);
        }
        cur.pop_front();
        if(cur.empty()){
            swap(cur,nxt);
            cout<<endl;
        }        
    }
}
void invert(bst *r){
    if(!r)
        return;
    invert(r->left);
    invert(r->right);
    bst *t=r->left;
    r->left=r->right;
    r->right=t;
}
int main()
{
    //                  1                                               1
    //          2               3                           3                       2
    //  4           5     6          7              7               6           5               4
    
    
    bst *root=new bst(1,new bst(2,new bst(4),new bst(5)),new bst(3,new bst(6),new bst(7)));
    lvlorder(root);
    invert(root);
    lvlorder(root);
    return 0;
    
    
    
}

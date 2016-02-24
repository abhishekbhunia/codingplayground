// Example program
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct node{
    char val;
    node *left, *right;
    node(char x):val(x),left(nullptr),right(nullptr){}
    node(char x, node *a, node *b):val(x), left(a), right(b){}
};
typedef node TreeNode;
void inord(TreeNode *h){
    if(h){
        inord(h->left);
        cout<<h->val<<" ";
        inord(h->right);
    }
}
TreeNode* foo(vector<string> &vs, vector<char> &s, TreeNode *head){
    if(head){
        s.push_back(head->val);
        TreeNode* l=foo(vs,s,head->left);
        TreeNode* r=foo(vs,s,head->right);
        if(!l&&!r){
            string st;
            for(char &c: s){
                st+=c;
            }
            vs.push_back(st);
            
        }
        s.pop_back();        
        return head;
    }   
    return nullptr;
}
int main(void){
    TreeNode *one = new TreeNode('1');
    one->left = new TreeNode('2');
    one->right = new TreeNode('3');
    one->left->right = new TreeNode('4');
    one->right->left = new TreeNode('5');;
    one->right->right = new TreeNode('6');
    TreeNode *six=one->right->right;
    six->left = new TreeNode('7');
    six->right = new TreeNode('8');
    
    inord(one);
    cout<<endl;
    vector<string> vs;
    vector<char> s;
    one=foo(vs,s,one);
    for(string &s:vs)
        cout<<s<<endl;
    
}
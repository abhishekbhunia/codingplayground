#include<iostream>
#include<vector>
using namespace std;
class BST{
public:
	
public:
	struct node{
		int val;
		node *left;
		node *right;
		node(int x, node *y, node *z) :val(x), left(y), right(z){}
		node(node *d) :val(d->val), left(d->left), right(d->right){}
	};

	node *root = nullptr;
	void changeLinks(node *par, node *ch, node *newch){
		if (!par)
			return;
		if (par->left == ch)
			par->left = newch;
		else
			par->right = newch;
	}
	bool empty(){
		return (!root);
	}
	void inOrder(node *root){
		if (root){
			inOrder(root->left);
			cout << root->val << " ";
			inOrder(root->right);
		}
	}
	void insert(int key){
		if (empty())
			root = new node(key, nullptr, nullptr);
		else{
			node *par = nullptr;
			node *cur = root;
			while (cur){
				par = cur;
				if (cur->val == key){
					cout << "Duplicate: Insertion failed!" << endl;
					return;// false;
				}
				cur = (key<cur->val) ? cur->left : cur->right;
			}
			if (key<par->val)
				par->left = new node(key, nullptr, nullptr);
			else
				par->right = new node(key, nullptr, nullptr);
		}
		cout << "Insertion of "<<key<<" Successful" << endl;
		return;// true;
	}
	void remove(int key){
		node *par = nullptr;
		node *cur = root;
		while (cur&&cur->val != key){
			par = cur;
			cur = (key<cur->val) ? cur->left : cur->right;
		}
		if (!cur)//1. when the root is null 2. when there is no node with the key
		{
			cout << "Deletion of "<<key<<" failed!" << endl;
			return;// false;
		}
		node *key_node = cur;
		if (key_node->right){
			node *right_key_node = key_node->right, *r_par = key_node;
			while (right_key_node->left){
				r_par = right_key_node;
				right_key_node = right_key_node->left;
			}
			//step 1: detach left subtree from key_node and attach it to right_key_node
			right_key_node->left = key_node->left;
			key_node->left = nullptr;
			//step 2: detach right subtree from right_key_node  
			node *rknr = right_key_node->right;
			right_key_node->right = nullptr;
			//step 3: attach it correctly to r_par
			if (r_par->left == right_key_node)
				r_par->left = rknr;
			else
				r_par->right = rknr;
			//step 4: right subtree key_node->right subtree of right_key_node
			right_key_node->right = key_node->right;
			//step 5: replacelink with parent
			changeLinks(par, key_node, right_key_node);
			if (root->val == key)
				root = right_key_node;
		}
		else{
			if (root->val == key)
				root = key_node->left;
			changeLinks(par, key_node, key_node->left);
		}
		cout << "Deletion of "<<key<<" Successful!" << endl;
		return;// true;
	}
};
int main(void){
	BST bt;
	vector<int> arg{ 50, 20, 80, 10, 30, 70, 90, 60, 75, 65, 64, 66 };
 	for (int i : arg)
		bt.insert(i);
	bt.inOrder(bt.root);
	cout << endl;
	bt.remove(50);
	bt.inOrder(bt.root);
	cout << endl;
	int in;
	cin >> in;
	return 0;
}
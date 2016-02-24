struct node{
	int val;
	node *left, *right;
	node(){}
	node(int x) :val(x), left(nullptr), right(nullptr){}
	node(int x, node* l, node *r) :val(x), left(l), right(r){}
};
typedef node TreeNode;
void inOrd(TreeNode *r, vector<int> &v){
	if (r){
		inOrd(r->left, v);
		v.push_back(r->val);
		inOrd(r->right, v);
	}
}
bool twoSumBST1(TreeNode *r, int x){
	//idea is to store inorder traversal in a list and since it's sorted we can use binary search
	//complexity: O(logn), space: O(n)
	vector<int> v;
	inOrd(r, v);
	int l = 0, rt = v.size() - 1;
	bool ok = false;
	while (l < rt){
		if (v[l] + v[rt] == x){
			ok = true;
			break;
		}
		if (v[l] + v[rt] > x)
			rt--;
		else
			l++;
	}
	if (ok){
		cout << "2Sum found, values are:" << v[l] << " " << v[rt] << endl;
	}
	return ok;
}
bool twoSumBST2(TreeNode *r, int x){
	//Complexity: O(n), space: O(logn)
	//Idea: Do iterative in-order and reverse-in-order traversal on the tree and compare the node sums with x to decide
	//which traversal to freeze and which one to continue, whether to exit if - i) n1 + n2 == x ii) n1>=n2
	stack<TreeNode*> s1, s2;
	int val1, val2;
	bool done1 = false, done2 = false;
	TreeNode *cur1 = r, *cur2 = r;
	while (1){
		while (!done1){
			if (cur1){
				s1.push(cur1);
				cur1 = cur1->left;
			}
			else{
				if (s1.empty())
					done1 = true;
				else{
					cur1 = s1.top();
					s1.pop();
					val1 = cur1->val;
					cur1 = cur1->right;
					done1 = true;//unlike normal iterative inorder, we want to break out
				}
				
			}
		}
		while (!done2){
			if (cur2){
				s2.push(cur2);
				cur2 = cur2->right;
			}
			else{
				if (s2.empty())
					done2 = true;
				else{
					cur2 = s2.top();
					s2.pop();
					val2 = cur2->val;
					cur2 = cur2->left;
					done2 = true;//unlike normal iterative inorder, we want to break out
				}
			}
		}
		if (val1 != val2&&val1 + val2 == x){
			cout << "2Sum(II) found:" << val1 << " " << val2 << endl;
			return true;
		}
		if (val1 + val2 < x){
			done1 = false;
		}
		if (val1 + val2 > x){
			done2 = false;
		}
		if (val1 >= val2)
			return false;
	}
}
int main(){
	TreeNode *r = new TreeNode(15, new TreeNode(10, new TreeNode(8), new TreeNode(12)), new TreeNode(20));
	r->right->left = new TreeNode(16);
	r->right->right = new TreeNode(25);
	cout << twoSumBST1(r, 33) << endl;
	cout << twoSumBST2(r, 33) << endl;
	getchar();
}
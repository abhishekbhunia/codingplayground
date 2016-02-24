//1. Height & Diameter
int getHeight(TreeNode *r){
	//O(n)
	if (!r)
		return 0;
	return 1 + max(getHeight(r->left), getHeight(r->right));
}
int getDiam(TreeNode *r){
	//TC: O(n^2) as it's calling getHeight(O(n)) for every node
	if (!r)
		return 0;
	int lh = getHeight(r->left);
	int rh = getHeight(r->right);
	return max(lh + rh + 1, max(getDiam(r->left), getDiam(r->right)));
}
int getDiam2(TreeNode *r, int *height){
	//TC: O(n)
	if (!r){
		*height = 0;
		return 0;
	}
	int lh = 0, rh = 0;
	int ld = getDiam2(r->left, &lh);
	int rd = getDiam2(r->right, &rh);
	*height = max(lh, rh) + 1;
	return max(lh + rh + 1, max(ld, rd));
}
//2. Equal Tree & Subtree
bool equalTree(TreeNode *r1, TreeNode *r2){
	if (!r1&&!r2)
		return true;
	if (!r1 || !r2)
		return false;
	return (r1->val == r2->val&&equalTree(r1->left, r2->left) && equalTree(r1->right, r2->right));
}
bool isSubTree(TreeNode *r1, TreeNode *r2){
	if (!r2)
		return true;
	if (!r1)
		return false;
	if (equalTree(r1, r2))
		return true;
	return equalTree(r1->left, r2) || equalTree(r1->right, r2);
}
void test_subtree(){
	//			    26                      
	//			   /  \
	//			  10   3
	//			 / \    \
	//		    4   6    3
	//			 \
	//			 30
	//		
	//			   10 
	//			  /  \     
	//		     4    6     
	//			  \
	//			  30
	TreeNode *r1 = new TreeNode(26, new TreeNode(10, new TreeNode(4, nullptr, new TreeNode(30)), new TreeNode(6)), new TreeNode(3, nullptr, new TreeNode(3)));
	TreeNode *r2 = new TreeNode(10, new TreeNode(4, nullptr, new TreeNode(30)), new TreeNode(6));
	cout << isSubTree(r1, r2) << endl;
}
//3. Isomorphic Tree

//4. Single Values Subtrees
bool singvalsubtree(TreeNode *r,int &cnt){
	if (!r)
		return true;
	if (!r->left&&!r->right){
		cnt++;
		return true;
	}
		
	bool ls = singvalsubtree(r->left, cnt);
	bool rs = singvalsubtree(r->right, cnt);
	if (ls&&rs){
		if (r->left&&r->left->val != r->val)
			return false;
		if (r->right&&r->right->val != r->val)
			return false;
		cnt++;
		return true;
	}
	return false;
}
void test_singlevalsubtree(){
	TreeNode *r1 = new TreeNode(5, new TreeNode(1, new TreeNode(5), new TreeNode(5)), new TreeNode(5, nullptr, new TreeNode(5)));
	TreeNode *r2 = new TreeNode(5, new TreeNode(4, new TreeNode(4), new TreeNode(4)), new TreeNode(5, nullptr, new TreeNode(5)));
	int cnt = 0;
	singvalsubtree(r1, cnt);
	cout << cnt << endl;
	cnt = 0;
	singvalsubtree(r2, cnt);
	cout << cnt << endl;
}

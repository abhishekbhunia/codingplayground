#include<iostream>
#include<deque>
using namespace std;
class BST{
public:
	int val;
	BST *left, *right;
	BST(int x, BST *l = nullptr, BST *r = nullptr) :val(x), left(l), right(r){}
};
pair<BST*, BST*> BSTtoDLL(BST *r){
	if (!r)
		return{ nullptr, nullptr };
	auto l = BSTtoDLL(r->left);
	auto rt = BSTtoDLL(r->right);
	if (l.second)
		l.second->right = r;
	r->left = l.second;
	if (rt.first)
		rt.first->left = r;
	r->right = rt.first;
	return{ l.first ? l.first : r, rt.second ? rt.second : r };
}
BST* DLLtoBST(BST **L, int low, int high){
	if (low >= high)
		return nullptr;
	int mid = low + ((high - low) >> 1);
	BST* lt = DLLtoBST(L, low, mid);
	BST* cur_root = *L;
	*L = (*L)->right;
	cur_root->left = lt;
	cur_root->right = DLLtoBST(L, mid + 1, high);
	return cur_root;	
}
void printLevelOrder(BST *r){
	if (r){
		deque<BST*> cur{r }, nxt;
		while (!cur.empty()){
			BST *tmp = cur.front();
			if (tmp){
				cout << tmp->val << " ";
				nxt.push_back(tmp->left);
				nxt.push_back(tmp->right);
			}
			cur.pop_front();
			if (cur.empty()){
				swap(cur, nxt);
				cout << endl;
			}
		}
	}
}
void appendNode(BST **li, BST **tail){
	(*tail)->right = (*li);
	*tail = (*li);
	(*li) = (*li)->right;
	//cout << "here" << endl;
}
BST* mergeLists(BST *L, BST *R){
	if (!L&&R)
		return R;
	if (!R&&L)
		return L;
	if (!L&&!R)
		return nullptr;
	
	BST *head = new BST(0), *tail = head;
	while (L&&R){
		appendNode((L->val < R->val) ? &L : &R, &tail);
	}
	
	if (L)
		appendNode(&L, &tail);
	if (R)
		appendNode(&R, &tail);
	//cout << "Returnning: " << head->val << endl;
	return head->right;
}
int main(void){
	//									      25(0)
	//							17(-1)				       32(1)
	//					12(-2)			19(0)		30(0)			35(2)
	// bottom view: 12,17,30,32,35
	BST *root = new BST(25);
	root->left = new BST(17);
	root->right = new BST(32);
	root->left->left = new BST(12);
	root->left->right = new BST(19);
	root->right->left = new BST(30);
	root->right->right = new BST(35);
	printLevelOrder(root);
	BST *li = BSTtoDLL(root).first, *tmp = li;
	int sz = 0;
	while (tmp != nullptr){
		cout << tmp->val << " ";
		tmp = tmp->right;
		sz++;
	}
	cout << endl;
	tmp = li;
	BST *x = DLLtoBST(&tmp,0,sz);
	printLevelOrder(x);


	//CREATE BST 2(17,50)
	//			  27
	//	    21			40
	// 18       24   37     49
	BST *root2 = new BST(27, new BST(21, new BST(18), new BST(24)), new BST(40, new BST(37), new BST(49)));
	printLevelOrder(root2);

	//FLATTEN BST 1 & 2
	BST *li1 = BSTtoDLL(root).first, *li2 = BSTtoDLL(root2).first;
	//MERGE TWO LISTS
	BST *li3 = mergeLists(li1, li2), *tmp2 = li3;
	sz = 0;
	while (tmp2 != nullptr){
		cout << tmp2->val << " ";
		tmp2 = tmp2->right;
		sz++;
	}
	//REBUILD BST
	BST *merged_bst = DLLtoBST(&li3, 0, sz);
	cout << endl;
	printLevelOrder(merged_bst);
	int in;
	cin >> in;
	return 0;

}
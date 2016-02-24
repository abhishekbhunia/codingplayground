#include<iostream>
#include<memory>
using namespace std;
struct node{
	int val;
	shared_ptr<node> next;
	node(){}
	node(int x, shared_ptr<node> y) :val(x), next(y){}
};
typedef shared_ptr<node> spnode;
 
void bar(spnode &head, spnode &tail, spnode &n){
	(!head) ? head = n : tail->next=n;
	tail = n;
	n = n->next;
}
spnode foo(spnode a, spnode b){
	spnode head = nullptr, tail = nullptr;
	while (a&&b){
		bar(head, tail, a->val < b->val ? a : b);
	}
	if (a)
		tail->next = a;
	if (b)
		tail->next = b;
	return head;
}
void prlist(spnode a){
	while (a){
		cout << a->val << " ";
		a = a->next;
	}
	cout << endl;
}
int main(void){
	spnode a = make_shared<node>(1, make_shared<node>(5, make_shared<node>(10, make_shared<node>(12, make_shared<node>(25, make_shared<node>(50, nullptr))))));
	spnode b = make_shared<node>(3, make_shared<node>(7, make_shared<node>(8, nullptr)));
	
	spnode res = foo(a, b);
	prlist(res);

	int inp;
	cin >> inp;
	return 0;

}
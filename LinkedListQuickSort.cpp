//NOT WORKING
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define pnl cout<<endl

struct node{
	int val;
	node *next;
	node(int x) :val(x), next(nullptr){}
};
typedef node ListNode;
void pl(ListNode *h){
	while (h){
		cout << h->val << " ";
		h = h->next;
	}
	pnl;
}
ListNode* getTail(ListNode *head){
	while (head&&head->next)
		head = head->next;
	return head;
}
void plht(ListNode *h, ListNode *t){
	if (h){
		while (h){
			cout << h->val << " ";
			h = h->next;
		}
	}
}
ListNode* partition(ListNode *head, ListNode *end, ListNode **newHead, ListNode **newEnd){
	ListNode *pivot = end, *prev = nullptr, *cur = head, *tail = end;

	while (cur != pivot){
		if (cur->val < pivot->val){
			if (!(*newHead))
				*newHead = cur;
			prev = cur;
			cur = cur->next;
		}
		else{
			if (prev)
				prev->next = cur->next;
			ListNode *temp = cur->next;
			cur->next = nullptr;
			tail->next = cur;
			tail = cur;
			cur = temp;
		}
	}
	if (!(*newHead))
		(*newHead) = pivot;
	(*newEnd) = tail;
	cout << "Partition:"; //plht(*newHead, *newEnd);
	return pivot;
}
ListNode* qsortListHelper(ListNode *head, ListNode *end){
	if (!head || head == end)
		return head;
	ListNode *newHead = nullptr, *newEnd = nullptr;
	ListNode *pivot = partition(head, end, &newHead, &newEnd);
	if (pivot != newHead){
		ListNode *temp = newHead;
		while (temp != pivot)
			temp = temp->next;
		temp->next = nullptr;

		//imp step to understand
		newHead = qsortListHelper(newHead, temp);

		temp = getTail(newHead);
		temp->next = pivot;
	}

	pivot->next = qsortListHelper(pivot->next, newEnd);
	return newHead;
}
ListNode* qsortList(ListNode **head){
	return qsortListHelper(*head, getTail(*head));
}
int main(){
	ListNode *head = new ListNode(4);
	head->next = new ListNode(-3);
	head->next->next = new ListNode(8);
	head->next->next->next = new ListNode(0);
	head->next->next->next->next = new ListNode(-20);

	pl(head);
	head = qsortList(&head);
	pl(head);

	getchar();
}
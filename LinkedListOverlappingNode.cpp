#include <iostream>
#include <memory>
using namespace std;
template <typename T>
struct node{
	T val;
	shared_ptr<node<T>> next;
};
template <typename T>
shared_ptr<node<T>> hasCycle(const shared_ptr<node<T>> &head){
	return nullptr;

}
template <typename T>
shared_ptr<node<T>> findOverlappingNode(const shared_ptr<node<T>> &head1,const shared_ptr<node<T>> &head2){
	return nullptr;

}

template <typename T>
shared_ptr<node<T>> findGeneralOverlap(const shared_ptr<node<T>> &head1,const shared_ptr<node<T>> &head2){
	shared_ptr<node<T>> s1=hasCycle(head1), s2=hasCycle(head2);

	if(!s1&&!s2)
		return findOverlappingNode(head1,head2);

	else if(s1&&s2){
		shared_ptr<node<T>> temp=s1;
		do{
			temp=temp->next;
		}while(temp!=s1&&temp!=s2)
		return temp==s2?s2:nullptr
;	}

	return nullptr;

}
template <typename T>
void printList(const shared_ptr<node<T>> &head){
	shared_ptr<node<T>> temp=head;
	while(temp){
		cout<<temp->val<<" ";
		temp=temp->next;
	}
	cout<<endl;
}
int main(void){
	//Preparing L1
	shared_ptr<node<int>> head1=make_shared<node<int>>(node<int>{1,nullptr});
	shared_ptr<node<int>> a=make_shared<node<int>>(node<int>{2,nullptr});
	head1->next=a;

	shared_ptr<node<int>> b=make_shared<node<int>>(node<int>{3,nullptr});
	a->next=b;
	
	shared_ptr<node<int>> c=make_shared<node<int>>(node<int>{4,nullptr});
	b->next=c;
	
	shared_ptr<node<int>> d=make_shared<node<int>>(node<int>{5,nullptr});
	c->next=d;
	
	//Preparing L2
	shared_ptr<node<int>> head2=make_shared<node<int>>(node<int>{6,nullptr});
	shared_ptr<node<int>> a2=make_shared<node<int>>(node<int>{7,nullptr});
	head2->next=a2;
	
	shared_ptr<node<int>> b2=make_shared<node<int>>(node<int>{8,nullptr});
	a2->next=b2;

	//Connecting L1 & L2
	b2->next=c;
	
	shared_ptr<node<int>> res=findGeneralOverlap(head1,head2);
	if(res)
	    cout<<"Overlapping Node: "<<res->val;						
	else{
	    //  
	}
	
	printList(head2);
	int inp;
	cin>>inp;
	return 0;
}
// Reverse a linked list
#include <iostream>
#include <memory>
using namespace std;
template <typename T>
struct node{
    T val;
    shared_ptr<node<T>> next;
};
template <typename T>
shared_ptr<node<T>> reverseListRecursive(shared_ptr<node<T>> &head){//builds reversed list from end: prefix normal, suffix reversed
    if(!head||!head->next)//guard against null list; base case for list with a single node
        return head;
    shared_ptr<node<T>> new_head=reverseListRecursive(head->next);
    head->next->next=head;
    head->next=nullptr;
    return new_head;
}
template <typename T>
shared_ptr<node<T>> reverseListIterative(shared_ptr<node<T>> &head){//builds reversed list from front: prefix reversed, suffix normal
    shared_ptr<node<T>> prev=nullptr,curr=head;
    while(curr){
       shared_ptr<node<T>> temp=curr->next;
       curr->next=prev;
       prev=curr;
       curr=temp;
    }
    return prev;
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
int main()
{
    shared_ptr<node<int>> head=make_shared<node<int>>(node<int>{1,nullptr});
    shared_ptr<node<int>> a=make_shared<node<int>>(node<int>{2,nullptr});
    head->next=a;
    shared_ptr<node<int>> b=make_shared<node<int>>(node<int>{3,nullptr});
    a->next=b;
    shared_ptr<node<int>> c=make_shared<node<int>>(node<int>{4,nullptr});
    b->next=c;
    printList(head);    
    shared_ptr<node<int>> rev=reverseListRecursive(head);
    printList(rev);
    rev=reverseListRecursive(rev);
    printList(rev);
    rev=reverseListIterative(rev);
    printList(rev);
    int inp;
    cin>>inp;
    return 0;
}

// Check if a linked list is palidrome
#include <iostream>
#include <memory>
using namespace std;
template <typename T>
struct node{
    T val;
    shared_ptr<node<T>> next;
};
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
template <typename T>
bool checkPalindrome(shared_ptr<node<T>> &head){
    shared_ptr<node<T>> slow=head,fast=head;
    //find the middle
    while(fast&&fast->next){
        slow=slow->next;
        fast=fast->next->next;
    }
    //reverse the second half, staring from the middle
    slow=reverseListIterative(slow);
    //compare two halves
    fast=head;
    while(slow){
        if(slow->val!=fast->val)
        {
            slow=reverseListIterative(slow);//only required if the list structure is to be restored
            return false;
        }
            
        slow=slow->next;
        fast=fast->next;
    }
    slow=reverseListIterative(slow);//only required if the list structure is to be restored
    return true;
}
int main()
{
    shared_ptr<node<char>> head=make_shared<node<char>>(node<char>{'a',nullptr});
    shared_ptr<node<char>> a=make_shared<node<char>>(node<char>{'b',nullptr});
    head->next=a;
    cout<<checkPalindrome(head)<<endl;
    shared_ptr<node<char>> b=make_shared<node<char>>(node<char>{'b',nullptr});
    a->next=b;
    shared_ptr<node<char>> c=make_shared<node<char>>(node<char>{'b',nullptr});
    b->next=c;
    cout<<checkPalindrome(head)<<endl;
    shared_ptr<node<char>> d=make_shared<node<char>>(node<char>{'a',nullptr});
    c->next=d;
    cout<<checkPalindrome(head)<<endl;
    int inp;
    cin>>inp;
    return 0;
}

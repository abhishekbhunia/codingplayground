// Example program
#include <iostream>
#include <string>
#include <memory>
using namespace std;
template <typename T>
struct Node{
    T val;
    shared_ptr<Node<T>> next;
};
template <typename T>
shared_ptr<Node<T>> findCycle(const shared_ptr<Node<T>> &head){
    shared_ptr<Node<T>> fast=head,slow=head;
    while(fast&&fast->next&&fast->next->next){
        fast=fast->next->next;
        slow=slow->next;        
        if(fast==slow){
            int looplen=0;
            do{
                slow=slow->next;
                looplen++;
            }while(slow!=fast);
            slow=head;
            fast=head;
            while(looplen--){
                fast=fast->next;
            }
            while(slow!=fast){
                slow=slow->next;
                fast=fast->next;
            }
            return slow;
        }
    }
    return nullptr;
}
template <typename T>
void printList(const shared_ptr<Node<T>> &head){
    shared_ptr<Node<T>> ref=head;
    while(ref){
        cout<<ref->val<<" ";
        ref=ref->next;
    }
    cout<<endl;
}
int main()
{
    shared_ptr<Node<int>> l5=make_shared<Node<int>>(Node<int>{5,nullptr});
    shared_ptr<Node<int>> l4=make_shared<Node<int>>(Node<int>{4,l5});
    shared_ptr<Node<int>> l3=make_shared<Node<int>>(Node<int>{3,l4});
    shared_ptr<Node<int>> l2=make_shared<Node<int>>(Node<int>{2,l3});
    shared_ptr<Node<int>> l1=make_shared<Node<int>>(Node<int>{1,l2});
    l5->next=l3;
    //printList(l1);
    shared_ptr<Node<int>> res=findCycle(l1);
    if(res==nullptr)
        cout<<"There is no cycle"<<endl;
    else
        cout<<"Cycle starts at:"<<res->val<<endl;
    int inp;
    cin>>inp;
    return 0;        
}

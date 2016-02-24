// Check if a linked list is palidrome
#include <iostream>
#include <memory>
using namespace std;

struct node{
    char val;
    shared_ptr<node> next;
    node(char x, shared_ptr<node> y) :val(x), next(y){}
};
typedef shared_ptr<node> spnode;

spnode reverseListIterative(spnode &head){//builds reversed list from front: prefix reversed, suffix normal
    spnode prev = nullptr, curr = head;
    while (curr){
        spnode temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    return prev;
}
 
void printList(const spnode &head){
    spnode temp = head;
    while (temp){
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;
}
 
bool checkPalindrome(spnode &head){
    spnode slow = head, fast = head;
    //find the middle
    while (fast&&fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    //reverse the second half, staring from the middle
    slow = reverseListIterative(slow);
    //compare two halves
    fast = head;
    while (slow){
        if (slow->val != fast->val)
        {
            slow = reverseListIterative(slow);//only required if the list structure is to be restored
            return false;
        }

        slow = slow->next;
        fast = fast->next;
    }
    slow = reverseListIterative(slow);//only required if the list structure is to be restored
    return true;
}
int main()
{
    spnode head = make_shared<node>('a', make_shared<node>('b', make_shared<node>('b',make_shared<node>('a', nullptr))));
    cout << checkPalindrome(head) << endl;
    int inp;
    cin >> inp;
    return 0;
}

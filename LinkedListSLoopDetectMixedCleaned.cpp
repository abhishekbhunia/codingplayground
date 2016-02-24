#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<memory>
using namespace std;
struct node{
    //public:
    int val;
    shared_ptr<node> next;
    node(){}
    node(int x, shared_ptr<node> y) :val(x), next(y){}
};
typedef shared_ptr<node> spnode;
spnode reverse_rec(spnode head){
    if (!head || !head->next)
        return head;
    spnode new_head = reverse_rec(head->next);
    head->next->next = head;
    head->next = nullptr;
    return new_head;
}
spnode reverse_iter(spnode head){
    spnode prev = nullptr, cur = head;
    while (cur){
        spnode tmp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = tmp;
    }
    return prev;
}
void prlist(spnode head){
    while (head){
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}
int lennode(spnode head){
    int len = 0;
    while (head){
        len++;
        head = head->next;
    }
    return len;
}
void advanceNode(spnode head, int len){
    while (len--){
        head = head->next;
    }
}
pair<bool, spnode> doesIntersect(spnode a, spnode b){
    int lena = lennode(a);
    int lenb = lennode(b);
    advanceNode(lena>lenb ? a : b, abs(lena - lenb));
    while (a&&b){
        if (a == b)
            return make_pair(true, a);
        a = a->next;
        b = b->next;
    }
    return make_pair(false, nullptr);
}
pair<bool, spnode> hasCycle(spnode head){

    spnode slow = head, fast = head;
    while (fast&&fast->next&&fast->next->next){
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast){
            int looplen = 0;
            do{
                looplen++;
                slow = slow->next;
            } while (slow != fast);
            slow = head; fast = head;
            while (looplen--)
                slow = slow->next;
            while (slow != fast){
                slow = slow->next; fast = fast->next;
            }
            return make_pair(true, slow);
        }
    }
    return make_pair(false, nullptr);
}
pair<bool, spnode> genOverlapNode(spnode a, spnode b){
    spnode cyc1 = hasCycle(a).second, cyc2 = hasCycle(b).second;
    //only one has a cycle=>no overlapping possible
    if ((cyc1&&!cyc2) || (!cyc1&&cyc2))
        return make_pair(false, nullptr);
    //both have cycle
    else if (cyc1&&cyc2){
        /*
        if(cyc2.second==cyc1.second)
        return make_pair(true,cyc2.second);
        else
        return make_pair(false,nullptr);
        */
        //1: separete cycles 2.single node of entry to the cycle 3.separate node of entry to the cycle
        spnode t = cyc1;
        cout <<endl<< t->val << " "<<cyc2->val<<endl;
        do{
            t = t->next; 
            cout << "loop" << endl;
        } while (t != cyc1 && t != cyc2);
        if (t == cyc2)
            return make_pair(true, t);
        else
            return make_pair(false, nullptr);
    }
    else{
        return doesIntersect(a, b);
    }
}
int main(void){
    //for just testing intersection
    spnode head = make_shared<node>(1, make_shared<node>(2, make_shared<node>(3, make_shared<node>(4, make_shared<node>(5, nullptr)))));
    spnode head2 = make_shared<node>(6, make_shared<node>(7, nullptr));
    //for just testing cycle
    spnode head3 = make_shared<node>(11, make_shared<node>(12, make_shared<node>(13, make_shared<node>(14, make_shared<node>(15, nullptr)))));
    spnode b = head2; b = b->next; spnode a = head; a = a->next->next;
    //cout<<b->val<<a->val;
    b->next = a;
    prlist(head2);
    a = head; b = head2;
    cout << endl << doesIntersect(a, b).first << endl;
    //create a loop in c (13,14,15)
    spnode c = head3;
    spnode c1 = c->next->next->next->next, c2 = c->next->next; c1->next = c2;
    pair<bool, spnode> ret = hasCycle(c);
    if (ret.first){
        cout << "C:Has Cycle:" << ret.second->val << endl;
    }
    else {
        cout << "C:No Cycle" << endl;
    }
    a = head, b = head2;
    ret = hasCycle(a);
    if (ret.first){
        cout << "A:Has Cycle:" << ret.second->val << endl;
    }
    else {
        cout << "A:No Cycle" << endl;
    }
    cout << "General Overlap Test:" << endl;
    a = head, b = head2, c = head3;

    cout << "a,b(linear):";//linear
    ret = genOverlapNode(a, b);
    if (ret.first){
        cout << ret.second->val << endl;
    }
    else {
        cout << "No overlap" << endl;
    }
    cout << "b,c(common loop, different entry):";//different entry:should print out c's entry to the loop
    a = head, b = head2, c = head3;

    b->next->next = c->next->next->next;

    //cout << b->next->val;
    b = head2, c = head3;
    ret = genOverlapNode(b, c);
     
    if (ret.first){
        cout << ret.second->val << endl;
    }
    else {
        cout << "No overlap" << endl;
    }
    cout << "b,c(common loop, same entry):";//same entry:should print out c's entry to the loop
    a = head, b = head2, c = head3;
    b->next->next = c->next->next;
    b = head2, c = head3;
    ret = genOverlapNode(b, c);
    if (ret.first){
        cout << ret.second->val << endl;
    }
    else {
        cout << "No overlap" << endl;
    }
    cout << "a,c(non intersecting unshared loops):";//same entry:should print out c's entry to the loop
    a = head, b = head2, c = head3;
    a->next->next->next->next->next = a->next->next;
    a = head, c = head3;
    ret = genOverlapNode(a, c);
    if (ret.first){
        cout << ret.second->val << endl;
    }
    else {
        cout << "No overlap" << endl;
    }
    int in;
    cin >> in;
    return 0;
}
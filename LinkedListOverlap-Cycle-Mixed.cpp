#include<iostream>
#include<memory>
using namespace std;


struct node{
	int val;
	shared_ptr<node> next;
	node(int x, shared_ptr<node> y) :val(x), next(y){}
};
typedef shared_ptr<node> spnode;

void moveKsteps(int k, spnode &h){
	while (k--)
		h = h->next;
}
/*
spnode hasCycle(spnode &a){
	spnode one = a, two = a;
	while (two&&two->next&&two->next->next){
		one = one->next;
		two = two->next->next;
		if (one == two){
			int len = 0;
			do{
				one = one->next;
				len++;
			} while (one != two);
			one = a, two = a;
			while (len--)
				one = one->next;
			while (one != two){
				one = one->next;
				two = two->next;
			}
			return one;
		}
	}
	return nullptr;
}*/
spnode interSection(spnode &a, spnode &b){
	if (!a || !b)
		return nullptr;

	//FIND LENGHTS
	int lena = 0, lenb = 0;
	spnode ta = a, tb = b;
	while (ta){
		ta = ta->next;
		lena++;
	}
	while (tb){
		tb = tb->next;
		lenb++;
	}
	int diff = lena - lenb > 0 ? lena - lenb : lenb - lena;

	//
	if (lena != lenb){
		moveKsteps(diff, lena - lenb > 0 ? a : b);
	}
	
	//
	while (a&&b){		
		a = a->next;
		b = b->next;
		if (a == b)
			break;
	}
	if (a == b)
		return a;
	return nullptr;
}
spnode hasCycle(spnode &head){
	spnode one = head, two = head;
	while (two&&two->next&&two->next->next){
		two = two->next->next;
		one = one->next;
		//len = 0;
		if (one == two){
			int looplen = 0;
			do{
				one = one->next;
				looplen++;
			} while (one != two);
			one = head, two = head;
			while (looplen--)
				one = one->next;
			while (one != two){
				one = one->next;
				two = two->next;
			}
			return two;
		}
	}
	return nullptr;
}
spnode findGenOverlap(spnode &a, spnode &b){
	//if both have loops/none has loops->intersection can be there
	//if one has loop, not the other->no intersection possible
	if ((hasCycle(a) && !hasCycle(b)) || (!hasCycle(a) && hasCycle(b))){
		cout << "Separate Lists, one is cyclic\n";
		return nullptr;
	}
		
	if (!hasCycle(a) && !(hasCycle(b))){
		cout << "Intersecting lists with no cycle\n";
		return(interSection(a, b));
	}
		
	else//1. overlapping cycle 2. separate lists with cycle
	{
		
		spnode x = hasCycle(a), y=hasCycle(b), temp=x;
		cout << "Intersecting list with cycle\n" << x->val << " " << y->val << endl;
		do{
			temp = temp->next;
		} while (temp != x&&temp != y);
		return temp == y ? y : nullptr;
	}		

}

void pee(spnode h){
	while (h){
		cout << h->val << " ";
		h = h->next;
	}
	cout << endl;
}
int main(void){
	spnode r = make_shared<node>(1, make_shared<node>(2, make_shared<node>(3, make_shared<node>(4, make_shared<node>(5,nullptr)))));
	spnode s = make_shared<node>(6, make_shared<node>(7, nullptr));

	

	spnode a = r, b = s;
	a = a->next->next;//3
	b = b->next;//b=7
	b->next = a;//b,a=3
	
	//make common cycle
	a = a->next->next;//a=5
	a->next = b->next;
	a = r, b = s;
	
	//pee(a);
	//pee(b);
	
	a = r, b = s;
	spnode ret = findGenOverlap(a, b);
	
	if (ret){
		cout << "Intersection Val: "<<ret->val << endl;
	}
	else
		cout << "no intersections" << endl;

	


	
	int inp;
	cin >> inp;
	return 0;
}
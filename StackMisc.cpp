//1. Greater element in an array: O(n) time O(n) space
void nextGreater(vector<int> v){
	stack<int> s;
	s.push(v[0]);
	for (int i = 1; i < v.size(); i++){
		if (s.empty())
			s.push(v[i]);
		else{
			while (!s.empty()&&v[i] > s.top()){
				cout << v[i] << ">" << s.top() << endl;
				s.pop();
			}
			s.push(v[i]);
		}		
	}
	while (!s.empty()){
		cout << s.top() << ">" << numeric_limits<int>::min() << endl;
		s.pop();
	}
}
void test_nextGreaterStack(){
	vector<int> v{ 11, 13, 21, 3 };
	nextGreater(v);
}

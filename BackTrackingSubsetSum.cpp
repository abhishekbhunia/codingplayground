bool subsetsumHelper(vector<int> v, vector<int> &ret, int sum, int ix=0){
	if (sum == 0)
		return true;
	if (ix == v.size())
		return false;
	for (int i = ix; i < v.size(); ++i){
		ret.push_back(v[i]);
		//cout << "ret:"; pv(ret);
		if (subsetsumHelper(v, ret, sum - v[i], i + 1))
			return true;
		ret.pop_back();
		//cout << "ret after pop:"; pv(ret);
	}
	return false;
}
void subsetsum(){
	vector<int> v{ 10, -6, 5, 18, 12, 20, 15 },ret;
	int sum = 23;
	pv(v);
	if (subsetsumHelper(v, ret, sum)){
		pv(ret);
	}
	else{
		cout << "required subset not found\n";
	}
}
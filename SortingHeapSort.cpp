void heapify(vector<int> &v, int root, int size){
	//algo: identify the smallest index, if it's not the root, swap and recurse on the swapped
	//position as heap would be unbalanced after swap
	//Complexity: O(logn) as maximum number of swap is proportional to height of the heap
	int l = 2 * (root + 1) -1;
	int r = l + 1;

	int largest = root;
	if (l < size&&v[largest] < v[l])
		largest = l;
	if (r < size&&v[largest] < v[r])
		largest = r;
	if (largest != root){
		//after swap, largest points to root of unbalanced heap so recurse from there
		swap(v[root], v[largest]);
		heapify(v, largest, size);
	}	
}
void build_heap(vector<int> &v, int size){
	//calls heapify for arr[0...length/2] bottom up 
	for (int i = size / 2; i >= 0; i--)
		heapify(v, i, size);
}
void heapsort(vector<int> &v, int size){
	//1. build heap O(nlogn) tight bounds to O(n): O(logn) for heapify
	build_heap(v, v.size());
	//2. sort
	//algo: hsz=size; for i in size-1...1: swap(v[0],v[i])--->heapify(v,0,--hsz)
	int sz = size;
	for (int i = size - 1; i >= 1; i--){
		swap(v[0], v[i]);
		heapify(v, 0, --sz);
	}
	
}
void test_heapsort(){
	vector<int> v;
	for (int i = 0; i < 10; ++i)
		v.push_back(rand() % 100 - 10);
	pv(v);  
	heapsort(v, v.size());
	pv(v);	 
}
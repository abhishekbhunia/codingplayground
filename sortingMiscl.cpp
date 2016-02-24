//1. Dutch National Flag
void dnf(vector<int> &v){
	// |<-----0's: 0 to low-1---->|<----1's: low to mid-1---->|<----unknowns: mid to high---->|<----2's: high+1 to n-1---->|
	// idea is to shrink [mid,high] and populate/uncover other regions by swapping
	int low=0, mid=0, high=0;
	while(low<=high){
		if(v[low]==0)
			swap(v[low++],v[mid++]);
		else if(v[low]==1)
			mid++;
		else
			swap(v[mid],v[high--]);
	}
}
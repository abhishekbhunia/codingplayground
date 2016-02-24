//matrix is sorted both row and columnwise
//elliminate one row/col in each iteration
#include <iostream>
#include <vector>
using namespace std;
pair<int,int> searchKin2Dsorted(const vector<vector<int>> &v,const int &k){
    int r=0,c=v.size()-1;     
    while(r<v.size()&&c>=0){
        if(v[r][c]==k)  
            return(make_pair(r,c));
        else if(k<v[r][c])
            c--;
        else
            r++;
    }
    return(make_pair(-1,-1));
}
int main(){
    vector<vector<int>> v(4,vector<int>(4,0));
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j)
            v[i][j]=10+2*i+3*j;
    }
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j
 )           cout<<v[i][j]<<" ";
        cout<<endl;
    }
    pair<int,int> res=searchKin2Dsorted(v,15);
    cout<<endl<<res.first<<" "<<res.second<<endl;
    return 0;
}
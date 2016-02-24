// program to print 2D array in circular fashion
#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <vector>
using namespace std;
void printCircular2DArray(const vector<vector<int>> &v,const int &offset)
{
    if((int)v.size()-1-offset==offset)//for odd dimensioned v
        cout<<v[offset][offset];
        
    for(int j=offset;j<(int)v.size()-1-offset;++j)
        cout<<v[offset][j]<<" ";
     
    for(int i=offset;i<(int)v.size()-1-offset;++i)
        cout<<v[i][(int)v.size()-1-offset]<<" ";
     
    for(int j=(int)v.size()-1-offset;j>offset;--j)
        cout<<v[(int)v.size()-1-offset][j]<<" ";
     
    for(int i=(int)v.size()-1-offset;i>offset;--i)
        cout<<v[i][offset]<<" ";
     
}
int main()
{
    int inp;
    cin>>inp;
    vector<vector<int>> a(inp,vector<int>(inp));
    for(int i=0;i<inp;i++){
        for(int j=0;j<inp;j++)
            a[i][j]=rand()%100;
    }
    for(int i=0;i<inp;i++){
        for(int j=0;j<inp;j++)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
    for(int offset=0;offset<ceil(.5*(int)a.size());++offset)
        printCircular2DArray(a,offset);
    cin>>inp;
    return 0;
}

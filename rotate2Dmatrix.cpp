// rotate 2D matrix
#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <iterator>
using namespace std;
void copyMat(vector<vector<int>> &d,const int &d_xs,const int &d_xe,const int &d_ys,const int &d_ye,const vector<vector<int>> &s,const int &sx,const int &sy)
{
    for(int i=0;i<d_xe-d_xs;++i){
        copy(s[sx+i].cbegin()+sy,s[sx+i].cbegin()+sy+d_ye-d_ys,d[i+d_xs].begin()+d_ys);    
    }
                
}
void rotateMat(vector<vector<int>> &v,const int &x_s,const int &x_e,const int &y_s,const int &y_e){
    if(x_e>x_s+1){
        int mid_x=x_s+((x_e-x_s)>>1),mid_y=y_s+((y_e-y_s)>>1);        
        vector<vector<int>> c(mid_x-x_s,vector<int>(mid_y-y_s));
        copyMat(c,0,c.size(),0,c.size(),v,x_s,y_s);
        copyMat(v,x_s,mid_x,y_s,mid_y,v,mid_x,y_s);
        copyMat(v,mid_x,x_e,y_s,mid_y,v,mid_x,mid_y);
        copyMat(v,mid_x,x_e,mid_y,y_e,v,x_s,mid_y);
        copyMat(v,x_s,mid_x,mid_y,y_e,c,0,0);
        
        rotateMat(v,x_s,mid_x,y_s,mid_y);
        rotateMat(v,x_s,mid_x,mid_y,y_e);
        rotateMat(v,mid_x,x_e,mid_y,y_e);
        rotateMat(v,mid_x,x_e,y_s,mid_y);
        
    }    
}
int main(){
    int inp;
    cin>>inp;
    vector<vector<int>> v(inp,vector<int>(inp));
    for(int i=0;i<v.size();++i){
        for(int j=0;j<v.size();++j){
            v[i][j]=rand()%1000;   
        }        
    }
    for(int i=0;i<v.size();++i){
        for(int j=0;j<v.size();++j){
            cout<<v[i][j]<<" ";   
        }
        cout<<endl;
    }
    cout<<endl;
    rotateMat(v,0,v.size(),0,v.size());
    for(int i=0;i<v.size();++i){
        for(int j=0;j<v.size();++j){
            cout<<v[i][j]<<" ";   
        }
        cout<<endl;
    }
    cin>>inp;
    return 0;   
}
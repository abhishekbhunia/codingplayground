#include <iostream>
#include <string>
#include <vector>
using namespace std;
//a more redable recursive printing
void print_LCS_recursive(string a, vector<vector<char>> S, int i, int j, string &ret){
	if (i == 0 || j == 0)
		return;
	else if (S[i][j] == 'x'){
		print_LCS_recursive(a, S, i - 1, j - 1,ret);
		//cout << a[i] << " ";
		ret.push_back(a[i]);
	}
	else if (S[i][j] == 'i')
		print_LCS_recursive(a, S, i - 1, j, ret);
	else
		print_LCS_recursive(a, S, i, j - 1, ret);
}
// GCS

string getRec(string a,vector<vector<char>> S,int m,int n){
    if(m==0||n==0)
        return "";
    else if(S[m][n]=='x'){
        return getRec(a,S,m-1,n-1)+a[m];
    }
    else if(S[m][n]=='i')
        return getRec(a,S,m-1,n);
    else
        return getRec(a,S,m,n-1);
}
string getIter(string a,vector<vector<char>> S,int m,int n){
    string ret="";
    while(m>0&&n>0){
        if(S[m][n]=='x'){
            ret = a[m] + ret;
            m--;
            n--;
        }
            
        else if(S[m][n]=='i')
            m--;
        else
            n--;
    }  
    return ret;
}
string gcs(string a,string b){
    if(a.length()==0||b.length()==0)
        return "";
    a = " "+a;
    b = " "+b;
    int lena=a.length(),lenb=b.length();
    
    vector<vector<int>> L;
    vector<vector<char>> S;
    
    for(int i=0;i<lena;i++){        
        L.push_back(vector<int>(lenb,0));
        S.push_back(vector<char>(lenb));
    }
    
    //populate distance array and mark arrays
    for(int i=1;i<lena;++i){
        for(int j=1;j<lenb;++j){
            if(a[i]==b[j]){
                L[i][j]=L[i-1][j-1]+1;
                S[i][j]='x';
            }
            else if(L[i-1][j]>L[i][j-1]){
                L[i][j]=L[i-1][j];
                S[i][j]='i';
            }
            else{
                L[i][j]=L[i][j-1];
                S[i][j]='j';
            }
        }
    }
    
    //string ret=getIter(a,S,lena-1,lenb-1);
    string ret=getRec(a,S,lena-1,lenb-1);
    return ret;
}
int main()
{
    string a="wbjkhioulwnipppal", b="bqwehuianeriqabb";
    cout<<gcs(a,b);

    int inp;
    cin>>inp;
    return 0;
}

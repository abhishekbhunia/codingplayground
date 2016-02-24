// Example program
#include <iostream>
#include <string>
#include <bitset>
using namespace std;
typedef unsigned int ui;
int main()
{
    ui x=23456890;
    bitset<32> xb(x);
    ui x2=x>>16;
    bitset<32> x2b(x2);
    //ui r=(1<<16)-1;
    //bitset<32> rb(r);
    //bitset<32> v(r&x>>16);
    cout<<sizeof(ui)<<endl<<xb<<endl<<x2b<<endl<<(((1<<16)-1)&x>>16)<<endl;
    
    return 0;
  
}

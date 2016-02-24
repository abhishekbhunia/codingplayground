// 0 sum subset mod n
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
using namespace std;
vector<int> foo(const vector<int> &v)
{
    vector<int> psum(v);//prefixsum vector. maps index->running sum%n. So it will contain numbers->[0,n-1]
    for (int i = 0; i<psum.size(); ++i){
        psum[i] += (i>0) ? psum[i - 1] : 0;
        psum[i] = psum[i] % psum.size();
    }

    vector<int> inv(psum.size(), -1);//inverted mapping. maps runningsum%n->index in psum where this runningsum%n was found

    for (int i = 0; i<psum.size(); ++i){
        if (psum[i] == 0){
            vector<int> res(i + 1);
            iota(res.begin(), res.end(), 0);
            return res;
        }
        else if (inv[psum[i]] != -1){
            vector<int> res(i - inv[psum[i]]);
            iota(res.begin(), res.end(), inv[psum[i]] + 1);            
            return res;
        }
        inv[psum[i]] = i;
    }

}
int main()
{
    int inp;
    cin >> inp;
    vector<int> v(inp);
    for (int i = 0; i<inp; ++i)
        v[i] = rand() % 100+1;
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    vector<int> r = foo(v);
    int sum = 0;
    for (auto it = r.begin(); it != r.end(); ++it)
    {
        cout << *it << ":" << v[*it] << " ";
        sum += v[*it];
    }
    cout << endl << "Sum: " << sum;
    cin >> inp;
    return 0;
}

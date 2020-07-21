#include <bits/stdc++.h>
using namespace std;
#include "StrBlobPtr.h"

int main() {
    # ifndef ONLINE_JUDGE
    // freopen("/home/wzy/learncpp/1.in","r",stdin);
    // freopen("/home/wzy/learncpp/1.out","w",stdout);
    #endif
    StrBlob a;
    a.push_back("1");
    a.push_back("2");
    auto p = StrBlobPtr(a.begin());
    cout << p.deref() << endl;
    p.incr();
    cout << p.deref() << endl;
    p.incr();
    cout << p.deref() << endl;
    p.incr();
    return 0;
}
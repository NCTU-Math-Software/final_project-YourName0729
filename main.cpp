#include <bits/stdc++.h>
 
#define For(i, n) for (int i = 0; i < n; ++i)
#define For1(i, n) for(int i = 1; i <= n; i++)
#define Forcase int __t = 0; cin >> __t; while (__t--)
#define pb push_back
#define ll long long
#define ull unsigned long long
#define ar array
 
using namespace std;
 
const int MOD = 1e9 + 7;
const ll INF = 1e18;

int pow3(int d) {
    if (d == 0) return 1;
    return 3 * pow3(d - 1);
}

// divisor = 3^a, repetend of 1/3^b, then construct repetend of 1/3^(a+b)
void recur(int divisor, vector<int>& repetend, vector<int>& rep) {
    int d = 0;
    For (i, divisor) {
        for (int p : repetend) {
            d *= 10;
            d += p;
            rep.push_back(d / divisor);
            d = d - d / divisor * divisor;
        }
        //cout << d << '\n';
    }
    /*do {
        for (int p : repetend) {
            d *= 10;
            d += p;
            rep.push_back(d / divisor);
            d = d - d / divisor * divisor;
        }
        cout << d << '\n';
    } while (d);*/
}

int main() {
    //ios_base::sync_with_stdio(0); cin.tie(0);

    vector<int> vec = {0, 3, 7};
    vector<int> ans;
    recur(27, vec, ans);
    for (auto d : ans) {
        cout << d;
    }
    cout << '\n';

    return 0;
}
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

vector<int> repeetend[17];

void generate_repeetend(int p, int q, vector<int>& rep) {
    vector<bool> vst(q);
    while (!vst[p]) {
        vst[p] = 1;
        p *= 10;
        rep.push_back(p / q);
        p = p - p / q * q;
    }
}

int dig(int k, int d, vector<int>& repeetend) {
    int p = 1;
    For (i, k)  p *= 3;
    if (d < p)  return 0;
    d -= p;
    return repeetend[d % repeetend.size()];
}

void output(int n) {
    stack<int> ans;
    int d = 0;
    for (int i = n + 15; i >= n - 1; i--) {
        //cout << i << '\n';
        for (int j = 1; j <= 16; j++) {
            d += dig(j, i, repeetend[j]);
        }
        ans.push(d % 10);
        d /= 10;
    }

    For (i, 10) {
        cout << ans.top();
        ans.pop();
    }
}

int main() {
    //ios_base::sync_with_stdio(0); cin.tie(0);

    int d = 3;
    for (int i = 1; i <= 16; i++) {
        generate_repeetend(1, d, repeetend[i]);
        d *= 3;
    }

    output(100);
    cout << '\n';
    output(100000000);

    return 0;
}
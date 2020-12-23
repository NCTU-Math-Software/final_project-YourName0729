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

void generate_repetend(vector<int>& pre_rep, vector<int>& rep) {
    int d = 0;
    do {
        for (int p : pre_rep) {
            d *= 10;
            d += p;
            rep.push_back(d / 3);
            d = d - d / 3 * 3;
        }
    } while (d);
}

int dig(int k, int d, vector<int>& repeetend) {
    int p = 1;
    For (i, k)  p *= 3;
    if (d < p)  return 0;
    d -= p;
    return repeetend[d % repeetend.size()];
}

void output(int n) {
    vector<int> ans;
    int d = 0;
    // n + 15, n - 1;
    for (int i = n + 13; i >= n - 1; i--) {
        //cout << i << '\n';
        for (int j = 1; j <= 16; j++) {
            d += dig(j, i, repeetend[j]);
        }
        ans.push_back(d % 10);
        d /= 10;
    }

    for (int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

int main() {
    //ios_base::sync_with_stdio(0); cin.tie(0);

    repeetend[1].push_back(3);
    for (int i = 2; i <= 16; i++) {
        generate_repetend(repeetend[i - 1], repeetend[i]);
    }

    output(100);
    cout << '\n';
    output(100000000);

    return 0;
}
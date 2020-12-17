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

vector<int> reps1[17];
vector<int> reps2[17];

void s(int p, int q, vector<int>& rep) {
    vector<bool> vst(q);
    while (!vst[p]) {
        vst[p] = 1;
        p *= 10;
        rep.push_back(p / q);
        p = p - p / q * q;
    }
}

void generate(vector<int>& pre_rep, vector<int>& rep) {
    int d = 0;
    /*for (int p : pre_rep) {
        d *= 10;
        d += p;
        rep.push_back(d / 3);
        d = d - d / 3 * 3;
    }*/
    do {
        for (int p : pre_rep) {
        d *= 10;
        d += p;
        rep.push_back(d / 3);
        d = d - d / 3 * 3;
        }
    } while (d);
}

/*int dig(int k, int d) {
    int p = 1;
    For (i, k)  p *= 3;
    if (d < p)  return 0;
    d -= p;
    return reps[k][d % reps[k].size()];
}*/

/*void output(int n) {
    stack<int> ans;
    int d = 0;
    for (int i = n + 15; i >= n - 1; i--) {
        //cout << i << '\n';
        for (int j = 1; j <= 16; j++) {
            d += dig(j, i);
        }
        ans.push(d % 10);
        d /= 10;
    }

    For (i, 10) {
        cout << ans.top();
        ans.pop();
    }
}*/

int main() {
    //ios_base::sync_with_stdio(0); cin.tie(0);

    reps2[1].push_back(3);
    for (int i = 2; i <= 16; i++) {
        generate(reps2[i - 1], reps2[i]);
    }

    /*int d = 3;
    For (i, 16) {
        s(1, d, reps1[i + 1]);
        //cout << reps1[i + 1].size() << '\n';
        d *= 3;
    }

    for (int i = 1; i <= 7; i++) {
        for (auto d : reps2[i]) cout << d;
        cout << '\n';
    }

    // for (int i = 0; i < 20; i++) {
    //     cout << dig(2, i);
    // }*/

    //output(100000000);

    return 0;
}
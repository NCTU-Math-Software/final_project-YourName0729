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
    vector<int> dif;
    int d = 0;
    For (i, divisor) {
        for (int p : repetend) {
            d *= 10;
            d += p;
            rep.push_back(d / divisor);
            d = d - d / divisor * divisor;
        }
        //cout << d << '\n';
        dif.push_back(d);
    }
    for (int i = 0; i < 10; i++) {
    	cout << dif[i] << '\n';
	}
	cout << '\n';
    //cout << "size " << rep.size() << '\n';
}

int divide10(int divisor, int l) {
	int d = 1;
	for (int i = 0; i < l; i++) {
		d *= 10;
		d = d - d / divisor * divisor;
        
        //cout << "d " << d << '\n';
    }
    return d;
}

int divided_fst(int divisor, vector<int>& repetend) {
	int d = 0;
	for (int p : repetend) {
        d *= 10;
        d += p;
        d = d - d / divisor * divisor;
    }
    return d;
}

int reminder(int div, vector<int>& rep, int n) {
	int d10 = divide10(div, rep.size());
	int k = divided_fst(div, rep);
	ll d1 = 1;
	ll d = 0;
	for (int i = 0; i < n; i++) {
		d = (d + k * d1) % div;
		d1 = (d1 * d10) % div;
	}
	return d;
}

int main() {
    //ios_base::sync_with_stdio(0); cin.tie(0);

	int divisor = 4782969;
    vector<int> vec = {0, 3, 7}; // repetend
    vector<int> ans;
    recur(divisor, vec, ans);
    
	
	for (int i = 1; i < 10; i++) {
		cout << reminder(divisor, vec, i) << '\n';
	}

    return 0;
}

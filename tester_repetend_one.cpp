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

int threshold = 8;
vector<int> repetend[34];
long long pow3[20];

int reminder(int start, int q, vector<int>& rep, int n) {
    int d = start;
    for (int i = 0; i < n; i++) {
        d *= 10;
        d += rep[i % rep.size()];
        d = d - d / q * q;
    }
    return d;
}

void repetender(int start, int q, vector<int>& rep, int n, vector<int>& fetch) {
    int d = start;
    for (int i = 0; i < n; i++) {
        d *= 10;
        d += rep[i % rep.size()];
        fetch.push_back(d / q);
        d = d - d / q * q;
    }
}

int producter(int start, vector<int>& rep, ll q, int n) {
    int d = start;
    for (int i = 0; i < n; i++) {
        d *= 10;
        d += rep[i % rep.size()];
        d = d - d / q * q;
    }
    d *= 10;
    d += rep[n % rep.size()];
    return d / q;
}

void init_repetend() {
    repetend[1] = {3};
    repetend[2] = {1};
    int n = 3;
    for (int i = 3; i <= threshold; i++) {
        repetender(0, 3, repetend[i - 1], n, repetend[i]);
        n *= 3;
    }
}

void init_pow3() {
    long long d = 1;
    for (int i = 0; i < 2 * threshold + 2; i++) {
        pow3[i] = d;
        d *= 3;
    }
}

int repetend_one(int k, long long n) {
    if (k == 0) return 0;
    if (k == 1) return 3;

    n %= pow3[k - 2];
    if (k <= threshold) return repetend[k][n];

    int l = k - threshold;
    k = threshold;
    vector<int> zeros = {0};
    vector<int> ones = {0};

    int dn = n / pow3[k - 2];

    int a = reminder(0, pow3[l], repetend[k], pow3[k - 2]);
    int b = reminder(1, pow3[l], zeros, pow3[k - 2]);
    int c = 0;
    int p = 1;
    for (int i = 0; i < dn; i++) {
        p = p * b % pow3[l];
        c = (c + p) % pow3[l];
    }
    //cout << a << ' ' << b << ' ' << 
    int start = a * c % pow3[l];
    return producter(start, repetend[k], pow3[l], n - dn * pow3[k - 2]);
    //return reminder(start, pow3[l], repetend[k], n - dn * pow3[k - 2]);
}

int digit_one(int k, long long n) {
    if (n < pow3[k])   return 0;
    return repetend_one(k, n - pow3[k]);
}

vector<int> read_repetend(fstream& fin) {
    vector<int> re;
    int n, tmp;
    fin >> tmp >> n;
    for (int i = 0; i < n; i++) {
        fin >> tmp;
        re.push_back(tmp);
    }
    return re;
}

int main() {
    //ios_base::sync_with_stdio(0); cin.tie(0);

    init_repetend();
    init_pow3();

    fstream fin;
    fin.open("repetend.txt");

    int k = 16;

    for (int i = 1; i <= k - 1; i++)    read_repetend(fin);

    vector<int> rep = read_repetend(fin);

    for (int i = 0; i < 100; i++) {
        std::random_device rd;
        std::default_random_engine gen = std::default_random_engine(rd());
        std::uniform_int_distribution<int> dis(0, pow3[k - 2] - 1);
        if (rep[i] != repetend_one(k, i)) {
            cout << "GG\n";
            return 0;
        }
    }
    cout << "Good\n";


    return 0;
}
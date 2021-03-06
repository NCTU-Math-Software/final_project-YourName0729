#include <bits/stdc++.h>

#define uint32 unsigned int
#define uint64 unsigned long long
 
using namespace std;

const uint32 threshold = 16;
const uint32 MAXK = 33;
vector<uint32> repetend[threshold + 1];
uint64 pow3[MAXK + 1];

uint32 reminder(uint32 start, uint32 q, vector<uint32>& rep, uint32 n) {
    if (q == 0 || rep.size() == 0)  throw invalid_argument("reminder error");

    uint32 d = start % q;
    for (uint32 i = 0; i < n; i++) {
        d *= 10;
        d += rep[i % rep.size()];
        d = d - d / q * q;
    }
    return d;
}

void repetender(uint32 start, uint32 q, vector<uint32>& rep, uint32 n, vector<uint32>& fetch) {
    if (q == 0 || rep.size() == 0)  throw invalid_argument("repetender error");

    uint32 d = start % q;
    for (uint32 i = 0; i < n; i++) {
        d *= 10;
        d += rep[i % rep.size()];
        fetch.push_back(d / q);
        d = d - d / q * q;
    }
}

uint32 producter(uint32 start, uint32 q, vector<uint32>& rep, uint32 n) {
    if (q == 0 || rep.size() == 0)  throw invalid_argument("producter error");

    uint32 d = start % q;
    for (uint32 i = 0; i < n; i++) {
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
    for (uint32 i = 3; i <= threshold; i++) {
        repetender(0, 3, repetend[i - 1], pow3[i - 2], repetend[i]);
    }
}

void init_pow3() {
    pow3[0] = 1;
    for (uint32 i = 1; i <= MAXK; i++) {
        pow3[i] = 3 * pow3[i - 1];
    }
}

uint32 repetend_one(uint32 k, uint64 n) {
    cout << "repetend one " << k << ' ' << n << '\n';
    if (k == 0) return 0;
    if (k == 1) return 3;

    n %= pow3[k - 2];
    if (k <= threshold) return repetend[k][n];

    uint32 l = k - threshold;
    k = threshold;
    vector<uint32> zeros = {0};

    uint32 dn = n / pow3[k - 2];

    uint32 a = reminder(0, pow3[l], repetend[k], pow3[k - 2]);
    uint32 b = reminder(1, pow3[l], zeros, pow3[k - 2]);
    uint32 c = 0;
    uint32 p = 1;
    for (uint32 i = 0; i < dn; i++) {
        p = p * b % pow3[l];
        c = (c + p) % pow3[l];
    }
    
    uint32 start = a * c % pow3[l];
    return producter(start, pow3[l], repetend[k], n - dn * pow3[k - 2]);
}

uint32 digit_one(uint32 k, uint64 n) {
    if (n < pow3[k])   return 0;
    return repetend_one(k, n - pow3[k]);
}

vector<uint32> read_repetend(fstream& fin) {
    vector<uint32> re;
    uint32 n, tmp;
    fin >> tmp >> n;
    for (uint32 i = 0; i < n; i++) {
        fin >> tmp;
        re.push_back(tmp);
    }
    return re;
}

vector<uint32> repetend_seg(int k, uint64 n, uint32 extend) {
    //cout << "seg " << k << ' ' << n << ' ' << extend << '\n';
    vector<uint32> re(extend);
    if (n < pow3[k]) return re;
    if (k == 1) {
        fill(re.begin(), re.end(), 3);
        return re;
    }
    n %= pow3[k - 2];
    if (k <= threshold) {
        //cout << "?\n";
        for (int i = 0; i < extend; i++) {
            re[i] = repetend[k][(n + i) % repetend[k].size()];
        }
        return re;
    }

    uint32 s = k - threshold, t = threshold;
    uint32 dn = n / pow3[t - 2];
    vector<uint32> zeros = {0};

    uint32 a = reminder(0, pow3[s], repetend[t], pow3[t - 2]);
    uint32 b = reminder(1, pow3[s], zeros, pow3[t - 2]);
    uint32 c = 0;
    uint32 p = 1;
    for (uint32 i = 0; i < dn; i++) {
        p = p * b % pow3[s];
        c = (c + p) % pow3[s];
    }

    uint32 start = a * c % pow3[s], nn = n - dn * pow3[t - 2], d = 0;
    for (uint32 i = 0; i < nn; i++) {
        d *= 10;
        d += repetend[t][i];
        d = d - d / pow3[s] * pow3[s];
    }
    for (uint32 i = 0; i < extend; i++) {
        d *= 10;
        d += repetend[t][nn + i];
        re[i] = d / pow3[s];
        d = d - d / pow3[s] * pow3[s];
    }
    return re;
}

void solver(uint64 n) {
    uint32 extend = 25;
    vector<uint32> ans(extend);
    for (uint32 i = 1; i <= MAXK; i++) {
        vector<uint32> d = repetend_seg(i, n - 1, extend);
        for (uint32 j = 0; j < extend; j++) {
            //cout << d[j] << ' ';
            ans[j] += d[j];
        }
        //cout << '\n';
    }
    for (uint32 i = extend - 1; i > 0; i--) {
        ans[i - 1] += ans[i] / 10;
        ans[i] %= 10;
    }
    ans[0] %= 10;
    for (uint32 i = 0; i < extend; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

/*void solver(uint64 n) {
    cout << n << '\n';
    vector<uint32> ans;
    uint32 d = 0;
    for (uint64 i = n + 15; i >= n - 1; i--) {
        for (uint32 j = 0; j <= MAXK; j++) {
            d += digit_one(j, i);
        }
        ans.push_back(d % 10);
        d /= 10;
    }
    
    for (uint32 i = 0; i < 10; i++) {
        cout << ans[ans.size() - 1 - i] << ' ';
    }
    cout << '\n';
}*/

int main() {

    init_pow3();
    init_repetend();
    
    solver(100);
    solver(100000000);
    solver(10000000000000000);

    return 0;
}
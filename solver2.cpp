#include <bits/stdc++.h>

#define uint32 unsigned int
#define uint64 unsigned long long
 
using namespace std;

const uint32 threshold = 17;
const uint32 MAXK = 33;
vector<uint32> repetend[threshold + 1];
uint64 pow3[MAXK + 1];
uint64 remaind[MAXK + 1];

uint32 remainder(uint32 start, uint32 q, vector<uint32>& rep) {
    uint32 d = start % q;
    for (uint32 i = 0; i < rep.size(); i++) {
        d *= 10;
        d += rep[i];
        d = d - d / q * q;
    }
    return d;
}

void repetender(uint32 start, uint32 q, vector<uint32>& rep, uint32 n, vector<uint32>& fetch) {
    uint32 d = start % q;
    for (uint32 i = 0; i < n; i++) {
        d *= 10;
        d += rep[i % rep.size()];
        fetch.push_back(d / q);
        d = d - d / q * q;
    }
}

void init_repetend() {
    repetend[1] = {3};
    for (uint32 i = 2; i <= threshold; i++) {
        repetender(0, 3, repetend[i - 1], pow3[i - 2], repetend[i]);
    }
}

void init_pow3() {
    pow3[0] = 1;
    for (uint32 i = 1; i <= MAXK; i++) {
        pow3[i] = 3 * pow3[i - 1];
    }
}

void init_remaind() {
	remaind[MAXK] = remainder(0, pow3[MAXK - threshold], repetend[threshold]);
    for (int i = MAXK - 1; i > threshold; i--) {
        remaind[i] = remaind[i + 1] % pow3[i - threshold];
    }
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

vector<uint32> repetend_seg(int k, uint64 n, uint32 ext) {
    vector<uint32> re(ext);
    if (n < pow3[k]) return re;
    if (k == 1) {
        fill(re.begin(), re.end(), 3);
        return re;
    }
    n %= pow3[k - 2];
    if (k <= threshold) {
        for (int i = 0; i < ext; i++) {
            re[i] = repetend[k][(n + i) % repetend[k].size()];
        }
        return re;
    }

    uint32 s = k - threshold, t = threshold;
    uint64 dn = n / pow3[t - 2];
    vector<uint32> zeros = {0};

    uint64 a = remaind[k];
    //cout << remaind[k] << '\n'; 

    uint64 d = a * dn % pow3[s], nn = n - dn * pow3[t - 2];
    for (uint32 i = 0; i < nn; i++) {
        d *= 10;
        d += repetend[t][i];
        d = d - d / pow3[s] * pow3[s];
    }
    for (uint32 i = 0; i < ext; i++) {
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
            ans[j] += d[j];
        }
    }
    for (uint32 i = extend - 1; i > 0; i--) {
        ans[i - 1] += ans[i] / 10;
        ans[i] %= 10;
    } 
    ans[0] %= 10;
    for (uint32 i = 0; i < 10; i++) {
        cout << ans[i];
    }
    cout << '\n';
}

int main() {

    init_pow3();
    init_repetend();
    init_remaind();
    
    solver(100);
    solver(100000000);
    solver(10000000000000000);

    return 0;
}

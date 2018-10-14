#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

pair<bool, long long> ok (long long ml, long long mr, long long a, long long b) {
    long long mo = ((ml + mr) * (mr - ml + 1)) / 2;
    return make_pair(mo <= min (a, b), mo);
}

int main() {
    // freopen("input.txt", "r", stdin);

    int T;
    scanf("%d", &T);

    for (int testId = 0; testId < T; ++ testId) {
        long long a, b, m;
        scanf("%lld %lld %lld", &a, &b, &m);

        m = min(m, min(a, b));
        while (m > 0) {
            // printf("a = %lld b = %lld m = %lld\n", a, b, m);
            long long lo = 1, hi = m;
            while (hi - lo > 1) {
                int mi = (hi + lo) / 2;
                if (ok (mi, m, a, b).first) hi = mi; else lo = mi;
            }
            // printf("lo = %lld\n", lo);
            // break;

            pair<bool, long long> p = ok (lo, m, a, b);
            if (p.first) { a -= p.second, b -= p.second, m = min(lo - 1, min(a, b)); continue; }
            p = ok (hi, m, a, b);
            if (p.first) { a -= p.second, b -= p.second, m = min(hi - 1, min(a, b)); continue; }
            m = 0;
        }

        printf("%lld\n", a + b);
    }
}
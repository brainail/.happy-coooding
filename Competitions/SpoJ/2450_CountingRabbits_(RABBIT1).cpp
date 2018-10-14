#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

inline int vv(int a, int b, int modulo) {
    return ((long long) a * (long long) b) % modulo;
}

vector< pair<int, int> > mult(vector< pair<int, int> > a, vector< pair<int, int> > b, int modulo) {
    vector< pair<int, int> > rtv;
    long long r00 = vv(a [0].first, b [0].first, modulo) + vv(a [0].second, b [1].first, modulo);
    long long r01 = vv(a [0].first, b [0].second, modulo) + vv(a [0].second, b [1].second, modulo);
    long long r10 = vv(a [1].first, b [0].first, modulo) + vv(a [1].second, b [1].first, modulo);
    long long r11 = vv(a [1].first, b [0].second, modulo) + vv(a [1].second, b [1].second, modulo);
    rtv.push_back(make_pair(r00 % modulo, r01 % modulo));
    rtv.push_back(make_pair(r10 % modulo, r11 % modulo));
    return rtv;
}

int main() {
    freopen("input.txt", "r", stdin);

    int C;
    scanf("%d", &C);

    for (int c = 0; c < C; ++ c) {
        int N, M;
        scanf("%d %d", &N, &M);
        // -- N;

        int modulo = 1;
        for (int m = 0; m < M; ++ m) modulo <<= 1;

        vector< pair<int, int> > fibMu;
        fibMu.push_back(make_pair(1, 1));
        fibMu.push_back(make_pair(1, 0));
        vector< pair<int, int> > fib;
        fib.push_back(make_pair(1, 0));
        fib.push_back(make_pair(0, 1));

        while (N) {
            if (N & 1) fib = mult(fib, fibMu, modulo);
            fibMu = mult(fibMu, fibMu, modulo);
            N >>= 1;
        }

        printf("%d\n", fib [0].first);
    }
}
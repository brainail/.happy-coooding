#include <iostream>
#include <stdio.h>
#include <cmath>
#include <cassert>
#include <string.h>
using namespace std;

#define DEBUG false
#define PRINT true
#define CHECK true

#define debug_(who) if (DEBUG) { cout << #who << " = " << who << endl; }
#define debug(who, who2) if (DEBUG) { cout << #who << " = " << who << ", " << #who2 << " = " << who2 << endl; }
#define debug3(who, who2, who3) if (DEBUG) { cout << #who << " = " << who << ", " << #who2 << " = " << who2 << ", " << #who3 << " = " << who3 << endl; }

typedef long long tll;

int T;
tll N, M, Z, L, R, B;

inline tll calc(tll N, tll M, tll Z, tll L, tll R, tll B) {
    tll rtv = 0;

    if (! (M - 1)) {
        rtv = min (N, Z + L + R + B), N = 0;
    }

    if (L && N) {
        tll _Lrows = L / (M - 1);
        debug("01", _Lrows);
            // if (L % (M - 1)) ++ _Lrows;
        _Lrows = min (min (_Lrows, B), N);
        debug("02", _Lrows);
        rtv += _Lrows * M, B -= _Lrows, N -= _Lrows, L -= _Lrows * (M - 1);

        tll Lrows = L / M;
        debug("03", Lrows);
        Lrows = min (Lrows, N);
        debug("04", Lrows);
        rtv += Lrows * M, L -= Lrows * M, N -= Lrows;

        // Wtf?
        if (M > 3 && L && (N > 1) && (L + 3 >= M) && (B > 1)) {
            // assert (false);
            rtv += (M - 3), L -= (M - 3), -- N, rtv += 2, B -= 2;
            rtv += min ((tll) 1, Z), Z -= min ((tll) 1, Z);
        }

        if (L && N) {
            tll rest = M - L;
            -- N, rtv += L;
            if (B) -- rest, ++ rtv, -- B;
            tll Rcolumns = min (rest, R);
            rtv += Rcolumns, R -= Rcolumns, rest -= Rcolumns;
            if (rest) {
                tll Bcolumns = min (rest / 2, B);
                rtv += Bcolumns, B -= Bcolumns; 

                tll Zcolumns = min (rest - Bcolumns, Z);
                rtv += Zcolumns, Z -= Zcolumns; 
            }
        }
    }

    if (R && N) {
        tll _Rrows = R / (M - 1);
        debug("01", _Rrows);
            // if (R % (M - 1)) ++ _Rrows;
        _Rrows = min (min (_Rrows, B), N);
        debug("02", _Rrows);
        rtv += _Rrows * M, B -= _Rrows, N -= _Rrows, R -= _Rrows * (M - 1);

        tll Rrows = R / M;
        debug("03", Rrows);
        Rrows = min (Rrows, N);
        debug("04", Rrows);
        rtv += Rrows * M, R -= Rrows * M, N -= Rrows;

        // Wtf?
        if (R && (N > 1) && (R == M - 2) && (B > 1)) {
            // assert (false);
            rtv += (R - 1), R = 1, -- N, rtv += 2, B -= 2;
            rtv += min ((tll) 1, Z), Z -= min ((tll) 1, Z);
        }

        if (R && N) {
            tll rest = M - R;
            debug("05", rest);
            -- N, rtv += R;
            if (B) -- rest, ++ rtv, -- B;
            debug("06", rest);
            debug("07", rtv);
            if (rest) {
                tll Bcolumns = min (rest / 2, B);
                rtv += Bcolumns, B -= Bcolumns; 

                tll Zcolumns = min (rest - Bcolumns, Z);
                rtv += Zcolumns, Z -= Zcolumns; 
            }
        }
    }

    if (B && N) {
        tll Brows = B / ((M + 1) / 2);
        Brows = min (Brows, N);    
        rtv += Brows * ((M + 1) / 2), B -= Brows * ((M + 1) / 2), N -= Brows;
        rtv += min (Z, Brows * (M / 2)), Z -= min (Z, Brows * (M / 2));

        if (B && N) {
            tll Bcolumns = min (B, ((M + 1) / 2));
            -- N, rtv += Bcolumns;
            rtv += min (Z, M - Bcolumns), Z -= min (Z, M - Bcolumns);
        }
    }

    if (Z && N) {
        rtv += min (Z, N * M), Z -= min (Z, N * M);
    }

    return rtv;
}

char board [10][10];

void gen(int cx, int cy, tll N, tll M, tll Z = 0, tll L = 0, tll R = 0, tll B = 0) {
    if (cx == N && cy == M - 1) {
        if (Z + L + R + B < ((N * M) / 3) * 2) return;

        printf("N = %lld, M = %lld, Z = %lld, L = %lld, R = %lld, B = %lld\n", N, M, Z, L, R, B);

        if (PRINT) {
            for (int i = 0; i < N; ++ i) {
                for (int j = 0; j < M; ++ j) {
                    printf("%c", board [i][j]);
                }
                printf("\n");
            }
        }

        tll fA = (Z + L + R + B), fB = calc (N, M, Z, L, R, B);
        printf("(Z+L+R+B) ?== calc(...) | %lld ?== %lld\n", fA, fB);
        assert(fA == fB);
        
        printf("\n");
        return;
    }

    // next
    int nx = cx, ny = cy - 1;
    if (ny < 0) { ++ nx; ny = M - 1; }
    // B
    if (board [cx][cy + 1] != 'B' && board [cx][cy + 1] != 'L') {
        board [cx][cy] = 'B';
        gen (nx, ny, N, M, Z, L, R, B + 1);
    }
    // R
    board [cx][cy] = 'L';
    gen (nx, ny, N, M, Z, L + 1, R, B);
    // L
    if (board [cx][cy + 1] != 'B' && board [cx][cy + 1] != 'L') {
        board [cx][cy] = 'R';
        gen (nx, ny, N, M, Z, L, R + 1, B);
    }
    // .
    board [cx][cy] = '.';
    gen (nx, ny, N, M, Z, L, R, B);
    // Z
    board [cx][cy] = 'Z';
    gen (nx, ny, N, M, Z + 1, L, R, B);
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d\n", &T);

    if (CHECK) {
        T = 0;
        memset(board, '.', sizeof(board));
        gen(0, 5, 6, 6);
    }

    for (int testId = 0; testId < T; ++ testId) {
        scanf("%lld %lld %lld %lld %lld %lld", & N, & M, & Z, & L, & R, & B);
        printf("%lld\n", calc (N, M, Z, L, R, B));
    }

    return 0;
}
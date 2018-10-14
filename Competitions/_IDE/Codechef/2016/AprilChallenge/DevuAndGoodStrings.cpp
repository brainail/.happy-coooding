#include <stdio.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <string>
using namespace std;

// MY
int LEN = 60;
int N = 10;
int NA = 2;
int H = 1e9;
int rtv = 0;
char S [60];
char s [60];
int i, it;

vector< vector< vector < string > > > ss;

clock_t tbegin, tend;
double time_spent;

void goo (int p /*, int h*/);
int good (int p, char ch);

// MAIN
int main() {
    // Using cout/printf together can't guarantee the right order
    // ios_base::sync_with_stdio(0);

    // freopen(OUTPUT_FILE.c_str(), "w", stdout);

    // CODE AREA =>
    tbegin = clock();

    int testId;
    scanf("%d\n", & testId);

    // precalc
    ss.resize (4);
    ss [1].resize (28);
    NA = 1;
    for (i = 0; i < LEN; ++ i) s [i] = '\0';
    goo(0 /*, 0*/);
    ss [2].resize (28);
    NA = 2;
    for (i = 0; i < LEN; ++ i) s [i] = '\0';
    goo(0 /*, 0*/);
    ss [3].resize (28);
    NA = 3;
    for (i = 0; i < LEN; ++ i) s [i] = '\0';
    goo(0 /*, 0*/);

    for (it = 0; it < testId; ++ it) {
        scanf("%d %d\n", &NA, &H);

        for (i = 0; i < LEN; ++ i) S [i] = '\0';
        scanf("%s\n", & S [0]);

        N = (int) strlen (S);
        if (N >= 27 && NA <= 3) {
            printf("0\n");
            continue;
        }
        if (N >= 9 && NA <= 2) {
            printf("0\n");
            continue;
        }
        if (N >= 3 && NA <= 1) {
            printf("0\n");
            continue;
        }

        rtv = 0;

        int cz = (int) ss [NA][N].size ();
        for (i = 0; i < cz; ++ i) {
            int hh = 0, j;
            for (j = 0; j < N; ++ j) {
                hh += (S [j] != ss [NA][N][i][j]);
                if (hh > H) break;
            }
            rtv += (hh <= H);
        }

        printf("%d\n", rtv);
    }

    tend = clock();
    time_spent = (double) (tend - tbegin) / CLOCKS_PER_SEC;
    // printf("time = %.10lf\n", time_spent * 1000.0);
    // CODE AREA <=

    return 0;
}

void goo (int p /*, int h*/) {
    ss [NA][p].push_back(string(s));

    if (p == 27) {
        return;
    }

    if (NA >= 1 && good(p, 'a') > 0) {
        // if (h + ('a' != S [p]) <= H) {
            s[p] = 'a';
            goo (p + 1 /*, h + ('a' != S [p])*/);
            s[p] = '\0';
        // }
    }

    if (NA >= 2 && good(p, 'b') > 0) {
        // if (h + ('b' != S [p]) <= H) {
            s[p] = 'b';
            goo (p + 1 /*, h + ('b' != S [p])*/);
            s[p] = '\0';
        // }
    }

    if (NA >= 3 && good(p, 'c') > 0) {
        // if (h + ('c' != S [p]) <= H) {
            s[p] = 'c';
            goo (p + 1 /*, h + ('c' != S [p])*/);
            s[p] = '\0';
        // }
    }

}

inline int good (int p, char ch) {
    int j;
    for (j = p - 1; j >= 0; -- j) {
        int t = p - j;
        if (j - t >= 0) {
            if (s [j] == ch && s[j - t] == ch) {
                return -1;
            }
        } else {
            break;
        }
    }

    return 1;
}
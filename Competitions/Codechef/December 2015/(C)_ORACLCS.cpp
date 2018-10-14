#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

int main() {
    // freopen("input.txt", "r", stdin);

    int T;
    scanf("%d\n", &T);

    for (int testId = 0; testId < T; ++ testId) {
        int n;
        scanf("%d\n", &n);

        int rtv = (int) 1e9;
        for (int i = 0; i < n; ++ i) {
            string s;
            getline(cin, s);

            int a = 0, m = s.length();
            for (int j = 0; j < m; ++ j) a += ('a' == s [j]);

            rtv = min (rtv, min (a, m - a));
        }

        printf("%d\n", rtv);
    }
}
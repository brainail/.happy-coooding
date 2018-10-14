#include <iostream>
#include <stdio.h>
#include <cmath>
#include <vector>
using namespace std;

const int Nmask = 1024;
const int Lmask = 10;
const int Modulo = (int) 1e9 + 7;

char ch;
vector<int> dp [2];

int main() {
    freopen("input.txt", "r", stdin);

    int T;
    scanf("%d\n", &T);

    for (int testId = 0; testId < T; ++ testId) {
        int photoMask = 0;
        for (int i = 0; i < Lmask; ++ i) {
            scanf("%c", &ch);
            photoMask += (1 << i) * ('b' == ch);
        }
        scanf("\n");

        // printf("photoMask = %d\n", photoMask);

        int lay = 0;
        dp [0].assign(Nmask, 0);
        dp [lay][photoMask] = 1;

        int Nfilters;
        scanf("%d\n", &Nfilters);

        for (int filterIndex = 0; filterIndex < Nfilters; ++ filterIndex) {
            int filterMask = 0;
            for (int i = 0; i < Lmask; ++ i) {
                scanf("%c", &ch);
                filterMask += (1 << i) * ('+' == ch);
            }   
            scanf("\n");

            // printf("filterMask = %d\n", filterMask); 

            int nextLay = lay ^ 1;
            dp [nextLay].assign(Nmask, 0);

            for (int mask = 0; mask < Nmask; ++ mask)
                if (dp [lay][mask] > 0) {
                    int nextMask = mask ^ filterMask;
                    dp [nextLay][nextMask] += dp [lay][mask];
                    if (dp [nextLay][nextMask] > Modulo) dp [nextLay][nextMask] -= Modulo;
                    // printf("nextMask [->] = %d\n", nextMask); 

                    nextMask = mask;
                    dp [nextLay][nextMask] += dp [lay][mask];
                    if (dp [nextLay][nextMask] > Modulo) dp [nextLay][nextMask] -= Modulo;
                    // printf("nextMask [->] = %d\n", nextMask); 
                }

            lay = nextLay;
        }

        int rtv = dp [lay][Nmask - 1];
        printf("%d\n", rtv);
    }
}
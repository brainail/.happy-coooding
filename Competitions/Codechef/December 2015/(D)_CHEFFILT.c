#include <stdio.h>
#include <string.h>

#define Nmask 1024
#define Lmask 10
#define Modulo 1000000007

char ch;
int dp [2][Nmask], testId, i, filterIndex, mask;

int main() {
    // freopen("input.txt", "r", stdin);

    int T;
    scanf("%d\n", &T);

    for (testId = 0; testId < T; ++ testId) {
        int photoMask = 0;
        for (i = 0; i < Lmask; ++ i) {
            scanf("%c", &ch);
            photoMask += (1 << i) * ('b' == ch);
        }
        scanf("\n");

        // printf("photoMask = %d\n", photoMask);

        int lay = 0;
        memset(dp [0], 0, sizeof(dp [0]));
        dp [lay][photoMask] = 1;

        int Nfilters;
        scanf("%d\n", &Nfilters);

        for (filterIndex = 0; filterIndex < Nfilters; ++ filterIndex) {
            int filterMask = 0;
            for (i = 0; i < Lmask; ++ i) {
                scanf("%c", &ch);
                filterMask += (1 << i) * ('+' == ch);
            }   
            scanf("\n");

            // printf("filterMask = %d\n", filterMask); 

            int nextLay = lay ^ 1;
            memset(dp [nextLay], 0, sizeof(dp [nextLay]));

            for (mask = 0; mask < Nmask; ++ mask)
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

        printf("%d\n", dp [lay][Nmask - 1]);
    }
}
#include <cstdio>
#include <cstring>
#include <cfloat>

#define MAXN 100  // 70C35
long double bin[MAXN + 1][MAXN + 1];

void precompute()
{
    memset(bin, 0, sizeof(bin[0][0]) * (MAXN + 1) * (MAXN + 1));

    for(int k = 0; k <= MAXN; k++) {
        bin[k][0] = bin[k][k] = 1;

        for(int i = 1; i < k; i++) {
            bin[k][i] = bin[k - 1][i - 1] + bin[k - 1][i];
        }
    }
}
long double nCr(int n, int k)
{
    if(bin[n][k] == 0) {
        precompute();
    }

    return bin[n][k];
}

int main()
{
    int n = 70, k = 35;
    printf("%d C %d = %.0Lf\n", n, k, nCr(n, k));
    return 0;
}

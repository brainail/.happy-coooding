#include <iostream>
enum {MAX = 30000 + 1, NUM_COIN = 11};
long long int count[MAX]; //unit is cent

int main()
{
    int coin[NUM_COIN] = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};
    count[0] = 1;

    for(int i = 0; i < NUM_COIN; ++i)
        for(int j = coin[i]; j < MAX; j += 5) //bug: use int j=5
            count[j] += count[ j - coin[i] ];

    int dollar, cent;

    while(scanf("%d.%d", &dollar, &cent) == 2) {
        if(dollar == 0 && cent == 0) break;

        printf("%3d.%02d%17lld\n", dollar, cent, count[dollar * 100 + cent]);
    }

    return 0;
}

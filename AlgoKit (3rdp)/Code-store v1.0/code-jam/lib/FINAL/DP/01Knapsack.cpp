// http://uva.onlinejudge.org/external/101/10130.html
/**
Notes :
1. 0/1 Knapsack problem
2. u can't take an object more than one time.
suppose, u can stand with maximum 30 kg weight
an object has a weight of 10 kg
but u can take the object only once, not 3 times, though u still have 20 kg space
3. calculate all the values up to 30 and save in an array dp[30]
if ur maxWeightLimit = i, thn dp[i] = maxValue u can get
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <cctype>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <cmath>
#include <bitset>
#include <utility>
#include <set>
#define INT_MAX 2147483647
#define INT_MIN -2147483648
#define N 1000000
using namespace std;
int main()
{
    int testCase;
    scanf("%d", &testCase);

    while(testCase--) {
        int objects;
        int values[1000 + 5];
        int weight[1000 + 5];
        scanf("%d", &objects);

        for(int i = 0; i < objects; ++i)
            scanf("%d %d", &values[i], &weight[i]);

        int dp[30 + 5];
        int last_added[30 + 5];
        memset(dp, 0, sizeof(dp));

        for(int j = 0; j < objects; ++j) {
            for(int i = 32; i >= 0; --i) {
                if(weight[j] <= i && dp[i] < dp[i - weight[j]] + values[j]) {
                    dp[i] = dp[i - weight[j]] + values[j];
                    last_added[i] = j;
                }
            }
        }

        int g, volume, aux;
        scanf("%d", &g);

        while(g--) {
            scanf("%d", &volume);
            printf("Max value = $%d\n", dp[volume]);
            // print solution
            aux = volume;

            while((aux > 0) && (last_added[aux] != -1)) {
                printf("Added object %d ($%d %dKg). Space left: %d\n", last_added[aux] + 1, values[last_added[aux]], weight[last_added[aux]], aux - weight[last_added[aux]]);
                aux -= weight[last_added[aux]];
            }
        }
    }

    return 0;
}

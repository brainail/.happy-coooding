#include <iostream>
#include <cmath>
#define MAX 100
#define INF 1<<30
using namespace std;
int s, n, coins[MAX], sol[MAX];
int solve()
{
    for(int i = 0; i <= s; i++)
        sol[i] = INF;

    sol[0] = 0;

    for(int i = 1; i <= s; i++) {
        for(int j = 0; j < n; j++) {
            if(coins[j] <= i && sol[i - coins[j]] + 1 < sol[i]) {
                sol[i] = sol[i - coins[j]] + 1;
            }
        }
    }

    cout << "solution = ";

    for(int i = 0; i <= s; i++)
        cout << sol[i] << " ";

    cout << endl;
    return sol[s];
}
int main()
{
    cin >> s >> n;

    for(int i = 0; i < n; i++)
        cin >> coins[i];

    cout << "min# coins = " << solve() << endl;
    return 0;
}

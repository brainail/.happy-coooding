#include <iostream>
using namespace std;
#define M 10
#define N 10
void kadane(int input[], int n, int &x1, int &x2, int &max)
{
    int cur;
    max = 0;
    cur = 0;
    x1 = x2 = 0;
    int lx1;
    lx1 = 0;

    for(int i = 0; i < n; i++) {
        cur = cur + input[i];

        if(cur > max) {
            max = cur;
            x2 = i;
            x1 = lx1;
        }

        if(cur < 0) {
            cur = 0;
            lx1 = i + 1;
        }
    }
}
int main()
{
    int tmp[100], x1, x2;
    int cur, max_sum, fx1, fx2, fy1, fy2;
    int i, j, k;
    int input[M][N];
    fx1 = fx2 = fy1 = fy2 = max_sum = cur = -1;

    for(i = 0; i < M; i++) {
        for(k = 0; k < N; k++)
            tmp[k] = 0;

        for(j = i; j < M; j++) {
            for(k = 0; k < N; k++)
                tmp[k] += input[j][k];

            kadane(tmp, N, x1, x2, cur);

            if(cur > max_sum) {
                fy1 = x1;
                fy2 = x2;
                fx1 = i;
                fx2 = j;
                max_sum = cur;
            }
        }
    }

    cout << "max Sum = " << max_sum << " from (" << fx1 << "," << fy1 << ") to ("
         << fx2 << "," << fy2 << ")" << endl;
}

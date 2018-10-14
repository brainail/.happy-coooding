//      N!
// ----------    compute the values of C(N,K) when N and/or K is big but the
//   (N-K)!*K!   result is guaranteed to fit in 32-bit integer
#include <cstdio>
int GCD(int x, int y)
{
    while(y > 0) {
        x = x % y;
        x ^= y;  //swap
        y ^= x;
        x ^= y;
    }
    return x;
}
void divByGCD(int &x, int &y)
{
    int g = GCD(x, y);
    x /= g;
    y /= g;
}
int fastestCountingCombinations(int n, int k)
{
    int numerator = 1, denominator = 1, toMul, toDiv;
    if(k > n / 2) {
        k = n - k;
    }
    for(int i = k; i; i--) {
        toMul = n - k + i;
        toDiv = i;
        divByGCD(toMul, toDiv);
        divByGCD(numerator, toDiv);
        divByGCD(toMul, denominator);
        numerator *= toMul;
        denominator *= toDiv;
    }
    return numerator / denominator;
}
int main()
{
    printf("%d\n", fastestCountingCombinations(24, 12));
    return 0;
}

#include<iostream>
using namespace std;

int gcd(int a, int b)
{
    int r = 1;

    if(a == b) return a;

    if(a < b) swap(a, b);

    while(r != 0) {
        r = a % b;
        a = b;
        b = r;
    }

    return a;
}

int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}

int main()
{
    int a = 15, b = 30;
    printf("gcd(%d, %d)=%d\n", a, b, gcd(a, b));
    printf("lcm(%d, %d)=%d\n", a, b, lcm(a, b));
    return 0;
}

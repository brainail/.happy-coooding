//  In number theory, Euler's totient or phi function, φ(n), 
// is an arithmetic function that counts the totatives of n, that is, 
// the positive integers less than or equal to n that are relatively prime to n. 
// Thus, if n is a positive integer, then φ(n) is the number of integers 
// k in the range 1 ≤ k ≤ n for which the greatest common divisor gcd(n, k) = 1.

#include <iostream>
#include <stdio.h>
#include <cassert>
using namespace std;

int phi(int n) {
    int result = n;

    for (int i = 2; i * i <= n; ++ i)
        if (!(n % i)) {
            while (!(n % i)) n /= i;
            result -= result / i;
        }

    if (n > 1) {
        result -= result / n;
    }

    return result;
}

int pow(int a, int n, int m) {
    int result = 1;
    
    for (int i = 0; i < n; ++ i) {
        result *= a;
        result %= m;
    }

    return result;
}

template<class T> inline T gcd(T A, T B) { 
    return (A < 0) ? gcd(-A, B) : ((B < 0) ? gcd(A, -B) : ((0 == B) ? A : gcd(B, A % B))); 
}

int main() {
    assert(120 == phi(155));
    assert(1 == gcd(17, 39) && 1 == pow(17, phi(39), 39));
}
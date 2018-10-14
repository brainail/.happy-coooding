#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <algorithm>
#define MAX_UINT64  9223372036854775807LL
using namespace std;
typedef long long uint64;
// Source: http://en.wikipedia.org/wiki/Binary_GCD_algorithm
uint64 gcd(uint64 u, uint64 v)
{
    if(u == 0 || v == 0) return u | v;

    // Remove common twos in u and v
    int shift;

    for(shift = 0; ((u | v) & 1) == 0; ++shift) {
        u >>= 1;
        v >>= 1;
    }

    // Remove twos from u
    while((u & 1) == 0) u >>= 1;

    do {
        // Remove twos in v
        while((v & 1) == 0) v >>= 1;

        /* Now u and v are both odd, so diff(u, v) is even.
        Let u = min(u, v), v = diff(u, v)/2. */
        if(u < v) {
            v -= u;
        } else {
            uint64 diff = u - v;
            u = v;
            v = diff;
        }

        v >>= 1;
    } while(v != 0);

    return u << shift;
}
/** Miller-Rabin */
uint64 mulmod(uint64 a, uint64 b, uint64 c)
{
    uint64 x = 0, y = a % c;

    while(b > 0) {
        if(b % 2 == 1) {
            x = (x + y) % c;
        }

        y = (y * 2) % c;
        b /= 2;
    }

    return x % c;
}
uint64 powmod(uint64 a, uint64 b, uint64 c) //(a^b)%c
{
    uint64 temp;

    if(!b)
        return 1;

    if(b == 1)
        return a % c;

    if(b % 2) {
        temp = powmod(a, b - 1, c);
        return mulmod(temp, a, c);
    }

    temp = powmod(a, b / 2, c);
    return mulmod(temp, temp, c);
}
bool is_prime(uint64 P)
{
    if(P != 2 && P % 2 == 0)
        return false;

    uint64 s = P - 1;

    while(s % 2 == 0) {
        s /= 2;
    }

    for(int i = 0; i < 25; i++) {
        uint64 a = rand() % (P - 1) + 1, temp = s;
        uint64 mod = powmod(a, temp, P);

        while(temp != (P - 1) && mod != 1 && mod != (P - 1)) {
            mod = mulmod(mod, mod, P);
            temp *= 2;
        }

        if(mod != (P - 1) && temp % 2 == 0) {
            return false;
        }
    }

    return true;
}
void brents_factor(uint64 n, vector<uint64>& f)
{
    if(is_prime(n)) {
        f.push_back(n);
        return;
    }

    uint64 a = random() % n;
    uint64 x = random() % n;
    uint64 y = 1;

    for(int i = 0; i * i / 2 < n; i++) {
        // x = x² + a mod n
        x = mulmod(x, x, n);
        x += a;

        if(x < a) x += (MAX_UINT64 - n) + 1;

        x %= n;
        uint64 g = gcd(n, y - x);

        if(g != 1 && g != n) {
            n /= g;
            brents_factor(g, f);

            if(n != g) brents_factor(n, f);

            return;
        }

        if((i & (i - 1)) == 0) y = x;
    }

    // Found no factors, yet n is not a prime, retry
    brents_factor(n, f);
}
uint64 brent_pollard_factor(uint64 n)
{
    const uint64 m = 1000;
    uint64 a, x, y, ys, r, q, g;

    do a = random() % n;

    while(a == 0 || a == n - 2);

    y = random() % n;
    r = 1;
    q = 1;

    do {
        x = y;

        for(uint64 i = 0; i < r; i++) {
            // y = y² + a mod n
            y = mulmod(y, y, n);
            y += a;

            if(y < a) y += (MAX_UINT64 - n) + 1;

            y %= n;
        }

        uint64 k = 0;

        do {
            for(uint64 i = 0; i < m && i < r - k; i++) {
                ys = y;
                // y = y² + a mod n
                y = mulmod(y, y, n);
                y += a;

                if(y < a) y += (MAX_UINT64 - n) + 1;

                y %= n;
                // q = q |x-y| mod n
                q = mulmod(q, (x > y) ? x - y : y - x, n);
            }

            g = gcd(q, n);
            k += m;
        } while(k < r && g == 1);

        r <<= 1;
    } while(g == 1);

    if(g == n) {
        do {
            // ys = ys² + a mod n
            ys = mulmod(ys, ys, n);
            ys += a;

            if(ys < a) ys += (MAX_UINT64 - n) + 1;

            ys %= n;
            g = gcd((x > ys) ? x - ys : ys - x, n);
        } while(g == 1);
    }

    return g;
}
vector<uint64> prime_factors(uint64 n)
{
    vector<uint64> factors;
    vector<uint64> primes;
    uint64 factor = brent_pollard_factor(n);
    factors.push_back(n / factor);
    factors.push_back(factor);

    do {
        uint64 m = factors[factors.size() - 1];
        factors.pop_back();

        if(m == 1) continue;

        if(is_prime(m)) {
            primes.push_back(m);

            // Remove the prime from the other factors
            for(int i = 0; i < (int) factors.size(); i++) {
                uint64 k = factors[i];

                if(k % m == 0) {
                    do k /= m;

                    while(k % m == 0);

                    factors[i] = k;
                }
            }
        } else {
//            factor = (m < 100) ? small_factor(m) : brent_pollard_factor(m);
            factor = brent_pollard_factor(m);
            factors.push_back(m / factor);
            factors.push_back(factor);
        }
    } while(factors.size());

    return primes;
}
/** MAX = 10^16 */
int t;
uint64 n, i;
vector<uint64> v;
int main()
{
    scanf("%d", &t);

    while(t--) {
        v.clear();
        scanf("%lld", &n);
        //brents_factor(n, v);
        v = prime_factors(n);
        sort(v.begin(), v.end());

        for(i = 0; i < (int)v.size(); ++i)
            printf("%lld", v[i]), printf(" ");

        printf("\n");
    }

    return 0;
}

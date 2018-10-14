#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long tll;

int main() {
    freopen("input.txt", "r", stdin);

    int n;
    scanf("%d", &n);

    vector<tll> a(n);
    for (int i = 0; i < n; ++ i) scanf("%lld", &a [i]);

    tll check = 1;
    sort(a.rbegin(), a.rend());    
    while (check <= a [0]) check <<= 1;    
    check >>= 1;

    for (int b = 0; check >= 1; check >>= 1) {
        int foundIndex = -1;
        for (int i = b; i < n; ++ i)
            if (a [i] & check) {
                foundIndex = i;
                break;
            }
        if (foundIndex < 0) continue;
        swap(a [b], a [foundIndex]);
        for (int i = 0; i < n; ++ i)
            if (i != b && (a [i] & check)) a [i] ^= a [b];
        ++ b;
    }

    tll rtv = 0;
    for (int i = 0; i < n; ++ i) rtv ^= a [i];

    printf("%lld", rtv);

    return 0;
}
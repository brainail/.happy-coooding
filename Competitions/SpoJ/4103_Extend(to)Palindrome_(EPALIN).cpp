#include <stdio.h>
#include <iostream>
using namespace std;

const int MAXN = (int) 2e5 + 10;
char a [MAXN];
int p [MAXN];
int slen, n, kmp;
string s;

inline bool isGoodCh(const char ch) {
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

inline void addCh(const char ch) {
    a [slen ++] = ch;
    while (kmp && a [kmp] != ch) kmp = p [kmp - 1];
    p [slen - 1] = (kmp += (a [kmp] == ch && (slen - 1)));
}

int main() {
    freopen("input.txt", "r", stdin);
    while (getline(cin, s)) {
        slen = 0, n = s.length(), kmp = 0, p [0] = 0;
        for (int i = n - 1; i >= 0; -- i) if (isGoodCh(s [i])) addCh(s [i]);
        int sep = slen;
        addCh('#');
        for (int i = slen - 2; i >= 0; -- i) addCh(a [i]);
        for (int i = sep + 1; i < slen; ++ i) putchar(a [i]);
        for (int i = kmp; i < sep; ++ i) putchar(a [i]);
        putchar('\n');    
    }
}
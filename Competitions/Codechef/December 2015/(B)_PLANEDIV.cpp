#include <iostream>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long tll;
typedef long double tld;

template<class T> inline T gcd(T A, T B) { return (A < 0) ? gcd(-A, B) : ((B < 0) ? gcd(A, -B) : ((0 == B) ? A : gcd(B, A % B))); }
template<class T> inline T lcm(T A, T B) { return (A < 0) ? lcm(-A, B) : ((B < 0) ? lcm(A, -B) : (A * (B / gcd(A, B)))); }

struct Coeff { 
    tll a, b; 
    Coeff() : a (1L), b (1L) {} 
    void fix(); 
    tld flv() const; 
    bool eql(const Coeff &) const; 
    bool lss(const Coeff &) const; 
    void out();
};

inline void Coeff::fix() {
    tll d = gcd(a, b);
    a /= d, b /= d;
    if (a < 0) { a *= -1L, b *= -1L; }
    if (! a) { b = 1; }
}

inline tld Coeff::flv() const {
    return a / (b + .0);
}

inline bool Coeff::eql(const Coeff & another) const {
    return a == another.a && b == another.b;
}

inline bool Coeff::lss(const Coeff & another) const {
    return flv() < another.flv();
}

inline void Coeff::out() {
    printf("[%lld / %lld]", a, b);
}

struct Line { 
    Coeff A, B, C; 
    void out();
};

inline void Line::out() {
    A.out();
    printf(", ");
    B.out();
    printf(", ");
    C.out();
    printf("\n");
}

inline bool lines_cmp(const Line & l1, const Line & l2) {
    if (! l1.A.eql(l2.A) && l1.A.lss(l2.A)) return true;
    if (! l1.A.eql(l2.A) && l2.A.lss(l1.A)) return false;
    if (! l1.C.eql(l2.C) && l1.C.lss(l2.C)) return true;
    if (! l1.C.eql(l2.C) && l2.C.lss(l1.C)) return false;
    return false;
}

int N;
vector<Line> lines;
vector<Line> xlines;

inline void addline(Line line) {
    tll d = line.B.a;
    line.A.b = d;
    line.A.fix();
    line.C.b = d;
    line.C.fix();
    line.B.a = line.B.b = 1L;
    lines.push_back(line);
}

inline void addxline(Line line) {
    tll d = line.A.a;
    line.A.b = d;
    line.A.fix();
    line.C.b = d;
    line.C.fix();
    line.B.a = line.B.b = 0L;
    xlines.push_back(line);    
}

inline int linessubset(vector<Line> lines) {
    int N = lines.size();

    sort(lines.begin(), lines.end(), lines_cmp);
    
    for (int i = 0; i < N; ++ i) lines [i].out();
    printf("\n");

    int rtv = 0, i = 0;
    while (i < N) {
        int j = i + 1, ctv = 1;
        while (j < N && lines [i].A.eql(lines [j].A)) {
            if (! lines [j].C.eql(lines [j - 1].C)) ++ ctv;
            ++ j;
        }

        rtv = max (rtv, ctv), i = j;
    }

    return rtv;
}

int main() {
    freopen("input.txt", "r", stdin);

    int T;
    scanf("%d", &T);

    for (int testId = 0; testId < T; ++ testId) {
        scanf("%d", &N);

        lines.clear();
        lines.reserve(N);

        xlines.clear();
        xlines.reserve(N);

        for (int i = 0; i < N; ++ i) {
            Line line;
            scanf("%lld %lld %lld", & line.A.a, & line.B.a, & line.C.a);

            if (0 != line.B.a) {
                addline(line);
            } else {
                addxline(line);
            }
        }

        int rtv = linessubset(lines);
        rtv = max (rtv, linessubset(xlines));

        printf("%d\n", rtv);
    }
}
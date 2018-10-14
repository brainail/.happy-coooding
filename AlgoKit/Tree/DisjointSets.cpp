#include <algorithm>
#include <iostream>
using namespace std;

const int maxn = 200000;
int Rank[maxn];
int p[maxn];
int n;

void init(int _n) {
	n = _n;
	fill(Rank, Rank + n, 0);
	for (int i = 0; i < n; i++) p[i] = i;
}

int root(int x) {
	return x == p[x] ? x : (p[x] = root(p[x]));
}

void unite(int a, int b) {
	a = root(a);
	b = root(b);
	if (a == b) return;
	if (Rank[a] < Rank[b]) swap(a, b);
	if (Rank[a] == Rank[b]) ++Rank[a];
	p[b] = a;
}

int main() {
	init(3);
	unite(0, 2);
	cout << (0 == root(0)) << endl;
	cout << (1 == root(1)) << endl;
	cout << (0 == root(2)) << endl;
}

int n, l;
vector < vector<int> > g;
vector<char> used;
vector<int> tin, tout;
int timer;
vector < vector<int> > up;

void dfs (int v, int p = 0) {
	used[v] = true;
	tin[v] = ++timer;
	up[v][0] = p;
	for (int i=1; i<=l; ++i)
		up[v][i] = up[up[v][i-1]][i-1];
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (!used[to])
			dfs (to, v);
	}
	tout[v] = ++timer;
}

bool upper (int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca (int a, int b) {
	if (upper (a, b))  return a;
	if (upper (b, a))  return b;
	for (int i=l; i>=0; --i)
		if (! upper (up[a][i], b))
			a = up[a][i];
	return up[a][0];
}

int main() {
	used.resize (n),  tin.resize (n),  tout.resize (n),  up.resize (n);
	l = 1;
	while ((1<<l) <= n)  ++l;
	for (int i=0; i<n; ++i)  up[i].resize (l+1);
	dfs (0);

	for (;;) {
		int a, b; 
		int res = lca (a, b); 
	}

}
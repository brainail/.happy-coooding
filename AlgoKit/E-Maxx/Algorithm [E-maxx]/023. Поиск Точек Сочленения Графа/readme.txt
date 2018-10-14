vector < vector<int> > g;
vector<char> used;
vector<char> cutpoint;
int timer;
vector<int> tin, fup;

void dfs (int v, int p = -1) {
	used[v] = true;
	tin[v] = fup[v] = timer++;
	int children = 0;
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p)  continue; 
		if (used[to])
			fup[v] = min (fup[v], tin[to]);
		else {
			++children;
			dfs (to, v);
			fup[v] = min (fup[v], fup[to]);
			if (fup[to] >= tin[v])
				cutpoint[v] = true;
		}
	}
	if (p == -1)
		cutpoint[v] = children > 1;
}

int main() {
	int n;
	
	timer = 0;
	used.assign (n, false);
	cutpoint.assign (n, false);
	tin.resize (n);
	fup.resize (n);
	dfs (0);
}
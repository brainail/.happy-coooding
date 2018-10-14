vector < vector<int> > g;
vector<char> used;
int timer;
vector<int> tin, fup;

void dfs (int v, int p = -1) {
	used[v] = true;
	tin[v] = fup[v] = timer++;
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p)  continue;
		if (used[to])
			fup[v] = min (fup[v], tin[to]);
		else {
			dfs (to, v);
			fup[v] = min (fup[v], fup[to]);
			if (fup[to] > tin[v])
				IS_BRIDGE(v,to);
		}
	}
}

int main() {
	int n;
	
	timer = 0;
	used.assign (n, false);
	tin.resize (n);
	fup.resize (n);
	dfs (0);
}

vector < vector<int> > g; 
int n;

vector<bool> used;

vector<int> ans;

void dfs (int v)
{
	used[v] = true;
	for (vector<int>::itetator i=g[v].begin(); i!=g[v].end(); ++i)
		if (!used[*i])
			dfs (*i);
	ans.push_back (v);
}

void topological_sort (vector<int> & result)
{
	used.assign (n, false);
	for (int i=0; i<n; ++i)
		if (!used[i])
			dfs (i);
	result = ans;
}
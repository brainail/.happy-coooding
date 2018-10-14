void find_connected_components (const vector < vector<int> > & g, int n)
{
	vector<bool> used (n);
	cout << "Components:\n";
	for (int v=0; v<n; ++v)
		if (!used[v])
		{
			cout << "[ " << v;
			vector<int> q (n);
			int h=0, t=0;
			q[t++] = v;
			used[v] = true;
			while (h < t)
			{
				int cur = q[h++];
				for (vector<int>::iterator i=g[cur].begin(); i!=g[cur].end(); ++i)
					if (!used[*i])
					{
						used[*i] = true;
						q[t++] = *i;
						cout << ", " << *i;
					}
			}
			cout << " ]\n";
		}
}
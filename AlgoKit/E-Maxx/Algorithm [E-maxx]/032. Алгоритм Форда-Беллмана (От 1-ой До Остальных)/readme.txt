void solve() {
	vector<int> d (n, INF);
	d[v] = 0;
	for (;;) {
		bool any = false;
		for (int j=0; j<m; ++j)
			if (d[e[j].a] < INF)
				if (d[e[j].b] > d[e[j].a] + e[j].cost) {
					d[e[j].b] = d[e[j].a] + e[j].cost;
					any = true;
				}
		if (!any)  break;
	}
	// вывод d, например, на экран
}

void solve() {
	vector<int> d (n, INF);
	d[v] = 0;
	vector<int> p (n, -1);
	int x;
	for (int i=0; i<n; ++i) {
		x = -1;
		for (int j=0; j<m; ++j)
			if (d[e[j].a] < INF)
				if (d[e[j].b] > d[e[j].a] + e[j].cost) {
					d[e[j].b] = max (-INF, d[e[j].a] + e[j].cost);
					p[e[j].b] = e[j].a;
					x = e[j].b;
				}
	}
 
	if (x == -1)
		cout << "No negative cycle from " << v;
} else {
    x // negative cycle end
}
for (int k=0; k<n; ++k)
	for (int i=0; i<n; ++i)
		for (int j=0; j<n; ++j)
			d[i][j] = min (d[i][j], d[i][k] + d[k][j]);

for (int k=0; k<n; ++k)
	for (int i=0; i<n; ++i)
		for (int j=0; j<n; ++j)
			if (d[i][k] < INF && d[k][j] < INF)
				d[i][j] = min (d[i][j], d[i][k] + d[k][j]);

if (d[i][k] + d[k][j] < d[i][j] - EPS)
	d[i][j] = d[i][k] + d[k][j];
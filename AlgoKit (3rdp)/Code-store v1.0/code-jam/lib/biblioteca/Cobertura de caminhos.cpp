#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int capac [500][500];
int grafo [500][500];
int numAdj[500];
char marcado[500];
int n, k;
int source, sink;

/*
2696 - Air Raid - live archive
Cobertura mínima de caminhos
Caminho de aumento com dfs
*/

void read () {
	int a, b;
	scanf ("%d%d", &n, &k);
	
	source = 0;
	sink = n*2 + 1;
	memset (grafo, 0, sizeof(grafo));
	memset (capac, 0, sizeof(capac));
	memset (numAdj, 0, sizeof(numAdj));
	
	for (int i = 1; i <= n; i++) {
		grafo[source][numAdj[source]++] = i;
		grafo[i][numAdj[i]++] = source;
		capac[source][i] = 1;
		capac[i][source] = 0;		
		
		grafo[n+i][numAdj[n+i]++] = sink;
		grafo[sink][numAdj[sink]++] = n+i;
		capac[n+i][sink] = 1;
		capac[sink][n+i] = 0;
	}
	
	for (int i = 0; i < k; i++) {
		scanf ("%d%d", &a, &b);
		b += n;
		
		grafo[a][numAdj[a]++] = b;
		grafo[b][numAdj[b]++] = a;
		capac[a][b] = 1;
		capac[b][a] = 0;
	}
	
}

bool dfs (int no) {
	int adj;
	if (marcado[no]) return false;
	
	marcado[no] = 1;
	if (no == sink) return true;
	for (int i = 0; i < numAdj[no]; i++) {
		adj = grafo[no][i];
		if (capac[no][adj] == 1) {
			bool ret = dfs (adj);
			if (ret) {
				capac[no][adj] = 0;
				capac[adj][no] = 1;
				return true;	
			}
		}	
	}
	return false;
}

void process () {
	int i = 0;
	
	memset (marcado, 0, sizeof (marcado));
	while (dfs (source)) {
		i++;
		memset (marcado, 0, sizeof (marcado));
	}
	
	printf ("%d\n", n-i);
}

int main () {
	freopen ("2696.in","r",stdin);
	freopen ("2696.out","w",stdout);
	
	int casos;
	scanf ("%d", &casos);
	while (casos--) {
		read();
		process();
	}

	return 0;	
}	

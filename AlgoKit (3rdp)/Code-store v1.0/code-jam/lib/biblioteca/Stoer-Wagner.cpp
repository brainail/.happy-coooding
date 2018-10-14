#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <algorithm>

#define LIM 110

using namespace std;

int cost[LIM][LIM];
int adj [LIM][LIM];
int nadj[LIM];
int rep [LIM];
int dist[LIM];
char mark[LIM];
int n, m;

int read () {
	scanf ("%d%d", &n, &m);
	int a, b, c;
	
	memset (nadj, 0, sizeof (nadj));
	memset (cost, 0, sizeof (cost));
	for (int i = 0; i < m; i++) {
		scanf ("%d%d%d", &a, &b, &c);
		cost[a][b] = cost[b][a] = c;
	}
	for (int i = 1; i <= n; i++) {
		rep[i] = i;	
	}
	
	return 1;	
}

int fs (int a) {
	int temp = a, temp2;
	while (rep[temp] != temp) temp = rep[temp];
	while (rep[a] != temp) {
		temp2 = rep[a];
		rep[a] = temp;
		a = temp2;	
	}	
	return temp;
}

void merge (int a, int b) {
	rep[a] = b;
	for (int i = 1; i <= n; i++) {
		cost[b][i] += cost[a][i];	
	}
}

int iter () {
	int atual, last, next;
	memset (dist, 0, sizeof (dist));
	memset (mark, 0, sizeof (mark));
	
	int r;
	atual = next = fs(1);
	while (1) {		
		last = atual;
		atual = next;
		mark[atual] = 1;
		
		next = 0;
		for (int i = 1; i <= n; i++) {
			r = fs(i);
			if (!mark[r]) {
				dist[r] += cost[atual][i];
				if (dist[r] >= dist[next]) next = r;
			}
		}
		if (!next) break;
	}
	
	merge (last, atual);
	
	return dist[atual];
}

void process () {
	if (n == 1) {
		printf ("0\n");
		return;	
	}
	int mini = 1<<30;
	for (int i = 1; i < n; i++) {
		mini = min (mini, iter());	
	}	
	printf ("%d\n", mini);
}

int main () {
 
	int casos;
	scanf ("%d", &casos);
	while (casos--) {
		read();	
		process();
	}
	return 0;
}

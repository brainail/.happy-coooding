/*
 *	Problem:  POJ 3691
 *	Source:   2008 hefei preliminary online.
 *	Algorithm: Trie Graph + DP.
 *	Reference: Trie Graph paper -> wc2006, maigo.
 * */

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXSIZE = 1000;
const int MAXCHAR = 4;
const int MAXNODE = 1000;

int N, len, nodes, caseID = 1;
char buf[MAXSIZE+1];
int trie[MAXNODE][MAXCHAR], suffix[MAXNODE], danger[MAXNODE], 
	dp[MAXSIZE][MAXNODE], que[MAXNODE], dna[MAXSIZE];

inline int getDNA(char c) {
	switch(c) {
		case 'A': return 0;
		case 'G': return 1;
		case 'C': return 2;
		case 'T': return 3;
	}
}

int build_trie_tree() {
	scanf("%d", &N);
	if (!N) return 0;
	int i, j;
	memset(trie, 0, sizeof(trie));
	memset(danger, 0, sizeof(danger));

	nodes = 1;
	for (i = 0; i < N; i++) {
		scanf("%s", buf);
		len = strlen(buf);
		int p = 1;
		for (j = 0; j < len; j++) {
			int d = getDNA(buf[j]);
			if (!trie[p][d]) 
				trie[p][d] = ++nodes;
			p = trie[p][d];
			if (danger[p]) break;
		}
		danger[p] = 1;
	}
	return 1;
}

void build_trie_graph() {
	int i, front, rear;
	front = rear = 0;
	memset(suffix, 0, sizeof(suffix));

	for (i = 0; i < MAXCHAR; i++) {
		if (!trie[1][i]) trie[1][i] = 1;
		else {
			que[rear++] = trie[1][i];
			suffix[trie[1][i]] = 1;
		}
	}

	while (front < rear) {
		int node = que[front++];
		danger[node] = danger[node] || danger[suffix[node]];
		if (!danger[node]) {
			for (i = 0; i < MAXCHAR; i++) {
				if (!trie[node][i]) trie[node][i] = trie[suffix[node]][i];
				else {
					que[rear++] = trie[node][i];
					suffix[trie[node][i]] = trie[suffix[node]][i];
				}
			}
		}
	}
}

void checkmin(int &a, int b) {
	if (a == -1) a = b;
	else if (a > b) a = b;
}

void solve() {
	int i, j, k;
	scanf("%s", buf);
	len = strlen(buf);
	for (i = 0; i < len; i++) dna[i] = getDNA(buf[i]);

	memset(dp, -1, sizeof(dp));
	if (!danger[trie[1][dna[0]]]) dp[0][trie[1][dna[0]]] = 0;
	for (i = 0; i < MAXCHAR; i++) {
		if (dna[0] != i && !danger[trie[1][i]]) dp[0][trie[1][i]] = 1;
	}
	for (i = 1; i < len; i++) {
		for (j = 1; j <= nodes; j++) {
			if (dp[i-1][j] == -1) continue;
			if (!danger[trie[j][dna[i]]])
				checkmin(dp[i][trie[j][dna[i]]], dp[i-1][j]);
			for (k = 0; k < MAXCHAR; k++) {
				if (dna[i] != k && !danger[trie[j][k]])
					checkmin(dp[i][trie[j][k]], dp[i-1][j]+1);
			}
		}
	}
	int ans = INT_MAX;
	for (i = 1; i <= nodes; i++)
		if (!danger[i] && dp[len-1][i] != -1 && dp[len-1][i] < ans)
			ans = dp[len-1][i];
	if (ans == INT_MAX) ans = -1;
	printf("Case %d: %d\n", caseID++, ans);
}

int main() {
	while (build_trie_tree()) {
		build_trie_graph();
		solve();
	}
return 0;
}


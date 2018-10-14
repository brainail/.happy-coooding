#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>
#include <vector>

using namespace std;

/*
610 - Street Directions
Encontra Componentes Biconexos e pontes.
Converter estradas bidirecionais em unidirecionais
*/

int grafo[1002][1002], d[1002],n, m, dfs_number[1002], cont, caso, mark[1002][1002];
stack < pair<int, int> > pilha;
vector< pair<int, int> > vetores;

int read(){
	int a, b;
	scanf("%d%d", &n, &m);
	
	if(!n && !m)return 0;
	memset(d, 0, sizeof(d));
	memset(mark, 0, sizeof(mark));
	
	for(int i = 0; i < m; i++){
		scanf("%d %d", &a, &b);
		grafo[a][d[a]++] = b;
		grafo[b][d[b]++] = a;
	}
	
	return 1;
}

int dfs(int no, int pai){
	int min, temp, v;
	min = dfs_number[no] = cont++;

	for(int i = 0; i < d[no]; i++){
		v = grafo[no][i];
		if(v == pai)continue;	
		if(!mark[v][no]){
			pilha.push(make_pair(no, v));
			mark[no][v] = 1;
		}
		if(!dfs_number[v]){
			
			temp = dfs(v, no);
			
			if(temp == dfs_number[no]){
				while(pilha.top().first != no){
					vetores.push_back(pilha.top());
					pilha.pop();	
				}
					vetores.push_back(pilha.top());
					pilha.pop();
			}
			if(temp > dfs_number[no]){
				vetores.push_back(pilha.top());
				vetores.push_back(make_pair( pilha.top().second, pilha.top().first));
				pilha.pop();
			}
			min <?= temp;
		}else{
			min <?= dfs_number[v];
		}
	}
	
	return min;
}

void process(){
	cont = 1;
	vetores.clear();
	memset(dfs_number , 0, sizeof(dfs_number));
	dfs(1, 1);
	printf("%d\n\n", caso++);
	for(int i = 0; i < vetores.size(); i++){
		printf("%d %d\n", vetores[i].first, vetores[i].second);
	}
	printf("#\n");
}

int main(){
	
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
	caso = 1;
	while(read())process();
	
	return 0;
}

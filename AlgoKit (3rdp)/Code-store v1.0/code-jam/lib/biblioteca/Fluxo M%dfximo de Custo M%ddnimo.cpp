#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <map>
#define source 0
#define sink (u + v + 1)
#define mp(a,b) make_pair(a, b)
#define INF 1000000000

using namespace std;

int u, v, d[650], e, grafo[650][650], dist[650], pot[650], custo[650][650], cap[650][650], mark[650], pai[650];
map <int , int> mapa1, mapa2;
int cont1, cont2;

int read(){
	int a,b,c;
	scanf("%d%d", &u, &v);
	scanf("%d", &e);
	memset(d, 0, sizeof(d));
	mapa1.clear();
	mapa2.clear();
	cont1 = 1;
	cont2= u + 1;
	for(int i = 1; i<= u;i++){
		grafo[source][d[source]++] = i;
		grafo[i][d[i]++] = source;
		cap[source][i] = 1;
		cap[i][source] = 0;
		custo[source][i] = custo[i][source] = 0;
	}
	
	for(int i = u + 1; i<= u + v;i++){
		grafo[sink][d[sink]++] = i;
		grafo[i][d[i]++] = sink;
		cap[sink][i] = 0;
		cap[i][sink] = 1;
		custo[sink][i] = custo[i][sink] = 0;
	}
	
	for(int i = 0; i < e;i++){
		scanf("%d %d %d", &a, &b, &c);
		a++;
		b++;
		if(mapa1[a]==0)mapa1[a] = cont1++;
		if(mapa2[b]==0)mapa2[b] = cont2++;
		a = mapa1[a];
		b = mapa2[b];
		grafo[a][d[a]++] = b;
		grafo[b][d[b]++] = a;
		custo[a][b] = c;
		custo[b][a] = -c;
		cap[a][b] = 1;
		cap[b][a] = 0;
	}
	return 1;
}

int dij(){
	priority_queue < pair <int, int> > heap;
	int atual, adj, achou = 0;
	memset(dist, -1, sizeof(dist));
	memset(mark, 0, sizeof(mark));
	dist[source] = 0;
	heap.push(mp(d[source], source));
	
	while(!heap.empty()){
		atual = heap.top().second;
		heap.pop();
		if(mark[atual])continue;
		mark[atual] = 1;
		if(atual == sink)achou = 1;
		for(int i = 0; i < d[atual]; i++){
			adj = grafo[atual][i];
			if(cap[atual][adj]){
				if(dist[adj] == -1 || (dist[atual] + custo[atual][adj] + pot[atual] - pot[adj] < dist[adj])){
					dist[adj] = dist[atual] + custo[atual][adj] + pot[atual] - pot[adj];
					heap.push(mp(-dist[adj], adj));
					pai[adj]= atual;
				}
			}
		}
	}	
	return achou;
}

void aument(int no){
	if(no == source)return;
	cap[pai[no]][no] = 0;
	cap[no][pai[no]] = 1;
	aument(pai[no]);
}

void process(){
	int total = 0;
	memset(pot, 0, sizeof(pot));
	while(dij()){
		aument(sink);
		for(int i = 0; i <= sink; i++){
			if(dist[i] != -1)pot[i] += dist[i];
			else pot[i] = 0;
		}
	}
	
	for(int i = 1; i <= u; i++)
		for(int j = 0; j < d[i]; j++)total += custo[i][grafo[i][j]]*cap[grafo[i][j]][i];
	printf("%d\n", total);
}

int main(){
    
    int casos, p = 1;
    freopen("G.in", "r",stdin);
    freopen("G.out", "w", stdout);
    scanf("%d", &casos);
    while(casos--){
    	read();
    	if(!p)printf("\n");
    	else p = 0;
    	process();
    }
    
    return 0;
}

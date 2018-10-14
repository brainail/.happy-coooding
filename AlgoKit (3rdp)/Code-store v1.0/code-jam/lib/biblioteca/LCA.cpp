#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIM 50000

/*
Calcula a distância entre dois vértices numa árvore
Até 10000 query's e 50000 vértices
*/

struct no{
    int adj[10];
    int custo[10];
    int q;
};

no TREE[LIM];
int n,m;

int readdata(){
    if( scanf("%d %d",&n,&m) != 2 ) return 0;
    int i,c;
    int x,y;
    char lixo[10];
    
    for(i=0;i<n;i++) TREE[i].q = 0;
    
    for(i=0;i<m;i++){
        scanf("%d %d %d %s",&x,&y,&c,lixo);
        
        TREE[x].adj[ TREE[x].q ] = y;
        TREE[x].custo[ TREE[x].q ] = c;
        TREE[x].q++;
        
        TREE[y].adj[ TREE[y].q ] = x;
        TREE[y].custo[ TREE[y].q ] = c;
        TREE[y].q++;
    }
    
    return 1;
}

int LV[LIM];
int T[LIM]; // Diz que é o pai do nó [i]
int c_pai[LIM]; //Custo para o pai do nó [i]

int P[LIM][20]; // 2^j-esimo ancestral
int COST[LIM][20]; //custo para os 2^j-esimos ancestrais 

int mark[LIM];

int dfs(int no,int level){
    
    LV[no] = level;
    
    int i;
    for(i=0;i < TREE[no].q; i++){
        if( !mark[ TREE[no].adj[i] ] ){
            mark[ TREE[no].adj[i] ]  = 1;
            
            T[ TREE[no].adj[i] ] = no;
            c_pai[ TREE[no].adj[i] ] = TREE[no].custo[i];
            dfs(TREE[no].adj[i],level + 1);
        }
    }
    
    return 0;
}

int preprocess(){
    
    int i,j;
    
    for(i=1;i<=n;i++){
        P[i][0] = T[i];
        if( P[i][0] != -1 ) COST[i][0] = c_pai[i];
    }
    
    for(j=1; 1<<j < n ;j++){
        for(i=1;i<=n;i++){
            if( P[i][j-1] != -1 ){
                P[i][j] = P[ P[i][j-1] ][ j-1 ];
                if( P[i][j] != -1 )
                    COST[i][j] = COST[i][j-1] + COST[ P[i][j-1] ][j-1];
            }
        }
    }

    return 0;
}

int lca(int no1,int no2){

    int i,j;
    int dist = 0;
    
    //Sobe o primeiro nó, até eles ficarem no mesmo level
    if( LV[no1] != LV[no2] ){
        for(j=15;j>=0;j--){
            if( P[no1][j] != -1 ){
                if( LV[ P[no1][j] ] >= LV[no2] ){
                    dist += COST[no1][j];
                    no1 = P[no1][j];
                }
            }
        }
    }
    
    // Se o No2 é ancestral de No1
    if( no1 == no2 ) return dist;
    
    for(j=15;j>=0;j--){
        if( P[no1][j] != -1 && P[no1][j] != P[no2][j] ){
            dist += COST[no1][j];
            dist += COST[no2][j];
            no1 = P[no1][j];
            no2 = P[no2][j];
        }
    }
    
    if( no1 == no2 ) return dist;
    
    return dist + COST[no1][0] + COST[no2][0];
}

int process(){
    
    memset(mark,0,sizeof(mark));
    memset(T,-1,sizeof(T));
    memset(P,-1,sizeof(P));
    memset(COST,0,sizeof(COST));
    memset(c_pai,-1,sizeof(c_pai));
    
    //Determina o level de cada nó
    dfs(mark[1] = 1,0);
    
    preprocess();  // N log N
      
    int q;
    scanf("%d",&q);
    
    int no1,no2;
    
    while(q--){
        scanf("%d %d",&no1,&no2);
        
        if( LV[no1] < LV[no2] ) no1 ^= no2 ^= no1 ^= no2;
        
        printf("%d\n",lca(no1,no2));  // log N
    }
    
    return 0;
}

int main(){
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    
    while(readdata())process();
    return 0;
}

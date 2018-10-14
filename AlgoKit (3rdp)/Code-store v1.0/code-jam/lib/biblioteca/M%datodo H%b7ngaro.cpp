#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>

using namespace std;

#define LIM 501
#define INF 99999999


/*
11383 - Golden Tiger Claw

Entrada:
N
matriz NxN

Sa�da:
linha resultado
coluna resultado
soma total
*/

int lx[LIM],ly[LIM];
int mark_T[LIM];

vector <int> S,T;

int vizinhos_X[LIM][LIM]; 
int num_vizinhos_X[LIM];

int saturadoX[LIM]; // Para os v�rtices de X ( Grafo bipartido (X,Y) )
int saturadoY[LIM];

// para achar o caminho de aumento
int paiX[LIM];  // Pai de um v�rtice em Y !
int paiY[LIM];  // Pai de um v�rtice em X !

int match[LIM]; // Matching apenas dos v�rtices de Y ! ( Grafo (X,Y) )

int N;

int w[LIM][LIM];

int readdata(){
    if( scanf("%d",&N) != 1 ) return 0;    
    
    int i,j;
    for(i=1;i<=N;i++){
        for(j=1;j<=N;j++){
            scanf("%d",&w[i][j]);
        }
    }

    return 1;
}

int m_nao_saturado(){
    int i;
    for(i=1;i<=N;i++){
        if( saturadoX[i] == 0 ) return i;
    }
    return 0;
}

int escolhe_vizinho_nao_em_T(int *x_pai){
    int i,j;
    
    for(i=0;i<S.size();i++){
        for(j=0; j < num_vizinhos_X[ S[i] ] ; j++){
            if( !mark_T[ vizinhos_X[ S[i] ][j] ] ){
                *x_pai = S[i];
                return vizinhos_X[ S[i] ][j];
            }
        }
    }
    
    return -1;
}

int clean_and_create(){
    
    memset(num_vizinhos_X,0,sizeof(num_vizinhos_X));
    memset(mark_T,0,sizeof(mark_T));
    memset(saturadoX,0,sizeof(saturadoX));
    memset(saturadoY,0,sizeof(saturadoY));
    memset(match,-1,sizeof(match));
    memset(paiX,-1,sizeof(paiX));
    memset(paiY,-1,sizeof(paiY));
    
    int i,j;
    
    for(i=1;i<=N;i++){
        for(j=1;j<=N;j++){
            if( lx[i] + ly[j] == w[i][j] ){
                vizinhos_X[i][ num_vizinhos_X[i]++ ] = j;
            }
        }
    }
    
    return 0;
}

int start(){
    int i,j,k;
    
    for(i=1;i<=N;i++){
        k = -1;
        for(j=1;j<=N;j++){
            if( w[i][j] > k ) k = w[i][j];
        }
        lx[i] = k;
        ly[i] = 0;
    }
    
    clean_and_create();
    
    return 0;
}

int compute(){
    int i,j;
    
    int best = INF;
    
    for(i=0;i<S.size();i++){
        for(j=1;j<=N;j++){
            if( !mark_T[ j ] ){
                if( lx[S[i]] + ly[j] - w[S[i]][j] < best ){
                   best = lx[S[i]] + ly[j] - w[S[i]][j];
                }
            }
        }
    }
    
    for(i=0;i<S.size();i++){
        lx[ S[i] ] -= best;
    }
    
    for(i=0;i<T.size();i++){
        ly[ T[i] ] += best;
    }
     
    clean_and_create();
    
    return 0;
}

int process(){
    
    int i,u,y,z;
    int x_pai;
    
    start();
    
    while( u = m_nao_saturado() ){

        S.clear();
        T.clear();
        memset(mark_T,0,sizeof(mark_T));
        
        S.push_back(u);
        
        while(1){
            
            /* pega um v�rtice em Y (vizinho de algu�m que esteja em S) 
             que nao perten�a a T */
            y = escolhe_vizinho_nao_em_T(&x_pai);
        
            if( y == -1 ){ // n�o encontrou matching perfeito
                 compute(); // calcula novos valores para lx e ly
                 break;
            }
            else{
                if( saturadoY[y] ){
                    S.push_back(match[y]);
                    T.push_back(y);
                    
                    mark_T[ y ] = 1;
                    
                    paiX[y] = x_pai;
                    paiY[ match[y] ] = y;
                }
                else{
                    // caminho de aumento
                    paiX[y] = x_pai;
                    
                    int atual = y;
                    
                    while( atual != -1 ){
                        
                        match[ atual ] = paiX[atual];
                        saturadoY[atual] = 1;
                        saturadoX[ paiX[atual] ] = 1;   
                        
                        atual = paiY[ paiX[atual] ] ; // atual sempre � um vertice de Y
                    }
                    
                    break;
                }
            }
        }

    }
    
    
    int sum = 0;
    
    for(i=1;i<=N;i++){
        if( i > 1 ) printf(" ");
        printf("%d",lx[i]);
        sum += lx[i];
    }
    printf("\n");
    
    for(i=1;i<=N;i++){
        if( i > 1 ) printf(" ");
        printf("%d",ly[i]);
        sum += ly[i];
    }
    printf("\n%d\n",sum);
    
    return 0;
}

int main(){
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    
    while(readdata()) process();
    return 0;
}

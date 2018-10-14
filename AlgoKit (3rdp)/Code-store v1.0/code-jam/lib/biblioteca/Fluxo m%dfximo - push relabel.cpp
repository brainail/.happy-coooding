#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIM 251
#define INF 10000000
#define sink (2*n+1)

using namespace std;

/*
10330 - Power Transmission 
Fluxo máximo - Push-Relabel
*/

int cap[LIM][LIM];
int numadj[LIM];
int viz[LIM][LIM];
int n;

int e[LIM],h[LIM],mark[LIM];

int fila[LIM*LIM];

int ini,fim;

int readdata(){
    if( scanf("%d",&n) != 1 ) return 0;
        
    int i,j,k;
    
    memset(numadj,0,sizeof(numadj));
    memset(cap,0,sizeof(cap));
    
    for(i=0;i<n;i++){
        scanf("%d",&k);
        cap[2*i+1][2*i+2] = k;
        viz[2*i+1][numadj[2*i+1]++] = 2*i+2; 
        viz[2*i+2][numadj[2*i+2]++] = 2*i+1;
    }
    
    int ar,c;
    scanf("%d",&ar);
    
    for(i=0;i<ar;i++){
        scanf("%d %d %d",&j,&k,&c);
        j--;k--;
        cap[2*j+2][2*k+1] = c;
        viz[2*j+2][numadj[2*j+2]++] = 2*k+1; 
        viz[2*k+1][numadj[2*k+1]++] = 2*j+2;
    }
    
    int b,d;
    scanf("%d %d",&b,&d);
    
    for(i=0;i<b;i++){
        scanf("%d",&j); j--;
        cap[0][2*j+1] = INF;
        viz[0][numadj[0]++] = 2*j+1; 
        viz[2*j+1][numadj[2*j+1]++] = 0; 
    }
    
    for(i=0;i<d;i++){
        scanf("%d",&j); j--;
        cap[2*j+2][sink] = INF;
        viz[2*j+2][numadj[2*j+2]++] = sink; 
        viz[sink][numadj[sink]++] = 2*j+2; 
    }
    
    return 1;
}

int init(){
    memset(h,0,sizeof(h));
    memset(e,0,sizeof(e));
    memset(mark,0,sizeof(mark));
    
    ini = fim = 0;
    
    h[0] = sink+1;
    
    int i,u;
    for(i=0; i<numadj[0]; i++){
        u = viz[0][i];
        e[u] = cap[0][u];
        e[0] -= cap[0][u];
        
        cap[u][0] = cap[0][u];
        cap[0][u] =  0;
        
        if( u != sink ){
            fila[fim++] = u;
            mark[u] = 1;
        }
    }
    
    return 0;
}

int push(int u,int v){
    int min = e[u];    
    min <?= cap[u][v];
    
    e[u] -= min;
    e[v] += min;
    
    cap[u][v] -= min;
    cap[v][u] += min;
    
    return 0;    
}

int process(){
        
    init();
    int i,min,k,u;
    
    while( ini!= fim ){
        u = fila[ini];
        min = INF;

        for(i=0;i<numadj[u] && e[u] > 0;i++){
            k = viz[u][i];
            
            if( cap[u][k] > 0 ) {
                if( h[u] == h[k] + 1 ){
                    push(u,k);
                    if( k != 0 && k != sink && !mark[k] )  fila[fim++] = (mark[k] = k);
                }
                else{
                    min <?= h[k];
                }
            }
        }
        
        if( e[u] == 0 ) {
            ini++;
            mark[u] = 0;
        }
        else{
            h[u] = min+1;
        }
    }
    
    printf("%d\n",e[sink]);
    
    return 0;
}

int main(){    
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    
    while( readdata() ) process();
    return 0;
}

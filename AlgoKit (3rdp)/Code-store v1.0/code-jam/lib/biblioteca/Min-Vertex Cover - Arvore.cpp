#include <stdio.h>
#include <string.h>
#include <stdio.h>

int PAI[1501];

int n;
int marcado[1501];
int FOLHAS[1501];
int FILHOS[1501];
int marks[1501];
int f;

/*
2038 - Strategic game - live archive
Min-Vertex cover em uma Árvore
entrada: 
n  => numero de vertices
id:(q)  => id do vertice, numero de vizinhos e lista de vizinhos
*/

int readdata(){
    if( scanf("%d",&n) != 1 ) return 0;
    
    int i,j,k,filho,tam;
    
    memset(PAI,-1,sizeof(PAI));
    memset(FILHOS,0,sizeof(FILHOS));
    memset(marks,0,sizeof(marks));
    f = 0;
    
    for(i=0;i<n;i++){
        scanf("%d:(%d)",&k,&tam);
        if(tam == 0){
             FOLHAS[f++] = k;        
             marks[k] = 1;
        }
        FILHOS[k] = tam;
        
        for(j=0;j<tam;j++){
            scanf("%d",&filho);
            PAI[filho] = k;
        }
        
    }
    return 1;
}


int process(){
    
    memset(marcado,0,sizeof(marcado));
    
    int i,k;
    int para = 0;

    for(i=0;i<f;i++){
        if( PAI[FOLHAS[i]] != -1 && !marcado[ PAI[FOLHAS[i]] ] ){
            marcado[ PAI[FOLHAS[i]] ] = 1;
            if(PAI[ PAI[FOLHAS[i]] ] != -1) FILHOS[ PAI[ PAI[FOLHAS[i]]]]--;
            
            if(PAI[ PAI[FOLHAS[i]] ] != -1 && !marcado[PAI[ PAI[FOLHAS[i]] ]] &&
            FILHOS[ PAI[ PAI[FOLHAS[i]]]] == 0){
                if( !marks[  PAI[ PAI[FOLHAS[i]] ] ] ) {
                    marks[  PAI[ PAI[FOLHAS[i]] ] ] = 1;
                    FOLHAS[ f++ ] = PAI[ PAI[FOLHAS[i]] ] ;
                }
            }
        }
    }
    
    
    int c = 0;
    for(i=0;i<n;i++){
        if( marcado[i] ) c++;
    }
    printf("%d\n",c);
    return 0;
}

int main(){
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    while(readdata()) process();
    return 0;
}

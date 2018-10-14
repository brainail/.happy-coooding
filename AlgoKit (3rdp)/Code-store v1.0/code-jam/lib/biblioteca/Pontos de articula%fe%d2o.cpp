#include <stdio.h>
#include <string.h>

int grafo[101][101];
int LOW[101],critic[101],dfsnumber[101];

int n,dfn,raiz;

char line[1000];

int readdata(){
    scanf("%d",&n);
    fgets(line,1<<20,stdin);
    return n;
}

int DFS(int k,int pai){
    
    dfsnumber[k] = dfn++;
    LOW[k] = dfsnumber[k];
    
    int i,filhos=0;
    
    for(i=0;i<n;i++){
        if( grafo[k][i] ){
            if( pai == i ) continue;
            
            if( dfsnumber[i] == 0 ){
                filhos++;
                DFS(i,k);
                if( LOW[i] >= dfsnumber[k] ){
                    if( raiz != k || filhos > 1 ){
                        critic[k] = 1;
                    }
                }
                if( LOW[i] < LOW[k] ) LOW[k] = LOW[i];
            }
            else{
                if( dfsnumber[i] < LOW[k] ) LOW[k] = dfsnumber[i];
            }
        }
    }
    
    return 0;
}

int process(){
    
    memset(grafo,0,sizeof(grafo));
    
    int k,tam,i;
    char word[100];
    int pos;
    int num;
    
    fgets(line,1<<20,stdin);
    sscanf(line,"%d",&k);
    
    tam = strlen(line);
    
    int si,sf;
    
    while( k != 0 ){

        num = 0;
        for(i=0;i<tam;i++){
            pos = 0;
            if( line[i] >= '0' && line[i] <= '9' ){
                while( i < tam && (line[i] >= '0' && line[i] <= '9') ){
                   word[pos++] = line[i];
                   i++;        
                }
                word[pos] = '\0';
                
                if( num == 0 ){
                    sscanf(word,"%d",&si);
                    si--;
                }
                else{
                    sscanf(word,"%d",&sf);
                    sf--;
                    grafo[si][sf] = 1;   
                    grafo[sf][si] = 1;                
                }
                num++;
            }       
        }
        
        fgets(line,1<<20,stdin);
        sscanf(line,"%d",&k);
        tam = strlen(line);
    }
    
    memset(dfsnumber,0,sizeof(dfsnumber));
    memset(critic,0,sizeof(critic));

    dfn = 1;
    k=0;

    raiz = k;
    DFS(k,-1);
    
    k=0;
    for(i=0;i<n;i++){
        if( critic[i] ){
            k++;
        }
    }
    
    printf("%d\n",k);
    return 0;
}


int main(){
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);

    while(readdata()) process();
    return 0;
}

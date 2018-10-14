#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <map>
#include <list>
#include <queue>
#include <ctype.h>

#define UNREACHED 0
#define PAR 1
#define IMPAR 2
#define NULO -1
#define LIM 90

using namespace std;

int N;
int val[LIM];

int mat[LIM][LIM];
int adj[LIM][LIM];
int nadj[LIM];

int status[LIM],pai[LIM],fila[LIM],ini,fim;
int root[LIM],base[LIM],match[LIM];

int rep[LIM],tam[LIM];
pair < int , int > ponte[LIM];

int find(int no){
    if( rep[no] != no ) return rep[no] = find(rep[no]);
    return no;
}
void uniao(int a,int b){
    int p1 = find(a),p2 = find(b);
    if( p1 == p2 ) return;
    if( tam[p1] < tam[p2] ){
        rep[p1] = p2;
    }
    else if( tam[p1] > tam[p2] ){
        rep[p2] = p1;
    }
    else{
        rep[p1] = p2;
        tam[p2]++;
    }
}

int read(){
    scanf("%d",&N);
    int i,j;

    N = (1<<N);
    
    for(i=0;i<N;i++){
        for(j=i+1;j<N;j++){
            scanf("%d",&mat[i][j]);
        }    
    }
    return 1;
}

int visited[LIM];

int nca(int x,int y){
    int xbase = base[ find(x) ];
    int u;
    if( visited[ xbase ] ) u = xbase;
    else{
        visited[xbase] = 1;
        if( y != NULO ) u = nca(y,pai[xbase]);
        else  u = nca(pai[xbase],y);
        visited[xbase] = 0;
    }
    return u;
}

list < int > path(int x,int y){
    list < int > ret;
    if( x == y ){
        ret.push_back(x);
    }
    else if( status[x] == PAR ){
        ret.push_back(x); ret.push_back( pai[x] );
        list < int > path2 = path( pai[ pai[x] ], y );
        ret.splice ( ret.end() , path2 );
    }
    else{
        ret.push_back(x);
        int s = ponte[x].first, t = ponte[x].second;
        
        list < int > path1 = path(s,match[x]);
        path1.reverse();
        list < int > path2 = path(t,y);
        
        ret.splice ( ret.end() , path1 );
        ret.splice ( ret.end() , path2 );
    }
    return ret;
}

int edmonds(){
    
    ini = fim = 0; // ponteiros da fila
    
    memset(status,UNREACHED,sizeof(status));

    int i;
    for(i=0;i<N;i++){
        rep[i] = i;
        tam[i] = 0;
        base[i] = i;
        pai[i] = NULO;
        
        if( match[i] == NULO ){
            fila[fim++] = i;
            status[i] = PAR;
            root[i] = i;
        }
    }
    
    while( ini < fim ){
        int v = fila[ini];
        ini++;
            
        for(i=0;i<nadj[v];i++){
            int w = adj[v][i];
            
            if( status[w] == UNREACHED ){ 
                // extensão da árvore
                root[w] = root[v];  status[w] = IMPAR; pai[w] = v;
                root[ match[w] ] = root[v];  status[ match[w] ] = PAR;  pai[ match[w] ] = w;
                
                fila[fim++] = match[w];
            }
            
            int wbase = base[ find(w) ];
            if( status[wbase] == PAR && root[v] != root[w] ){ 
                // caminho aumento
                list < int > aumentingpath = path(v,root[v]);
                aumentingpath.reverse();
                list < int > aumentingpath2 = path(w,root[w]);
                aumentingpath.splice( aumentingpath.end(), aumentingpath2 );
                
                list < int >::iterator iter;
                
                for( iter = aumentingpath.begin() ; iter != aumentingpath.end(); iter++ ){
                    int x = *iter;
                    iter++;
                    int y = *iter;
                    match[x] = y;
                    match[y] = x;
                }
                return 1;
            }
            
            int vbase = base[ find(v) ];
            if( status[wbase] == PAR && root[v] == root[w] && vbase != wbase ){ 
                // shrink
                int u = nca(v,w);
                int xbase;
                for(xbase = base[ find(v) ]; xbase != u; xbase = base[ find(pai[xbase]) ] ){
                    uniao( find(u), find(xbase) );
                    if( status[ xbase ] == IMPAR ){
                        fila[fim++] = xbase;
                        ponte[xbase] = make_pair(v,w);
                    }
                    base[ find(u) ] = u;
                }
                
                for(xbase = base[ find(w) ]; xbase != u; xbase = base[ find(pai[xbase]) ] ){
                    uniao( find(u), find(xbase) );
                    if( status[ xbase ] == IMPAR ){
                        fila[fim++] = xbase;
                        ponte[xbase] = make_pair(w,v);
                    }
                    base[ find(u) ] = u;
                }
            }
        } 
    }
    
    return 0;
}

int ok(int val){
    int i,j;
    memset(nadj,0,sizeof(nadj));
    for(i=0;i<N;i++){
        for(j=i+1;j<N;j++){
            if( mat[i][j] >= val ){
                adj[i][ nadj[i]++ ] = j;
                adj[j][ nadj[j]++ ] = i;
            }
        }
    }
    
    int ret = 0;
    memset(match,NULO,sizeof(match));
    while(edmonds()){
        ret++;
    }
    if( ret == N/2 ) return 1;
    return 0;
}

int caso = 1;
void process(){
  
    int bi = 1,bf = 1000000000;

    while( bf - bi > 1 ){
        int med = (bi+bf)/2;
        
        if( ok(med) ) bi = med;
        else          bf = med - 1;
    }
    
    if( ok(bf) ) bi = bf;
    
    printf("Case %d: %d\n",caso++,bi);
}

int main(){
    
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    
    int casos;
    scanf("%d",&casos);
    while(casos--){
        read();
        process();
    }
    return 0;
}

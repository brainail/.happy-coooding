#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>
#include <queue>

using namespace std;

int n;
char text[100100];
char dict[1010][1010];
char found[1010],mark[1010];

struct state{
  map < char , int > mapa;
  vector < int > final;
};

state Trie[100100];
int f[100100];
int idatual;

int read(){
  scanf("%s",text);
  int i;
  scanf("%d",&n);
  for(i=1;i<=n;i++){
    scanf("%s",dict[i]);
  }
  return 1;
}

int add(char *s, int pos,int id, int w ){
  if( s[pos] == 0 ){
    Trie[id].final.push_back(w);
    return 1;
  }
  if( Trie[id].mapa[ s[pos] ] ){
    add(s,pos+1,Trie[id].mapa[ s[pos] ],w );
  }
  else{
    Trie[id].mapa[ s[pos] ] = idatual;
    Trie[idatual].mapa.clear();
    Trie[idatual].final.clear();
    idatual++;
    add(s,pos+1,idatual-1,w);
  }
  return 0;
}

int gera_falha(){
  f[0] = 0;
  map < char , int >::iterator iter;
  queue < int > fila;
  int k;

  for(iter = Trie[0].mapa.begin(); iter != Trie[0].mapa.end(); iter++){
    fila.push( iter->second );
    f[ iter-> second ] = 0;
  }

  while( !fila.empty() ){
    int pai = fila.front();
    fila.pop();
    
    for(iter = Trie[pai].mapa.begin(); iter != Trie[pai].mapa.end(); iter++){
      int no = iter->second;
      k = f[pai];
      while( k>0 && Trie[k].mapa[ iter->first ] == 0 ) k = f[k];
      f[no] = k;
      if( Trie[k].mapa[ iter->first ] ) f[no] = Trie[k].mapa[ iter->first ];
      fila.push(iter->second);
    }
  }

  return 0;
}

int find(){
  int k=0,i,j,v;

  for(i=0;text[i];i++){
    while(k>0 && Trie[k].mapa[ text[i] ] == 0 ) k = f[k];

    if( Trie[k].mapa[ text[i] ] ) k = Trie[k].mapa[ text[i] ];
    j = k;
    while(j>0){
      if( mark[j] ) break;
      mark[j] = 1;
      for(v=0;v<Trie[j].final.size();v++){
	found[Trie[j].final[v]] = 1;
      }
      j = f[j];
    }
  }
  return 0;
}

void process(){
  int i;
  idatual = 1;
  Trie[0].mapa.clear();
  Trie[0].final.clear();

  for(i=1;i<=n;i++){
    add(dict[i],0,0,i);
  }
  gera_falha();
  memset(found,0,sizeof(found));
  memset(mark,0,sizeof(mark));
  find();
  for(i=1;i<=n;i++){
    printf("%c\n",found[i]?'y':'n');
  }
}

int main(){
  int casos;
  scanf("%d",&casos);
  while(casos--){
    read();
    process();
  }
  return 0;
}

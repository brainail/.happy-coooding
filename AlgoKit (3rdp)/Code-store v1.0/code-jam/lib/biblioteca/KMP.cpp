#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char text[10000000],pat[10000000];
int f[10000000];

void gera_falha(){
  int i,k;
  f[0]=-1;
  for(i=1;pat[i];i++){
    k = f[i-1];
    while(k>=0 && pat[i] != pat[k+1] ) k = f[k];
    f[i] = k;
    if( pat[i] == pat[k+1] ) f[i]++;
  }
}

void find(){
  int i,k=-1;
  for(i=0;text[i];i++){
    while(k>=0 && text[i] != pat[k+1] ) k = f[k];
    if(text[i] == pat[k+1]) k++;
    if(pat[k+1] == 0){
      printf("%d\n",i-k);
    }
  }
}

int main(){
  int n;
  int t = 0;
  while( scanf("%d %s %s",&n,pat,text) == 3 ){
    if( t++ ) printf("\n");
    gera_falha();
    find();
  }
  return 0;
}

/* Matching in general graph */

# include <stdio.h>

# define MAX 222
# define QS MAX+1

int MaximumMatching(int n,int c[MAX][MAX],int m[MAX])
{
  int q[QS],r,f;
  int level[MAX],p[MAX],b[MAX];
  int tc[MAX][MAX];
  int i,j,k,l,u,v,w,base,last;
  for(i=0;i<n;i++) m[i]=-1;
  for(w=0;w<n;w++)
    if(m[w]==-1){
      for(i=0;i<n;i++){
	  level[i]=0;
	  b[i]=0;
        p[i]=-1;
      }
      for(i=0;i<n;i++)
        for(j=0;j<n;j++)
          tc[i][j]=c[i][j];
      r=f=0;
      level[w]=1;
      q[r++]=w;
      last=-1;
      while(r!=f){
        u=q[f++];
        if(f==QS) f=0;
        for(v=0;v<n;v++)
          if(tc[u][v] && level[u]==level[v])
            break;
        if(v<n){
          i=p[u];
          j=p[v];
          while(i!=j){
            i=p[i];
            j=p[j];
          }
          base=i;
          while(u!=base){
            for(i=0;i<n;i++)
              if(tc[i][u]){
		tc[i][u]=tc[u][i]=0;
		tc[i][base]=1;
		tc[base][i]=1;
              }
            b[u]=1;
            u=p[u];
          }
          while(v!=base){
            for(i=0;i<n;i++)
              if(tc[i][v]){
		tc[i][v]=tc[v][i]=0;
                tc[i][base]=1;
                tc[base][i]=1;
              }
            b[v]=1;
            v=p[v];
          }
	  b[base]=1;
	  i=f;
	  while(i!=r){
	    if(q[i]==v){
	      q[i]=base;
	      break;
	    }
	    i++;
	    if(i==QS) i=0;
	  }
	  continue;
	}
	if(level[u]%2){
          for(v=0;v<n;v++)
            if(tc[u][v] && level[v]==0){
              level[v]=level[u]+1;
              p[v]=u;
              if(m[v]==-1){
                last=v;
                break;
              }
              q[r++]=v;
              if(r==QS) r=0;
            }
        }
        else{
          v=m[u];
          level[v]=level[u]+1;
          p[v]=u;
          q[r++]=v;
          if(r==QS) r=0;
        }
        if(last!=-1) break;
      }
      l=1;
      while(last!=-1){
        if(!b[last]) v=p[last];
        else{
          if(l%2==0) v=m[last];
          else{
            for(i=0;i<n;i++)
              if(b[i] && c[last][i] && i!=m[last]){
                v=i;
                break;
              }
          }
        }
        if(l%2){
          m[last]=v;
          m[v]=last;
        }
        l++;
        last=v;
      }
    }
  for(k=0,i=0;i<n;i++)
    if(m[i]!=-1) k++;
  return k/2;
}

int main(void)
{
  int n,c[MAX][MAX],m[MAX];
  int i,j;
  scanf("%d",&n);
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      c[i][j]=0;
  while(scanf("%d%d",&i,&j)==2)
    c[i-1][j-1]=c[j-1][i-1]=1;
  printf("%d\n",2*MaximumMatching(n,c,m));
  for(i=0;i<n;i++)
    if(m[i]!=-1){
      printf("%d %d\n",i+1,m[i]+1);
      m[m[i]]=-1;
    }
  return 0;
}

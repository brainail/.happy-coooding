#include<iostream>
#define MAX 100

using namespace std;

int G[MAX][MAX];
int predecessor[MAX];
int V, E;

void floyd()
{
   for(int i=0; i<=V; i++)
      for(int j=0; j<=V; j++)
         if(G[j][i])
            for(int k=1; k<=V; k++)
               if(G[i][k] > 0)
                  if(!G[j][k] || (G[j][i] + G[i][k] < G[j][k])) {
                     G[j][k] = G[j][i] + G[i][k];
                     predecessor[j][k] = predecessor[i][k];
                  }
}

void print_path (int i, int j) {
   if (i!=j)
      print_path(i,p[i][j]);
   cout << j << " ";
}

int main() {
   read();
   return 0;
}


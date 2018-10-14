#include<iostream>
#include<queue>
#define MAX 100

using namespace std;

queue<int> myQueue;
int G[MAX][MAX];
int visit[MAX];
int V, E;


void dfs(int s) {
     int i, j, node;
     memset(visit, 0, sizeof(visit));
     myQueue.push(s);
     
     while(!myQueue.empty())
     {
          node = myQueue.front();
          myQueue.pop();
          if(visit[node]) continue;
          visit[node] = 1;
          cout << node << " ";
          
          for(i=0; i<V; i++)
               if(G[i][node]) myQueue.push(i);
          for(j=0; j<V; j++)
               if(G[node][j]) myQueue.push(j);     
     }
     
}

int main() {
    memset(visit, 0, sizeof(visit));
    dfs(0);
    return 0;
}


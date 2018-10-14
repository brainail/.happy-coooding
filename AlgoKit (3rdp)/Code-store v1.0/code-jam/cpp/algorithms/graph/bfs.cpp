#include<iostream>
#include<stack>
#define MAX 100

using namespace std;

queue<int> myStack;
int G[MAX][MAX];
int visit[MAX];
int V, E;


void bfs(int s) {
     int i, j, node;
     memset(visit, 0, sizeof(visit));
     myStack.push(s);
     
     while(!myStack.empty())
     {
          node = myStack.top();
          myStack.pop();
          if(visit[node]) continue;
          visit[node] = 1;
          cout << node << " ";
          
          for(i=0; i<V; i++)
               if(G[node][i]) myStack.push(i);
     }
     
}

int main() {
    memset(visit, 0, sizeof(visit));
    bfs(0);
    return 0;
}

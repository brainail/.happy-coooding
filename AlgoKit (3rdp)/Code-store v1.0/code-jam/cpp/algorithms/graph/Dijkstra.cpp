#include<queue>
#include<iostream>
#include<math.h>
using namespace std;

#define MAXINT (int)(pow(2,31)-1)
#define MAX 100  


int graph[MAX][MAX];
int total;             
                 

int distances[MAX];          
int father[MAX];     
bool visit[MAX]; 

void dijkstra(int start)
{
  priority_queue<pair<int,int> > queue;
  pair <int,int> nodotmp;
  int i, j;
  
  for (int i=1; i<=total; i++) {
    distances[i] = MAXINT;
    father[i] = -1;
    visit[i] = false;
  }
 
  distances[start] = 0;
  queue.push(pair <int,int> (distances[start], start));
 
  while(!queue.empty()) {
    nodotmp = queue.top();  
    queue.pop();
    i = nodotmp.second;
    if (!visit[i]) {
      visit[i] = true;
      for (j = 1; j<=total; j++)
        if (!visit[j] && graph[i][j] > 0 && distances[i] + graph[i][j] < distances[j]) {
          distances[j] = distances[i] + graph[i][j];
          father[j] = i;
          queue.push(pair <int,int>(-distances[j], j));
        }
    }
  }
}


void getPath(int end) {
  cout << end << " ";
  while (father[end]!= -1) { 
    cout << father[end] << " ";
    end = father[end];
  }
  cout << endl;
}

int main()
{
   int a, b, c;
   int tedges;
   memset(graph, 0, sizeof(graph));
   cin >> total >> tedges;
   for (int i=0; i<tedges; i++) {
     cin >> a >> b >> c;
     graph[a][b] = c;
   }
   for(int i=1; i<=total; i++) {
      for(int j=1; j<=total; j++)
         printf("%d ", graph[i][j]);
      printf("\n");
   }
   dijkstra(1);
   getPath(3);
   
   /*for (int i=1; i<=total; i++) {
     dijkstra(i);
     for(int i=1; i<=total; i++) 
        cout << distances[i] << " ";
     cout << endl;
     for(int i=1; i<=total; i++)
        cout << father[i] << " ";
     cout << endl;
     getPath(5);
   }*/
   return 0;
}

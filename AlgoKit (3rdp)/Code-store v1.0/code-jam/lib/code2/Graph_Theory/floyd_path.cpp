/*
 * Floyd's Algorithm
 *
 * Author: Howard Cheng
 *
 * The following code takes a graph stored in an adjacency matrix "graph",
 * and returns the shortest distance from node i to node j in dist[i][j].
 * We assume that the weights of the edges is not DISCONNECT, and the
 * DISCONNECT constant is used to indicate the absence of an edge.
 *
 * path[i][j] is an array that lists the shortest path going
 * from i to j, except that the first node (i) is missing.  path_len[i][j]
 * indicates the number of edges in this path.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_NODES  26
#define DISCONNECT -1

int graph[MAX_NODES][MAX_NODES];
int dist[MAX_NODES][MAX_NODES];

int path[MAX_NODES][MAX_NODES][MAX_NODES];
int path_len[MAX_NODES][MAX_NODES];

void floyd(void)
{
  int i, j, k;
  int new_path[MAX_NODES][MAX_NODES][MAX_NODES];
  int new_path_len[MAX_NODES][MAX_NODES];
  int l;

  for (i = 0; i < MAX_NODES; i++) {
    for (j = 0; j < MAX_NODES; j++) {
      dist[i][j] = graph[i][j];
      if (dist[i][j] != DISCONNECT) {
        path[i][j][0] = j;
        path_len[i][j] = 1;
      } else {
        path_len[i][j] = 0;
      }
    }
  }

  for (k = 0; k < MAX_NODES; k++) {
    for (i = 0; i < MAX_NODES; i++) {
      for (j = 0; j < MAX_NODES; j++) {
        for (l = 0; l < MAX_NODES; l++) {
          new_path[i][j][l] = path[i][j][l];
        }
        new_path_len[i][j] = path_len[i][j];
      }
    }
    for (i = 0; i < MAX_NODES; i++) {
      for (j = 0; j < MAX_NODES; j++) {
        if (dist[i][k] != DISCONNECT && dist[k][j] != DISCONNECT) {
          int temp = dist[i][k] + dist[k][j];
          if (dist[i][j] == DISCONNECT || dist[i][j] > temp) {
            dist[i][j] = temp;
            for (l = 0; l < new_path_len[i][k]; l++) {
              path[i][j][l] = new_path[i][k][l];
            }
            for (l = 0; l < new_path_len[k][j]; l++) {
              path[i][j][l+new_path_len[i][k]] = new_path[k][j][l];
            }
            path_len[i][j] = new_path_len[i][k] + new_path_len[k][j];
          } else if (dist[i][j] == temp) {
            /* if there is some sort of preferences like */
            /* lexicographic ordering, put it here.      */

          }
        }
      }
    }
  }

  for (i = 0; i < MAX_NODES; i++) {
    dist[i][i] = 0.0;
    path_len[i][i] = 0;
  }
}

int main(void)
{
  int m, n, w;
  int i, j;

  /* clear graph */
  for (i = 0; i < MAX_NODES; i++) {
    for (j = 0; j < MAX_NODES; j++) {
      graph[i][j] = DISCONNECT;
    }
  }

  /* read graph */
  scanf("%d %d %d", &i, &j, &w);
  while (!(i == -1 && j == -1)) {
    assert(0 <= i && i < MAX_NODES && 0 <= j && j < MAX_NODES);
    graph[i][j] = graph[j][i] = w;
    scanf("%d %d %d", &i, &j, &w);
  }

  floyd();

  /* do queries */
  scanf("%d %d", &i, &j);
  while (!(i == -1 && j == -1)) {
    assert(0 <= i && i < MAX_NODES && 0 <= j && j < MAX_NODES);
    printf("%d %d: %d\n", i, j, dist[i][j]);
    printf("%d", i);
    for (m = 0; m < path_len[i][j]; m++) {
      printf(" %d", path[i][j][m]);
    }
    printf("\n");
    scanf("%d %d", &i, &j);
  }

  return 0;
}

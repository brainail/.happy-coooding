/*
 * Dijkstra's Algorithm - heap version
 *
 * Author: Howard Cheng
 * Reference:
 *   Ian Parberry's "Problems on Algorithms", page 102.
 *
 * Given a weight matrix representing a graph and a source vertex, this
 * algorithm computes the shortest distance, as well as path, to each
 * of the other vertices.  The paths are represented by an inverted list,
 * such that if v preceeds immediately before w in a path from the
 * source to vertex w, then the path P[w] is v.  The distances from
 * the source to v is given in D[v] (DISCONNECT if not connected).
 *
 * Call get_path to recover the path.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

/* Note: unlike in adj matrix version, DISCONNECT is large and positive */
/* rather than negative.  This makes it easier to maintain the heap */

#define MAX_NODES 20
#define DISCONNECT INT_MAX

/*
 * This structure is used in the adjacency list.
 *    Edge graph[MAX_NODES][MAX_NODES]
 *    int deg[MAX_NODES]
 * graph[i][] is an array of vertices adjacent to i
 * deg[i] is the (out)degree of vertex i.
 *
 * If G is undirected, add edge ij to both graph[i][] and graph[j][]
 */
typedef struct {
  int v;
  int wgt;
} Edge;

void siftdown(Edge *heap, int *index, int i, int h_size)
{
  int j,k,m;
  Edge te;

  assert( 0 <= i && i < h_size);

  k = i;
  do {
    j=k;
    m=2*j+1;
    if( m < h_size && heap[m].wgt < heap[k].wgt ) {
      k = m;
    }
    m=2*j+2;
    if( m < h_size && heap[m].wgt < heap[k].wgt ) {
      k = m;
    }
    index[heap[j].v] = k;
    index[heap[k].v] = j;
    te = heap[j];
    heap[j] = heap[k];
    heap[k] = te;
  } while( j != k );
}

void percolate( Edge *heap, int *index, int i)
{
  Edge te;
  int j;

  for( j=(i+1)/2 - 1; j>=0 && heap[j].wgt > heap[i].wgt; j = (j+1)/2-1 ) {
    index[heap[j].v] = i;
    index[heap[i].v] = j;
    te = heap[j];
    heap[j] = heap[i];
    heap[i] = te;
    i = j;
  }
}

/* for debugging */
int verify_heap(Edge heap[], int h_size)
{
  int i,j;

  for( i=0; i<h_size; i++ ) {
    j = 2*i+1;
    if( j<h_size && heap[i].wgt > heap[j].wgt ) {
      fprintf(stderr,"Child node %d is smaller than parent %d\n",j,i);
      return 0;
    }
    j= 2*i+2;
    if( j<h_size && heap[i].wgt > heap[j].wgt ) {
      fprintf(stderr,"Child node %d is smaller than parent %d\n",j,i);
      return 0;
    }
  }

  return 1;
}

/* assume that D and P have been allocated */
void dijkstra(Edge graph[MAX_NODES][MAX_NODES], int deg[MAX_NODES],
	      int n, int src, int *D, int *P)
{
  char used[MAX_NODES];
  Edge heap[MAX_NODES]; 
  int index[MAX_NODES]; /* index into heap */
  int h_size;
  int v, w, i, j, k;
  Edge te;
  int t;

  D[src] = 0;

  /* Construct the heap */
  h_size = 0;
  for( v=0; v<n; v++ ) {
    if( v != src ) {
      heap[h_size].v = v;
      heap[h_size].wgt = DISCONNECT;
      index[v] = h_size;
      used[v] = 0;
      h_size++;
      P[v] = -1;
    } else {
      used[v] = 1;
      P[v] = -1;
    }
  }

  if( !h_size ) {
    return;
  }

  for( i=0; i<deg[src]; i++ ) {
    v = graph[src][i].v;
    D[v] = heap[index[v]].wgt = graph[src][i].wgt;
    P[v] = src;
  }
  for( i=h_size/2; i>=0; i-- ) {
    siftdown(heap,index,i,h_size);
  }

  if( !verify_heap(heap,h_size) ) {
    exit(1);
  }

  while( h_size && heap[0].wgt != DISCONNECT ) {
    v = heap[0].v;
    D[v] = heap[0].wgt;
    used[v] = 1;
    /* Remove this vertex from the heap */
    heap[0] = heap[--h_size];
    if( h_size ) {
      siftdown(heap,index,0,h_size);
      if( !verify_heap(heap,h_size) ) {
	exit(1);
      }
    }
    /* Update distances in the heap */
    for( i=0; i<deg[v]; i++ ) {
      w = graph[v][i].v;
      if( w != src && !used[w] ) {
	if( D[v] + graph[v][i].wgt < heap[index[w]].wgt ) {
	  heap[index[w]].wgt = D[v] + graph[v][i].wgt;
	  P[w] = v;
	  percolate(heap,index,index[w]);
	  if( !verify_heap(heap,h_size) ) {
	    exit(1);
	  }
	}
      }
    }
  }


}

int get_path(int v, int *P, int *path)
{
  int A[MAX_NODES];
  int i, k;

  k = 0;
  A[k++] = v;
  while (P[v] != -1) {
    v = P[v];
    A[k++] = v;
  }
  for (i = k-1; i >= 0; i--) {
    path[k-1-i] = A[i];
  }
  return k;
}

int main(void)
{
  int m, n, w, num;
  int i, j;
  Edge graph[MAX_NODES][MAX_NODES];
  int P[MAX_NODES][MAX_NODES], D[MAX_NODES][MAX_NODES];
  int path[MAX_NODES];
  int deg[MAX_NODES];

  /* clear graph */
  for (i = 0; i < MAX_NODES; i++) {
    deg[i] = 0;
  }

  /* read graph */
  scanf("%d %d %d", &i, &j, &w);
  while (!(i == -1 && j == -1)) {
    assert(0 <= i && i < MAX_NODES && 0 <= j && j < MAX_NODES);
    graph[i][deg[i]].v = j;
    graph[j][deg[j]].v = i;
    graph[i][deg[i]].wgt = graph[j][deg[j]].wgt = w;
    deg[i]++;
    deg[j]++;
    scanf("%d %d %d", &i, &j, &w);
  }

  for (i = 0; i < MAX_NODES; i++) {
    dijkstra(graph, deg, MAX_NODES, i, D[i], P[i]);
  }

  /* do queries */
  scanf("%d %d", &i, &j);
  while (!(i == -1 && j == -1)) {
    assert(0 <= i && i < MAX_NODES && 0 <= j && j < MAX_NODES);
    printf("%d %d: %d\n", i, j, D[i][j]);

    for (m = j; m != -1; m = P[i][m]) {
      printf(" %d", m);
    }

    printf("\n");
    num = get_path(j, P[i], path);
    for (m = 0; m < num; m++) {
      printf(" %d", path[m]);
    }
    printf("\n");

    scanf("%d %d", &i, &j);
  }

  return 0;
}

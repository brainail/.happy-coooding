/*
 * Max Flow in a directed graph
 *
 * Author: Matthew McNaughton <mcnaught@cs.ualberta.ca>
 *
 * Usage:
 *
 * The graph is the global head_t g[], which you must allocate, and
 * initialize the elements to 0/NULL. Each graph node has a list of
 * edge_t elements with the neighbour "v", the capacity "cap" along
 * the edge, and "flow", which is the flow along the edge after
 * maxflow() has finished.
 *
 * Add edges to the graph with graph_addedge( g, v, w, c ), meaning
 * there is a directed edge from node v to node w with capacity
 * c. Nodes are numbered by index in g[]. You must make sure that g[]
 * is large enough, it is not resized automatically by maxflow() or
 * support functions, in fact the graph utilities have no idea how
 * large g[] is. Use graph_access(g, v, w) to get the edge_t* for the
 * edge from v to w.
 *
 * maxflow(source, sink, N) computes and returns the maxflow through
 * the graph from node source to node sink. N is the number of nodes
 * in the global g[].  As a side effect maxflow() sets the global S[].
 * S[i] == 1 if node i is on the source side of the min-cut, and S[i]
 * == 0 if node i is on the sink side of the min-cut. Ie. any edge
 * (i,j) with S[i] == 1 and S[j] == 0 is an edge of the min-cut.
 *
 * Date: April 1999-March 2000
 * Added: 9 March 2000
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>

FILE *in, *out;
int s, a, b, source, sink;

typedef struct {
  int v, cap, flow;
} edge_t;

typedef struct {
  int n;
  edge_t *l;
} head_t;

/* g[] is the capacity/flow graph. g[x] is the list of edges leaving x */
/* g[x].l[i] holds the neighbour, the capacity to it, and flow to it, from x */
head_t *g;

/* min-cut list. S[i] != 0 iff i is on the source side of the min-cut. */
int *S;


int min(int a, int b) { return a < b ? a : b; }

void
graph_free(head_t *g, int n) {
  int i;

  for( i = 0; i < n; i++ ) {
    free(g[i].l);
  }
  free(g);
}

edge_t *
graph_access(head_t *g, int v, int w) {
  int i;

  for( i = 0; i < g[v].n; i++ ) {
    if( g[v].l[i].v == w ) return &g[v].l[i];
    /*    if( g[v].l[i].v > w ) return NULL; */
  }
  return NULL;
}

/* add 0-capacity edge from v to w for neighbour information bfs in maxflow */
void
graph_add_dummy(head_t *g, int v, int w) {
  edge_t *p; int j;

  for( j = 0; j < g[v].n; j++ ) {
    
    /* already have an edge */
    if( g[v].l[j].v == w ) return;
  }

  g[v].l = realloc(g[v].l, (g[v].n+1)*sizeof(g[v].l[0]));
  p = &g[v].l[ g[v].n ];
  
  p->v = w;
  p->cap = 0;
  p->flow = 0;
  g[v].n++;

  return;
}

edge_t *
graph_addedge(head_t *g, int v, int w, int cap) {
  edge_t *p; int j;

  for( j = 0; j < g[v].n; j++ ) {
    if( g[v].l[j].v == w ) {
      g[v].l[j].cap += cap;
      /* edge in other direction has already been added. */
      return & g[v].l[j];
    }
  }


  g[v].l = realloc(g[v].l, (g[v].n+1)*sizeof(g[v].l[0]));
  p = &g[v].l[ g[v].n ];

  p->v = w;
  p->cap = cap;
  p->flow = 0;
  g[v].n++;

  graph_add_dummy(g, w, v);
  return p;
}


/* See usage at top of file */
int
maxflow( int source, int sink, int N ) {
  int flow, i, j, head, tail, v,w, inc;
  int *queue, *pred, *maxcap;
  edge_t *p, *e, *e1, *e2;

  queue = malloc((N+1)* sizeof(queue[0]));
  pred  = malloc(N * sizeof(pred[0]));
  maxcap= malloc(N * sizeof(maxcap[0]));
  if( S ) free(S);
  S     = malloc(N * sizeof(S[0]));

  /* initialize flows to 0 */
  for( i = 0; i < N; i++ ) 
    for( j = 0; j < g[i].n; j++ )
      g[i].l[j].flow = 0;

  flow = 0;

  while(1) {

    head = tail = 0;
    for( i = 0; i < N; i++ ) S[i] = 0;
    queue[tail++] = source; S[source] = 1;

    while(head != tail) {
      v = queue[head++];
      if(v ==sink ) break;

      /* for each neighbour */
      for( j = 0; j < g[v].n; j ++ ) {
	p = &g[v].l[j];

	i = p->v;
	if(S[i]) continue;

	e = p;

	if( e->cap && e->flow < e->cap ) {

	  S[i] = 1;
	  queue[tail++] = i; pred[i] = v;
	  maxcap[i] = e->cap - e->flow;
	}
	else {

	  /* need to look at edge going the other way. */
	  e = graph_access(g,i,v);

	  /* it may not exist */
	  if( e && e->cap && e->flow > 0 ) {
	    maxcap[i] = e->flow;
	    S[i] = 1;
	    queue[tail++] = i; pred[i] = v;
	  }
	}
      }
    } /* bfs: while( head != tail) */

    if( v != sink) {
      break; /* return */

    } else {
      inc = INT_MAX;
      v = sink;
      while( v != source ) {
	inc = min(inc, maxcap[v] );
	v = pred[v];
      }

      flow += inc;

      v = sink;
      while(v != source) {
	w = pred[v];

	e1 = graph_access(g, w, v);
	e2 = graph_access(g, v, w);

	if( e1 && e1->cap ) {
	  e1->flow += inc;
	}
	else if( e2 && e2->cap ) {
	  e2->flow -= inc;
	}
	else assert(0);

	if( e1 && e2 && e1->flow && e2->flow ) {
	  if( e1->flow > e2->flow ) {
	    e1->flow -= e2->flow;
	    e2->flow = 0;
	  }
	  else {
	    e2->flow -= e1->flow;
	    e1->flow = 0;
	  }
	}

	v = w;
      }
    }
  }
  free(queue); free(pred); free(maxcap);
  return flow;
}

int
main() {
  int n, i, j, v, w, c, source, sink, flow;
  edge_t *e;

  fscanf(stdin, "%d %d %d", &n, &source, &sink) ;

  g = malloc( n * sizeof(g[0]));

  for( i = 0; i < n; i++ ) {
    g[i].n = 0; g[i].l = NULL;
  }

  while(fscanf(stdin, "%d %d %d", &v, &w, &c ) == 3 ) {
    assert(v < n);
    assert(w < n);
    assert(c >= 0 );
    graph_addedge(g, v, w, c);
  }

  flow = maxflow(source, sink, n);

  fprintf(stdout, "Maxflow: %d\nMin-cut edges:\n", flow);

  for( i = 0; i < n; i++ ) {
    if( S[i] == 1 ) {

      for( j = 0; j < g[i].n; j++ ) {
	if( S[ g[i].l[j].v ] == 0 ) {
	  fprintf(stdout, " (%d -> %d)\n", i, g[i].l[j].v );
	}
      }

    }
  }

  fprintf(stdout, "Flow values:\n");
  
  for( i = 0; i < n; i++ ) {
    for( j = 0; j < n; j++ ) {
      if( (e = graph_access(g, i, j)) && e->flow ) {
	fprintf(stdout, " (%d -> %d) : %d\n",
		i, j, e->flow);
      }
    }
  }
  return 0;
}


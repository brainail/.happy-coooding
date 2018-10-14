/*
 * Biconnected Components
 * 
 * by Adam Beacham
 *
 * References:  
 *  Baase, pp. 184-191
 *  West, p. 140
 *  + Adam's own peculiar sense of coding
 *
 * WARNING: Buggy (2 Mar 2000, Adam)
 * WARNING: In incoming
 */ 

#include <stdio.h>
#include <assert.h>

#define MAX_VERT 30

int back[MAX_VERT];
int dfsNum[MAX_VERT];
int dfn;
int stackBase[MAX_VERT+1];
int *stack;     /* points at the stack */

/* This is an adjacency LIST */
/* adjList[i] is a list of the vertices adjacent to i.  End the */
/* list with -1 */
int adjList[MAX_VERT][MAX_VERT];

int min(int x, int y)
{
  return x<y ? x : y;
}

/*
 * ProcessNewComponent
 *
 * Component consists of all elements on stack until it reaches
 * the specified point.
 *
 * This procedure can be modified as needed.
 */
void ProcessNewComponent(int *stackBottom)
{
  static int compNum = 0;

  printf("Component #%d:\n",++compNum);

  do {
    printf("%d ",*--stack);
  } while( stack != stackBottom );
  printf("\n");  
}

void DFSConnect(int root, int v)
{
  int *w;
  int *p;

  dfn++;
  back[v] = dfsNum[v] = dfn;
  *stack++ = v;

  for( w=adjList[v]; *w != -1; w++ ) {
    if( dfsNum[*w] ) {
      /* w already visited */
      back[v] = min(back[v],dfsNum[*w]);
    } else {
      p = stack;
      DFSConnect(root,*w);

      if( back[*w] >= dfsNum[v] ) {
	*stack++ = v;
	ProcessNewComponent(p);
      } else {
	back[v] = min(back[v],back[*w]);
      }
    }
  }

  /* This is a bit of a hack; does it show? :-) */
  if( v==root ) {
    if( adjList[v][0] == -1 ) {
      ProcessNewComponent(stackBase);
    } else {
      stack--;
    }
  }
}

/*
 * Global Vars:
 *  dfsNum[]
 *  stackBase
 *  stack
 *  dfn
 *
 * Calls: ProcessNewComponent, DFSConnect
 *
 */
void Biconnect(int numVert)
{
  int v;

  /* Initialization */
  for( v=0; v<numVert; v++ ) {
    dfsNum[v] = 0;
  }
  dfn = 0;
  stack = stackBase;

  for( v=0; v<numVert; v++ ) {
    if( !dfsNum[v] ) {
      DFSConnect(v,v);
      
      if( stack != stackBase ) {
	fprintf(stderr,"Problem with stack.\n");
	fprintf(stderr,"stack = %lu, stackBase = %lu\n",
		stack,stackBase);
	exit(1);
      }
    }
  }
}

int main(void)
{
  int n,m;
  int v,w, i;
  int deg;
  int d[MAX_VERT];

  /*
   * Format of input:
   * First line:  integer n, indicating # of verts
   * The next n lines of the format:
   *  degree of vertex, list of vertices
   *
   */
  /*
  scanf("%d",&n);
  
  for( v=0; v<n; v++ ) {
    scanf("%d",&deg);
    for( w=0; w<deg; w++ ) {
      scanf("%d",&adjList[v][w]);
    }
    adjList[v][w] = -1;
  }
  */

  /*
   * Input format #2
   *
   * First line: n, n = #vert
   * Remaining lines are edges in the form 
   *   v1 v2
   *
   * Vertices are numbered from 0.
   */

  scanf("%d",&n);

  for( v=0; v<n; v++ ) {
    d[v] = 0;
  }

  while( scanf("%d %d",&v,&w) == 2 ) {
    adjList[v][d[v]++] = w;
    adjList[w][d[w]++] = v;
  }

  for( v=0; v<n; v++ ) {
    adjList[v][d[v]] = -1;
  }

  Biconnect(n);

  return 0;
}

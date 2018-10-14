/*
 * Topological sort of a directed graph
 *
 * Author: Paul Shelley
 * Reference: Algorithms in C (Robert Sedgewick)
 *
 * This routine takes a directed graph represented by an
 * adjacency list, and produces a list of the nodes
 * in topologically sorted order. Node B is in Node A's
 * adjacency list if there is an edge from A to B.
 *
 * The sample program in main() reads in the number of
 * vertices, and then reads in pairs of integers (x,y),
 * which represent directed edges from x to y. The nodes
 * are represented by the integers 0 ... numNodes - 1.
 * It then performs a topological sort, printing out the
 * resulting list, which is stored in the global array
 * "topo".
 *
 * NOTE: This is a very simple routine, and might be
 *       easier to code in your own style. The idea is
 *       to build the list backwards by doing a dfs, 
 *       adding a node to the list when all its descendants
 *       in the graph have been visited.
 *
 * Added: 12 March 2000
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000

typedef struct
{
    int numAdj;
    int* adj;
}Node;

int numNodes;              /* total number of nodes */
Node allNodes[MAX_NODES];  /* adjacency lists */
int val[MAX_NODES];        /* used to see if a node has been visited */
int topo[MAX_NODES];       /* stores the topologically sorted list */
int topoIndex;             /* index into results list */
int id = 0;                /* global nodes visited counter */

void topo_dfs( int k )
{
    int next;

    /* mark this node as having been visited */
    val[k] = ++id;

    /* look at all nodes adjecent to the current node */
    for ( next = 0; next < allNodes[k].numAdj; next++ )
    {
	if ( !val[allNodes[k].adj[next]] )
	{
	    /* recurse if the node has not been visited before */
	    topo_dfs( allNodes[k].adj[next] );
	}
    }

    /* the current node is adjacent to no more unvisited nodes, so put
       it in the list, in the unused position closest to the end */
    topo[topoIndex--] = k;
}

int main()
{
    int n1, n2, i;
    int* tptr;

    /* read in the number of nodes */
    scanf( "%d", &numNodes );
    
    /* initialize */
    for ( i = 0; i < numNodes; i++ )
    {
	allNodes[i].numAdj = 0;
	allNodes[i].adj = NULL;
	val[i] = 0;
    }

    /* read in the edges in the dag */
    while( scanf( "%d%d", &n1, &n2 ) == 2 )
    {
	tptr = realloc( allNodes[n1].adj, 
			allNodes[n1].numAdj * sizeof( int ) );
	if ( !tptr )
	{
	    fprintf( stderr, "Out of memory, exiting.\n" );
	    exit( 1 );
	}
	allNodes[n1].adj = tptr;
	allNodes[n1].adj[allNodes[n1].numAdj++] = n2;
    }

    /* MUST INITIALIZE topoIndex to the end of the topo array */
    topoIndex = numNodes - 1;

    /* call the dfs procedure on each connected component */
    for ( i = 0; i < numNodes; i++ )
    {
	if ( !val[i] )
	{
	    topo_dfs( i );
	}
    }

    /* print out the results */
    for ( i = 0; i < numNodes; i++ )
    {
	printf( "%d ", topo[i] );
    }    
    printf( "\n" );

    return 0;
}









/**
 *   ///////////////////////////////////
 *   // STRONGLY CONNECTED COMPONENTS //
 *   ///////////////////////////////////
 *
 * This file is part of my library of algorithms found here:
 *      http://www.palmcommander.com:8081/tools/
 * LICENSE:
 *      http://www.palmcommander.com:8081/tools/LICENSE.html
 * Copyright (c) 2008
 * Contact author:
 *      igor at cs.ubc.ca
 **/

/*********************************
 * Strongly Connected Components * (Tarjan's linear-time)
 *********************************
 * Takes a directed graph and produces a Union-Find array.
 *
 * PARAMETERS:
 *      - deg (global): vertex degrees
 *      - adj (global): adjacency list
 *      - n: the number of vertices ([0, n-1] are considered as vertices).
 * RETURNS:
 *      - uf (global): FIND(u) == FIND(v) iff u and v are in the same component.
 * FIELD TESTING:
 *      - Valladolid 11324: Largest Clique
 **/

#define NN 1024

// Inputs (populate these).
int deg[NN];
int adj[NN][NN];

// Union-Find.
int uf[NN];
int FIND( int x ) { return uf[x] == x ? x : uf[x] = FIND( uf[x] ); }
void UNION( int x, int y ) { uf[FIND( x )] = FIND( y ); }

// dfsn[u] is the DFS number of vertex u.
int dfsn[NN], dfsnext;

// mindfsn[u] is the smallest DFS number reachable from u.
int mindfsn[NN];

// The O(1)-membership stack containing the vertices of the current component.
int comp[NN], ncomp;
bool incomp[NN];

void dfs( int n, int u )
{
  dfsn[u] = mindfsn[u] = dfsnext++;
  incomp[comp[ncomp++] = u] = true;
  for( int i = 0, v; v = adj[u][i], i < deg[u]; i++ )
  {
    if( !dfsn[v] ) dfs( n, v );
    if( incomp[v] ) mindfsn[u] <?= mindfsn[v];
  }
  
  if( dfsn[u] == mindfsn[u] )
  {
    // u is the root of a connected component. Unify and forget it.
    do
    {
      UNION( u, comp[--ncomp] );
      incomp[comp[ncomp]] = false;
    } while( comp[ncomp] != u );
  }
}

void scc( int n )
{
  // Init union-find and DFS numbers.
  for( int i = 0; i < n; i++ ) dfsn[uf[i] = i] = ncomp = incomp[i] = 0;
  dfsnext = 1;

  for( int i = 0; i < n; i++ ) if( !dfsn[i] ) dfs( n, i );
}

//----------------- EXAMPLE USAGE -----------------
int main()
{
    // Make a graph.
    int n = 100;
    for( int i = 0; i < n; i++ )
    {
      deg[i] = 0;
      for( int j = 0; j < 10; j++ ) adj[u][deg[u]++] = ( i * j * 13 + 9 ) % 100;
    }

    scc( n );

    for( int i = 0; i < 100; i++ ) if( FIND( i ) == i )
      printf( "Component root: %d\n", i );
       
    return 0;
}

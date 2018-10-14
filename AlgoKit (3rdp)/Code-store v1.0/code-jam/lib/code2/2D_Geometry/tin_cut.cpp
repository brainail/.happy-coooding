/*
 * Generic "tin cutting" algorithm
 *
 * Author: Matthew McNaughton, January 17, 1999. <mcnaught@cs.ualberta.ca>
 *
 *
 * Given a set of line segments on the plane, find the number and
 * sizes of the distinct measurable "holes" these segments form.
 *
 * a hole inside a hole is one hole. a figure-eight is two holes.
 *
 *  ,-----,                __
 *  |  _  |               |  |
 *  | | | |               |__|__
 *  | |_| |                  |  |
 *  |     |    1 hole        |__|   2 holes.
 *  `-----'
 *
 *
 * The coordinates of the segments can be arbitrarily large, but
 * there shouldn't be more than a few thousand distinct x-values
 * and y-values.
 * 
 * Returns a count of holes and the sizes of each.
 *
 * Technique:
 * Scale the x-values and y-values independent of each other so that
 * a grid of the smallest rectangle containing all provided segments
 * can be made, and the segments are drawn in.
 * Repeatedly flood-fill empty areas until there are none left.
 *
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define a(a,b) (array[((a)*(2*ny+1)+(b))])
#define isHorz(a) ((a).p1.y == (a).p2.y)
#define isVert(a) ((a).p1.x == (a).p2.x)
#define swap(a,b,t) ( (t) = (a), (a) = (b), (b) = (t) )

#define debug 0
void dump_array(char array[], int nx, int ny) {
  int i,j; char c;

  for( i = 0; i < 2*nx+1; i++ ) {
    for( j = 0;j < 2*ny+1; j++ ) {
      c = a(i,j);
      switch(c) {
      case '*':
	fputc(c,out); break;
      case 0:
	fputc('.',out); break;
      case 1:
	fputc('+', out); break;
      default:
	assert(0);
      }
    }
    fputc('\n', out);
  }
  fputc('\n', out);
}

typedef struct {
  int x,y;
} Coor_t;

typedef struct {
  Coor_t p1, p2;
} Seg_t;

int int_cmp(const void *a, const void *b) {
  int *ap = (int *)a;
  int *bp = (int *)b;
  if( *ap < *bp ) return -1;
  if( *ap > *bp ) return 1;
  return 0;
}

/* Input:
 * array of Seg_t structures in segs, and count in nsegs. 
 *
 * Output:
 * pholesizes and pnholes, provided by caller, must be valid pointers.
 * Sets *pholesizes to array of int with sizes of holes in no particular
 * order, and *pnholes to the count of holes. it is caller's responsibility
 * to free *pholesizes.
 */

void find_holes(Seg_t segs[], int nsegs, int **pholesizes, int *pnholes) {
  int *xorder, *yorder, found;
  int nx, ny, i,j,k, y1, y2, x1, x2, t, x, y, *queue, head, tail, qlen;
  char *array;
  int hole_total;

  xorder = malloc(2*nsegs*sizeof(xorder[0])); assert(xorder);
  yorder = malloc(2*nsegs*sizeof(yorder[0])); assert(yorder);

  for( i = 0, j = 0, k = 0; i < nsegs; i++ ) {
    xorder[j++] = segs[i].p1.x;
    xorder[j++] = segs[i].p2.x;
    yorder[k++] = segs[i].p1.y;
    yorder[k++] = segs[i].p2.y;
  }

  qsort(xorder, j, sizeof(*xorder), int_cmp);
  qsort(yorder, k, sizeof(*yorder), int_cmp);

  /* uniqify the arrays xorder and yorder. */
  for( i = 1, j = 0; i < nsegs*2; /* nil */ )
    if( xorder[i] != xorder[j] ) xorder[++j] = xorder[i++]; else i++;

  nx = j + 1;

  for( i = 1, j = 0; i < nsegs*2; /* nil */ )
    if( yorder[i] != yorder[j] ) yorder[++j] = yorder[i++]; else i++;

  ny = j + 1;

  /* now allocate our happy array. */
  array = calloc( (2*nx+1) * (2*ny+1) , sizeof(*array) );
  
  for( i = 0; i < nsegs; i++ ) {
    if( isVert(segs[i])) {
      x = y1 = y2 = -1;
      for( j = 0; j < ny; j++ ) {
	if( segs[i].p1.y == yorder[j] ) y1 = j;
	if( segs[i].p2.y == yorder[j] ) y2 = j;
      }
      for( j = 0; j < nx; j++ ) if( segs[i].p1.x == xorder[j] ) x  = j;
      /* assert(y1 != -1 && y2 != -1 && x != -1);*/
      if( y1 > y2 ) swap(y1,y2,t);
      
      x = x*2 + 1;
      for( j = 2*y1+1; j <= 2*y2+1; j ++ ) {
	a(x,j) = '*';
      }
      
    } else if( isHorz(segs[i])) {
      y = x1 = x2 = -1;
      for( j = 0; j < nx; j++ ) {
	if( segs[i].p1.x == xorder[j] ) x1 = j;
	if( segs[i].p2.x == xorder[j] ) x2 = j;
      }
      for( j = 0; j < ny; j++ ) if( segs[i].p1.y == yorder[j] ) y  = j;
      /* assert(x1 != -1 && x2 != -1 && y != -1); */
      if( x1 > x2 ) swap(x1,x2,t);
      y = y * 2 + 1;
      for( j = 2*x1+1; j <= 2*x2+1; j ++ ) {
	a(j,y) = '*';
      }
    } else {
      assert(0); /* must be either horizontal or vertical. */
    }
  }
  if( debug ) dump_array(array, nx, ny);

  /* now the array is filled in with the segment boundaries */
  /* flood fill from the outside. */
  
  /* well, first set up the bfs queue. */

  /* this should be quite big enough. I claim that 2 * ... would
   * be enough. */
  /* the entries of the queue are encoded as:
   * x<<16 | y */
  qlen = 4 * ( (2*nx+1) + (2*ny+1));
  queue = malloc(qlen*sizeof(queue[0])); assert(queue);

  head = tail = 0;
  queue[tail++] = 0;
  a(0,0) = 1; /* visited is marked 1. */

  while( head != tail ) {
    x = queue[head]; 
    head = (head + 1) % qlen;
    y = x & 0xffff; x >>= 16;

    for( t = 0; t < 4; t++ ) {
      switch(t) {
      case 0: i = x-1; j = y  ; break;
      case 1: i = x  ; j = y-1; break;
      case 2: i = x+1; j = y  ; break;
      case 3: i = x  ; j = y+1; break;
      default:
      }

      if( i >= 0 && i <= 2*nx && j >= 0 && j <= 2*ny && !a(i,j) ) {
	queue[tail] = i << 16 | j;
	tail = (tail + 1) % qlen;
	a(i,j) = 1;
      }
    }
  }

  if(debug) dump_array(array, nx, ny);

  /* now the array has been flooded from the outside. condense
   * adjacent holes by dissolving the boundaries between them. */

  /* the bounds of these for loops are shrunk by one because
   * by construction the entire array has boundaries 1 now,
   * so we don't need to check them. */
  for( i = 1; i < 2*nx; i++ ) {
    for( j = 1; j < 2*ny; j++ ) {
      if( a(i,j) == '*' &&
	((a(i-1,j) == 0 && a(i+1,j) == 0) || (a(i,j-1) == 0 && a(i,j+1) == 0)))
	a(i,j) = 0;
    }
  }
  if(debug) dump_array(array, nx, ny);

  /* now while there is a still an element of the array with coordinates
   * of form (2k,2m) set to zero, flood fill and measure the area. */
  *pholesizes = NULL; *pnholes = 0;
  do {
    found = 0;
    for( i = 2; i <= 2*nx; i += 2 ) {
      for( j = 2; j <= 2*ny; j += 2 ) {
	if( ! a(i,j) ) { found = 1; goto zero_found; }
      }
    }
    /* ! found */ break;
    
  zero_found:
    hole_total = head = tail = 0;
    queue[tail++] = i << 16 | j;
    a(i,j) = 1; /* visited is marked 1. */
    
    while( head != tail ) {
      x = queue[head]; 
      head = (head + 1) % qlen;
      y = x & 0xffff; x >>= 16;
      if( !(x&1) && !(y&1) ) {
	/* an even-coordinate square. that means, measure it. */
	hole_total += 
	  (xorder[x/2] - xorder[(x/2)-1]) * (yorder[y/2] - yorder[(y/2)-1]);
      }
      /* and enqueue its neigbours. */
      for( t = 0; t < 4; t++ ) {
	switch(t) {
	case 0: i = x-1; j = y  ; break;
	case 1: i = x  ; j = y-1; break;
	case 2: i = x+1; j = y  ; break;
	case 3: i = x  ; j = y+1; break;
	default:
	}
	if( i >= 0 && i <= 2*nx && j >= 0 && j <= 2*ny && !a(i,j) ) {
	  queue[tail] = i << 16 | j;
	  tail = (tail + 1) % qlen;
	  a(i,j) = 1;
	}
      }
    } /* end loop bfs flood filling this hole */
    
    if( *pholesizes == NULL ) {
      *pholesizes = malloc((*pnholes + 1) * sizeof((*pholesizes)[0]));
      assert(*pholesizes);
    } else {
      *pholesizes = realloc( *pholesizes, 
			     (*pnholes + 1) * sizeof((*pholesizes)[0]));
      assert(*pholesizes);
    }
    (*pholesizes)[(*pnholes)++] = hole_total;
  } while(1); /* broken when zero elements are exhausted. */
  free(queue); free(array); free(xorder); free(yorder);
}

int main() {
  int i,x1,y1,x2,y2,nsegs, *holes, nholes;
  Seg_t *segs;

  segs = NULL; nsegs = 0;

  while(scanf("%d %d %d %d", &x1, &y1, &x2, &y2) == 4 ){
    segs = segs 
      ? realloc(segs, ++nsegs * sizeof(segs[0])) 
      : malloc(++nsegs * sizeof(segs[0]));
    
    segs[nsegs-1].p1.x = x1; segs[nsegs-1].p1.y = y1;
    segs[nsegs-1].p2.x = x2; segs[nsegs-1].p2.y = y2;
  }

  find_holes(segs, nsegs, &holes, &nholes);
  printf("There are %d holes.\n", nholes);

  for( i = 0; i < nholes; i++ )
    printf("Hole of size %d\n", holes[i]);
  return 0;
}

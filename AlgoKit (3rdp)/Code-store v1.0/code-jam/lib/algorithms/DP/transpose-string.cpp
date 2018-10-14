#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

typedef enum { Insert = 1, Delete, Replace, Match, Transpose } move_t;

typedef struct {
  move_t move;
  int x,y;
} action_t;

char a[512], b[512];
int m, n;

int dist[512][512];
action_t action[512][512];

int min(int a, int b) { return a > b ? b : a; }
int min3(int a, int b, int c) { return min(a, min(b,c)); }
int min4(int a, int b, int c, int d) { return min(a, min(b, min(c,d))); }

/* returns the smallest number of moves required to transform
   the substring of _a_ starting at _i_ into the substring of _b_
   starting at index _j_ */

int
string_distance(int i, int j) {
  int insert_cost, delete_cost, replace_cost, 
      match_cost, transpose_cost, mincost;

  if( i == m && j == n) {
    action[i][j].move = Match;
    action[i][j].x = i; action[i][j].x = j;
    dist[i][j] = 0;
    return 0;
  } else if( i == m ) {

    /* we are at the end of the source string - we must insert */
    dist[i][j] = string_distance(i,j+1) + 1;
    action[i][j].move = Insert;
    action[i][j].x = i; action[i][j].y = j+1;
    return dist[i][j];

  } else if( j == n ) {

    /* we are at the end of the destination string - we must delete */
    dist[i][j] = string_distance(i+1,j) + 1;
    action[i][j].move = Delete;
    action[i][j].x = i+1; action[i][j].y = j;
    return dist[i][j];

  }

  /* if we already know the cost... */
  if(dist[i][j] != INT_MAX) return dist[i][j];

  insert_cost = string_distance(i,j+1) + 1;
  delete_cost = string_distance(i+1,j) + 1;
  replace_cost= string_distance(i+1,j+1) + 1;
  match_cost = a[i] == b[j] ? string_distance(i+1,j+1) : INT_MAX;
  transpose_cost = (i+1 < m && j+1 < n) && (a[i+1] == b[j] && a[i] == b[j+1])
                    ? string_distance(i+2,j+2) + 1: INT_MAX;

  mincost = min( insert_cost, 
                 min(delete_cost, 
                     min(replace_cost, 
                         min(match_cost, transpose_cost))));

  if( match_cost == mincost ) {

    action[i][j].move = Match;
    action[i][j].x = i+1; action[i][j].y = j+1;

  } else if( replace_cost == mincost ) {

    action[i][j].move = Replace;
    action[i][j].x = i+1; action[i][j].y = j+1;

  } else if( delete_cost == mincost ) {

    action[i][j].move = Delete;
    action[i][j].x = i+1; action[i][j].y = j;

  } else if( transpose_cost == mincost ) {

    action[i][j].move = Transpose;
    action[i][j].x = i+2; action[i][j].y = j+2;
  } else {

    action[i][j].move = Insert;
    action[i][j].x = i; action[i][j].y = j+1;

  }

  dist[i][j] = mincost;

  return dist[i][j];
}


int
main () {
  int i,j,offset,p,q;

  while( fgets(a,512,stdin) != NULL ) {
    fgets(b, 512, stdin);

    /* note that we are saying the string is one character longer than
       it really is. This makes it all work out nicely. The null
       is special character that everything past it matches for free*/

    m = strlen(a);
    n = strlen(b);
    a[m-1] = '\0'; m--;
    b[n-1] = '\0'; n--;

    for( i = 0; i < m; i++ ) {
      for( j = 0; j < n; j++ ) {
        dist[i][j] = INT_MAX;
      }
    }

    printf("distance is %d.\n", string_distance(0,0));

    i = 0; j = 0;
    offset = 0;
    do {
      switch(action[i][j].move) {
      case Insert:
	printf("Insert %c before position %d\n", b[j], i+offset);
	offset++;
	break;
      case Delete:
	printf("Delete %c at position %d\n", a[i], i+offset);
	offset--;
	break;
      case Replace:
	printf("Replace %c at position %d with %c\n", a[i], i+offset, b[j]);
	break;
      case Match:
	printf("Match %c at position %d\n", a[i], i+ offset);
	break;
      case Transpose:
    printf("Tranpose %c%c at position %d\n", a[i], a[i+1], i+offset);
    break;
      default:
	assert(!fprintf(stderr, "whoa there.\n"));
      }
      p = i; q = j; /* watch out for simultaneous assignment! duh! */
      i = action[p][q].x; j = action[p][q].y;
    } while( i != m || j != n);


  }
  return 0;
}

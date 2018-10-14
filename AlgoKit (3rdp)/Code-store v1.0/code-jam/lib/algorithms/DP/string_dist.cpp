/*
 * Edit distance between two strings 
 *
 * Author: Scott Crosswhite
 * Source: Text Algorithms, p238-240
 *         (Maxime Crochemore & Wojciech Rytter)
 *         QA 76.9 T48 C76 1994 c.1
 *
 * The edit distance between two strings is determined based on 
 * three possible actions:
 *    1) Change: changes one symbol in a string to match
 *          a symbol in another string.
 *    2) Insert: inserts a symbol into a string at a position
 *          corresponding to the same symbol in the other string.
 *    3) Delete: deletes a symbol from one string that doesn't 
 *          appear in the other string.
 *
 * There is a simple (very simple) example for path recovery.  Should
 * you wish to implement your own, the parts of this code pertaining to
 * path recovery are centralized in the procedure path_recovery(). 
 *
 * This algorithm uses dynamic programming and is O(nm).  In theory, 
 * ie. not in this implementation, it is not necessary to store the 
 * entire table, only two columns need to be stored at any given step
 * if all that is desired is to compute the edit distance.  In this
 * case, it takes O(m) space.  NOTE: If this is done, path recovery
 * is NOT possible.
 *
 * If you don't like this algorithm, another possiblity is to use
 * Dijkstra's algorithm for shortest paths in the grid graph.
 *
 * Two possible edit distance configurations are coded below, and
 * the vast multitude remaining are left as an exercise for the 
 * reader.
 *
 * - int edit_general(char *A, char *B, int change, int insert, int delete);
 *     Specify the strings and assign weights for changing, inserting,
 *     and deleting.
 *
 * - int edit_equal(char *A, char *B);
 *     Specify the strings.  Changing, inserting, and deleting all
 *     carry unit weight.
 *
 * - int edit_no_change(char *A, char *B);
 *     Specify the strings.  Changing is not allowed.  To represent
 *     this to the algorithm, the weight of changing is set to greater
 *     than the sum of insert and delete--in this case, three.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INSERT 1
#define DELETE 2
#define CHANGE 3

typedef struct {
  /* Empty struct to hold a sample to return, if desired. */
  /* Note that you have to code your own Return, so that the
     format will be correct */

  int *mods; /* Stores the modifications made, in reverse order */
  int len; /* Stores the number of modifications. */
} ReturnType;


int is_insert (int **EDIT, int i, int j, int insert) {
  if (j && (EDIT[i][j] == EDIT[i][j-1] + insert)) return 1;
  return 0;
}


int is_delete (int **EDIT, int i, int j, int delete) {
  if (i && (EDIT[i][j] == EDIT[i-1][j] + delete)) return 1;
  return 0;
}


int is_change (int **EDIT, int i, int j, char *A, char *B, int change) {
  if (i && j && (A[i-1] != B[j-1]) && (EDIT[i][j] == EDIT[i-1][j-1] +change)) {
    return 1;
  }
  return 0;
}


int is_nochange (int **EDIT, int i, int j, char *A, char *B) {
  if (i && j && (A[i-1] == B[j-1]) && (EDIT[i][j] == EDIT[i-1][j-1])) return 1;
  return 0;
}


void path_recovery(int **EDIT, char *A, char *B, int change, int insert,
		   int delete, ReturnType *aSample) {
  int i, j, k;

  /*
   * At this point, you have a number for changes required to
   * change from one string to the other.  If you want a sample
   * returned, this is where you would specify the format.
   *
   * In order to retrieve the path, start at EDIT[strlen(a)][strlen(b)]
   * and travel back up the graph to the start--EDIT[0][0].
   *
   * To determine which position in the string the change (whatever)
   * is taking place is messy.  Have fun. :-)
   */

  i = strlen(A);
  j = strlen(B);

  /* Fix up your storage space, if necessary */
  aSample->mods = (int *) malloc (EDIT[i][j] * sizeof(int));
  assert(aSample->mods);
  aSample->len = EDIT[i][j];
  k = EDIT[i][j] - 1; /* We'll use this to index into the
		       * storage space we have.  Starts from
		       * the end and works back.
		       */

  while (i || j || k>-1) {
    if (is_insert(EDIT, i, j, insert)) {
      /* Character B[j-1] was inserted */
      aSample->mods[k] = INSERT; k--;

      j--;
    } else if (is_delete(EDIT, i, j, delete)) {
      /* Character A[i-1] was deleted */
      aSample->mods[k] = DELETE; k--;

      i--;
    } else if (is_change(EDIT, i, j, A, B, change)) {
      /* Character A[i-1] was replaced by B[j-1] */
      aSample->mods[k] = CHANGE; k--;

      i--; j--;
    } else if (is_nochange(EDIT, i, j, A, B)) {
      /* Nothing happened */

      i--; j--;
    }
  }
}


int edit_general(char *A, char *B,
                 int change, int insert, int delete, ReturnType *aSample) {
  int len_a, len_b;    /* Lengths of strings A & B */
  int** EDIT;          /* Array to hold path information */
  int i, j;
  int cha, ins, del;
  int number_of_changes;

  len_a = strlen(A);
  len_b = strlen(B); 

  EDIT = (int **) malloc ((len_a+1) * sizeof(int *));
  assert(EDIT);

  for (i=0; i<= len_a; i++) {
    EDIT[i] = (int *) malloc ((len_b+1) * sizeof(int));
    assert(EDIT[i]);
  }

  /* More details that already provided...
   *
   * The goal of this exercise is essentially to transform string A
   * into string B through a minimal set of changes.  To that end, all
   * deletions, insertions, and changes are from the point of view of
   * string A.
   *
   * For the following, B is considered be represented by the +x axis,
   * and A by the -y axis... that is, B across, A down.
   */

  /* 
   * Set the boundary values -- this means that to go from a string 
   * of length i to 0 requires a min. of i deletions.  Similar for j, 
   * except j deletions. 
   */
  for (i=0; i<= len_a; i++) {
    EDIT[i][0] = i;
  }

  for (j=0; j<= len_b; j++) {
    EDIT[0][j] = j;
  }

  /* Calculate */
  for (i=1; i<= len_a; i++) {
    for (j=1; j<= len_b; j++) {
      /* Calculate the new value */
      cha = EDIT[i-1][j-1];
      ins = EDIT[i][j-1] + insert;
      del = EDIT[i-1][j] + delete;

      /* Are the previous elements the same already? If not, change. */
      if (A[i-1] != B[j-1]) {
	cha += change;
      }

      /* Decide what is best (ie. min(cha, ins, del)) */
      if ((del <= ins) && (del <= cha)) {
	EDIT[i][j] = del;
      } else if (ins <= cha) {
	EDIT[i][j] = ins;
      } else {
	EDIT[i][j] = cha;
      }
    }
  }
  number_of_changes = EDIT[len_a][len_b];

  path_recovery(EDIT, A, B, change, insert, delete, aSample);
  
  /* Free up the memory. */
  for (i=0; i<= len_a; i++) {
    free(EDIT[i]);
  }

  free(EDIT);

  return number_of_changes;
}
  

int edit_equal(char *A, char *B, ReturnType *aSample) {
  return edit_general(A, B, 1, 1, 1, aSample);
}


int edit_no_changes(char *A, char *B, ReturnType *aSample) {
  return edit_general(A, B, 3, 1, 1, aSample);
}


int main () {
  char A[80];
  char B[80];
  ReturnType aSample;
  int i;

  while (scanf("%s %s", A, B) != EOF) {
    printf("Disallowing changes, it is: %d\n", 
	   edit_no_changes(A, B, &aSample));
    free(aSample.mods);

    printf("Allowing changes, the distance is: %d\n", 
	   edit_equal(A, B, &aSample));

    for (i=0; i<aSample.len; i++) {
      switch(aSample.mods[i]) {
      case INSERT:
	printf("Insert\n");
	break;
      case DELETE:
	printf("Delete\n");
	break;
      case CHANGE:
	printf("Change\n");
	break;
      }
    }
    free(aSample.mods);
  }

  return 0;
}


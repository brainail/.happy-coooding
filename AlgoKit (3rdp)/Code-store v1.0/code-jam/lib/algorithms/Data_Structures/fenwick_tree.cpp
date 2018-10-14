/*
Fenwick tree (aka Binary indexed tree) is a data structure that maintains a sequence of elements, and is able to compute cumulative sum of any range of consecutive elements in O(logn) time. Changing value of any single element needs O(logn) time as well.
The structure is space-efficient in the sense that it needs the same amount of storage as just a simple array of n elements.
*/

// In this implementation, the tree is represented by a vector<int>.
// Elements are numbered by 0, 1, ..., n-1.
// tree[i] is sum of elements with indexes i&(i+1)..i, inclusive.
// (Note: this is a bit different from what is proposed in Fenwick's article.
// To see why it makes sense, think about the trailing 1's in binary
// representation of indexes.)

// Creates a zero-initialized Fenwick tree for n elements.
vector<int> create(int n) { return vector<int>(n, 0); }

// Returns sum of elements with indexes a..b, inclusive
int query(const vector<int> &tree, int a, int b) {
    if (a == 0) {
        int sum = 0;
        for (; b >= 0; b = (b & (b + 1)) - 1)
          sum += tree[b];
        return sum;
    } else {
        return query(tree, 0, b) - query(tree, 0, a-1);
    }
}

// Increases value of k-th element by inc.
void increase(vector<int> &tree, int k, int inc) {
    for (; k < (int)tree.size(); k |= k + 1)
        tree[k] += inc;
}

typedef long long lint;
typedef unsigned long long ulint;

const int MAX = 1050;

int tree[MAX][MAX], lastx, lasty;
int M[MAX][MAX];

int
readx (int x, int y)
{
  int sum = 0;
  while (x > 0)
    {
      sum += tree[x][y];
      x -= (x & -x);
    }
  return sum;
}

int
getsum (int x, int y)
{
  int sum = 0;
  while (y > 0)
    {
      sum += readx (x, y);
      y -= (y & -y);
    }
  return sum;

}


void
updatey (int x, int y, int val)
{
  while (y = lasty)
    {
      tree[x][y] += val;
      y += (y & -y);
    }

}

void
update (int x, int y, int val)
{
  while (x = lastx)
    {
      updatey(x,y,val);
      x += (x & -x);
    }
}

int
get (int x1, int y1, int x2, int y2)
{
  int a = getsum (x1-1 , y1-1 );
  int b = getsum (x2, y2);
  int c = getsum (x2, y1 -1);
  int d = getsum (x1 -1, y2);
//	printf("%d,%d,%d,%d\n",a,b,c,d);
  return a + b - c - d;
}

int
main ()
{
  int no;
  scanf (" %d", &no);
  while (no--)
    {
      memset (tree, 0, sizeof (tree));
      int n, i, j, x, u, v, p, q, y;
      char str[10];
      scanf (" %d", &n);
      lastx = lasty = n;
      while (scanf (" %s", str) != EOF)
	{
	  if (strcmp (str, "END") == 0)
	    break;
	  if (strcmp (str, "SET") == 0)
	    {
	      	scanf (" %d %d %d", &x, &y, &v);

	      	x++, y++;
		int val=v-get(x,y,x,y);
		//int val=v-M[x][y];
//		printf("val=%d,%d\n",val,tree[x][y]);

	        update (x, y, val);

//		printf("after updating %d\n",tree[x][y]);
	    }
	  if (strcmp (str, "SUM") == 0)
	    {
	      scanf (" %d %d %d %d", &u, &v, &p, &q);
	       u++,v++,p++, q++;
	      printf ("%d\n", get (u, v, p, q));
	    }
	}
    }
	if(no) printf("\n");

  return 0;
}

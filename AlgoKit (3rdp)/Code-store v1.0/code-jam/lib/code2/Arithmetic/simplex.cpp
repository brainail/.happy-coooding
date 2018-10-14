//  Simplex Method for Linear Programming
// 
//  m - number of (less than) inequalities
//  n - number of variables
// 
//  C - (m+1) by (n+1) array of coefficients:
// 
//      row 0        - objective function coefficients
//      row 1:m      - less-than inequalities
// 
//      column 0:n-1 - inequality coefficients
//      column n     - inequality constants (0 for objective function)
// 
//  X[n] - result variables
// 
//  return value - maximum value of objective function
//                 (-inf for infeasible, inf for unbounded)
// 

#define MAXM 400   // leave one extra
#define MAXN 400   // leave one extra
#define EPS 1e-9
#define INF 1.0/0.0 

double A[MAXM][MAXN];
int basis[MAXM], out[MAXN];

void pivot(int m, int n, int a, int b) {
   int i,j;
   for (i=0;i<=m;i++) if (i!=a) for (j=0;j<=n;j++) if (j!=b) {
      A[i][j] -= A[a][j] * A[i][b] / A[a][b];
   }
   for (j=0;j<=n;j++) if (j!=b) A[a][j] /= A[a][b];
   for (i=0;i<=m;i++) if (i!=a) A[i][b] = -A[i][b]/A[a][b];
   A[a][b] = 1/A[a][b];

   i = basis[a];
   basis[a] = out[b];
   out[b] = i;
}


double simplex(int m, int n, double C[][MAXN], double X[]) {
   int i,j,ii,jj;  // i,ii are row indexes; j,jj are column indexes
   for (i=1;i<=m;i++) for (j=0;j<=n;j++) A[i][j] = C[i][j];
   for (j=0;j<=n;j++) A[0][j] = -C[0][j];
   for (i=0;i<=m;i++) basis[i] = -i;
   for (j=0;j<=n;j++) out[j] = j;

   for(;;) {
      for (i=ii=1;i<=m;i++) {
         if (A[i][n]<A[ii][n]
                 || (A[i][n]==A[ii][n] && basis[i]<basis[ii]))
             ii=i;
      }
      if (A[ii][n] >= -EPS) break;
      for (j=jj=0;j<n;j++) 
         if (A[ii][j]<A[ii][jj]-EPS
                 || (A[ii][j]<A[ii][jj]-EPS && out[i]<out[j]))
             jj=j;
      if (A[ii][jj] >= -EPS) return -INF;
      pivot(m,n,ii,jj);
   }
   
   for(;;) {
      for (j=jj=0;j<n;j++) 
         if (A[0][j]<A[0][jj]
                 || (A[0][j]==A[0][jj] && out[j]<out[jj]))
             jj=j;
      if (A[0][jj] > -EPS) break;
      for (i=1,ii=0;i<=m;i++)
         if (A[i][jj]>EPS && 
             (!ii || A[i][n]/A[i][jj]<A[ii][n]/A[ii][jj]-EPS ||
              (A[i][n]/A[i][jj]<A[ii][n]/A[ii][jj]+EPS
                  && basis[i]<basis[ii])))
             ii=i;
      if (A[ii][jj] <= EPS) return INF;
      pivot(m,n,ii,jj);
   }

   for (j=0;j<n;j++) X[j] = 0;
   for (i=1;i<=m;i++) if (basis[i] >= 0) X[basis[i]] = A[i][n];
   return A[0][n];
}
   
void print(int m, int n, char *msg) {  // not used -- debug only
   int i,j;
   printf("%s\n",msg);
   for(i=0;i<=m;i++) {
      for (j=0;j<=m;j++) printf(" %10d",i==j);
      for (j=0;j<=n;j++) printf(" %10g",A[i][j]);
      printf("\n");
   }
   for (i=0;i<=m;i++) printf(" %10d",basis[i]);
   for (j=0;j<n;j++) printf(" %10d",out[j]);
   printf("\n");
}

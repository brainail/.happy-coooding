#include<iostream>
#define MAXN 100
#define MAXM 100

using namespace std;

int matrix[MAXN][MAXM];
 
void process(int i, int j) {
      cout << matrix[i][j] << " ";
}

void row_major(int n, int m) {
   for(int i=1; i<=n; i++)
      for(int j=1; j<=m; j++)
         process(i, j);
   cout << endl << endl;
}

void column_major(int n, int m) {
   for(int j=1; j<=m; j++)
      for(int i=1; i<=n; i++)
         process(i, j);
   cout << endl << endl;
}

void snake_order(int n, int m) {
   for(int i=1; i<=n; i++)
      for(int j=1; j<=m; j++)
         process(i, j+(m+1-(2*j))*((i+1)%2));
   cout << endl << endl;
}

void diagonal_order(int n, int m) {
   int d;
   int pcount;
   int height;
   
   for(d=1; d<=(m+n-1); d++) {
      height = 1 + max(0, d-m);
      pcount = min(d, (n-height+1));
      for(int j=0; j<pcount; j++)
         process(min(m, d)-j, height+j);
   }
   cout << endl << endl;
}

int main() {
   for(int i=1; i<=3; i++) {
      for(int j=1; j<=3; j++)
         cin >> matrix[i][j];
   }
   
   row_major(3, 3);
   column_major(3, 3);
   snake_order(3, 3);
   diagonal_order(3, 3);
   return 0;
}

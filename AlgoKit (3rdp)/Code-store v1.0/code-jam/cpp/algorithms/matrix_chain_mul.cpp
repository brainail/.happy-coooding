#include<cstdio>
#define MAX 15 /* number of matrix */
#define INF 4294967295 /* a maximum number of multiplication */

int num;
/* ************************************************* */
/* Print out the sequence */
/* Input : A two dimentional array(created */
/* by the matrix chan order function) */
/* with there starting point */
/* Return : None */
/* ************************************************* */
void print(unsigned long s[][MAX], int i, int j)
{
    if(i == j)
        printf("A%d", num++);
    else {
        printf("(");
        print(s, i, s[i][j]);
        printf(" x ");
        print(s, s[i][j] + 1, j);
        printf(")");
    }
}

/* *********************************************** */
/* Find out the order */
/* Input : A sequence of dimention and the */
/* number of matrix */
/* Return : none */
/* *********************************************** */
void matrix_chan_order(int *p, int n)
{
    unsigned long m[MAX][MAX] = {0};
    unsigned long s[MAX][MAX] = {0};
    unsigned int q;
    int l, j, i, k;

    for(l = 2; l <= n ; l++) {
        for(i = 1 ; i <= n - l + 1 ; i++) {
            j = i + l - 1;
            m[i][j] = INF;

            for(k = i ; k < j ; k++) {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];

                if(q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    num = 1;
    print(s, 1, n);
}

/* A sample main function */
main(void)
{
    int n;
    int p[MAX] = {0};
    int i;

    while(scanf("%d", &n), n) {
        for(i = 1; i <= n; i++)
            scanf("%d %d", &p[i - 1], &p[i]);

        matrix_chan_order(p, n);
        putchar('\n');
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#define N 8
void backtrack(int* column, int* rup, int* lup, int* queen, int);
int main(void)
{
    int column[N + 1];
    int rup[2 * N + 1];
    int lup[2 * N + 1];
    int queen[N + 1] = {0};
    int i;

    for(i = 1; i <= N; i++)
        column[i] = 1;

    for(i = 1; i <= 2 * N; i++)
        rup[i] = lup[i] = 1;

    backtrack(column, rup, lup, queen, 1);
    return 0;
}
void printQueen(int* queen)
{
    int x, y;

    for(y = 1; y <= N; y++) {
        for(x = 1; x <= N; x++) {
            printf(" %c", queen[y] == x ? 'Q' : '.');
        }

        printf("\n");
    }

    printf("\n");
}
void backtrack(int* column, int* rup, int* lup, int* queen, int i)
{
    if(i > N) {
        printQueen(queen);
    } else {
        int j;

        for(j = 1; j <= N; j++) {
            if(column[j] == 1 &&
                    rup[i + j] == 1 && lup[i - j + N] == 1) {
                queen[i] = j;
                column[j] = rup[i + j] = lup[i - j + N] = 0;
                backtrack(column, rup, lup, queen, i + 1);
                column[j] = rup[i + j] = lup[i - j + N] = 1;
            }
        }
    }
}

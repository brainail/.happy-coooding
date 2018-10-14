/**
 * 篩法建質數表
 */
#include<cstdio>
using namespace std;
enum {MAX = 1001};

char p[MAX]; //prime=0, not prime=1

void shieve()
{
    p[0] = 1;
    p[1] = 0; //本題1算質數

    for(int i = 2; i * i < MAX; ++i) {
        if(p[i] == 1)
            continue;

        for(int j = i * i; j < MAX; j += i)
            p[j] = 1;
    }
}

int main()
{
    shieve();

    for(int i = 0; i < MAX; ++i) {
        if(p[i] == 0)
            printf(" %d is prime. \n", i);
    }
}

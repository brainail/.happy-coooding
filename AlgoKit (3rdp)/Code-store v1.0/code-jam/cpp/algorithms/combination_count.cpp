#include <iostream>
#include <cmath>
#define MAX 30
double test(char *str)
{
    int de[MAX] = {0};
    int ss[300] = {0};
    int l = strlen(str);
    int i, j = 0;
    double c = 1, d = 1;

    for(i = 0; i < l; i++) {
        ss[str[i]]++;

        if(ss[str[i]] > 1)
            de[j++] = ss[str[i]];
    }

    c = 1;

    for(i = 2; i <= l; i++) {
        c *= i;

        if(j > 0)
            d *= de[--j];

        if((d != 1) && !(fmod(c, d))) {
            c /= d;
            d = 1;
        }
    }

    return c;
}

main(void)
{
    char word[MAX];
    int n;
    int j = 0;
    scanf("%d", &n);

    for(; n > 0; n--) {
        scanf("%s", word);
        printf("Data set %d: %.0f", ++j, test(word));
        putchar('\n');
    }

    return 0;
}

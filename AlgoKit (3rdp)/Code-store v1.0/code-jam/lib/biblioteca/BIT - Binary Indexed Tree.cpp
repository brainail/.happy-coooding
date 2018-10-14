#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int tree[(1<<18)+1];

int add(int ind){
    while( ind <= n ){
        tree[ind]++;
        ind += (ind & -ind); 
        // ind = ind + 2^r , r = indice do ultimo digito 1, da rep. binária
    }
    return 0;
}

int find(int ind){
    int s = 0;
    while(ind > 0){
        s += tree[ind];
        ind -= (ind & -ind);
    }
    return s;
}

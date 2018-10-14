#include <iostream> 
#include <sstream> 
#include <string> 
#include <vector> 
#include <deque> 
#include <queue> 
#include <stack> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <math.h> 


using namespace std; 

int tree[20][70000];
long long t[300000];

/* 
RMQ - Range Minimum Query  - N * Log N

Calcula o k-esimo menor elemento de um conjunto em varias iterações:
Em cada iteração, um valor do conjunto é alterado
*/

int insert(int x){
    int a = x,lv;    
    for(lv = 0; lv <= 16; lv++ ) {
        tree[lv][a]++;
        a/=2;
    }
    return 0;
}

int remove(int x){
    int a = x,lv;
    for(lv = 0;lv <= 16; lv++){
        tree[lv][a]--;
        a/=2;
    }
    return 0;
}

int k_element(int k){
    int a = 0,lv;
    for(lv = 16; lv >= 0; lv-- ){
        a *= 2;
        if( tree[lv][a] < k ){
            k -= tree[lv][a++];
        }
    }
    return a;
}

/* 
 * File:   algorithms.cpp
 * Author: seb
 *
 * Created on 25 de junio de 2010, 10:55 AM
 */

#include "algorithms.h"
#include <cstring>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>


char *alg_mark;
int *alg_lista;

//r most be less or equal than n, index=0
void perm(int* vector, int n, int r, int index, void (*func) (int*,int)) {
    if (r==0) {
        func(alg_lista,index);
        return;
    }
    for (int i=0; i<n; i++) {
        if (! alg_mark[i]) {
            alg_mark[i]=1;
            alg_lista[index]=vector[i];
            perm(vector, n, r-1, index+1, func);
            alg_mark[i]=0;
        }
    }
}

//r most be less or equal than n, index=0
void comb(int* vector, int n, int r, int index, void (*func) (int*,int)) {
    if (r==0) {
        func(alg_lista,index);
        return;
    }
    int *nvect = vector;
    for (int i=0; i<=(n-r); i++) {
        alg_lista[index]=vector[i];
        comb(++nvect, n-i-1, r-1, index+1, func);
    }
}

/**
 * Receives a vector of n integers and does all possible permutations
 * of r elements. Once a new permutation if found, it calls the received
 * function func with the computed vector and its respective size (r)
 */
void permutations(int* vector, int n, int r, void (*func) (int*,int)) {
    if ((r<0) || (r>n)) return;
    alg_mark = new char[n];
    alg_lista = new int[r];
    memset(alg_mark,0,n);
    perm(vector,n,r,0,func);
    delete [] alg_mark;
    delete [] alg_lista;
}


using namespace std;

char entrada[20];

int main()
{
    int tam = 0;
    int caseN = 1;
    while ((cin >> entrada) && (tam = strlen(entrada)))
    {
        sort(entrada, entrada + tam);
        cout << "Case " << caseN++ << "\n";
        do
        {
            cout << entrada << "\n";
        } while(next_permutation(entrada, entrada + tam));
        cout << endl;
    }
}

/**
 * Receives a vector of n integers and does all possible combinations
 * of r elements. Once a new combination if found, it calls the received
 * function func with the computed vector and its respective size (r)
 */
void combinations(int* vector, int n, int r, void (*func) (int*,int)) {
    if ((r<0) || (r>n)) return;
    alg_lista = new int[r];
    comb(vector,n,r,0,func);
    delete [] alg_lista;
}


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cassert>
#include <vector>
#include <cmath>
#include <complex>
#include <map>
#include <queue>
using namespace std;

struct No {
    int fail;
    vector< pair<int,int> > out;
    map<char, int> the_list;
    int next;
};
No tree[1000003];
int qtdNos, qtdPadroes;

void init() {
    tree[0].fail = -1;
    tree[0].the_list.clear();
    tree[0].out.clear();
    tree[0].next = -1;
    qtdNos = 1;
    qtdPadroes = 0;
}

void activate() {
    int no,v,f,w;
    queue<int> row;
    for (map<char,int>::iterator it = tree[0].the_list.begin();
         it != tree[0].the_list.end() ; it++) {
        tree[no = it->second].fail = 0;
        tree[no].next = tree[0].out.size() ? 0 : -1;
        row.push(no);
    }
    while (!row.empty()) {
        no = row.front(); row.pop();
        for (map<char,int>::iterator it=tree[no].the_list.begin();
             it!=tree[no].the_list.end(); it++) {
            char c = it->first;
            v = it->second;
            row.push(v);
            f = tree[no].fail;
            while (tree[f].the_list.find(c) == tree[f].the_list.end()) {
                if (f == 0) { tree[0].the_list[c] = 0; break; }
                f = tree[f].fail;
            }
            w = tree[f].the_list[c];
            tree[v].fail = w;
            tree[v].next = tree[w].out.size() ? w : tree[w].next;
        }
    }
}

void add(char *input) {
    int no = 0, len = 0;
    for (int i = 0 ; input[i] ; i++, len++) {
        if (tree[no].the_list.find(input[i]) == tree[no].the_list.end()) {
            tree[qtdNos].the_list.clear(); tree[qtdNos].out.clear();
            tree[no].the_list[input[i]] = qtdNos;
            no = qtdNos++;
        } else no = tree[no].the_list[input[i]];
    }
    tree[no].out.push_back(pair<int,int>(qtdPadroes++,len));
}

void search(char *input) {
    int v, no = 0;
    for (int i = 0 ; input[i] ; i++) {
        while (tree[no].the_list.find(input[i]) == tree[no].the_list.end()) {
            if (no == 0) { tree[0].the_list[input[i]] = 0; break; }
            no = tree[no].fail;
        }
        v = no = tree[no].the_list[input[i]];
        while (v != -1) {
            for (int k = 0 ; k < tree[v].out.size() ; k++) {
                printf("Default %d in position %d\n", tree[v].out[k].first,
                       i-tree[v].out[k].second+1);
            }
            v = tree[v].next;
        }
    }
}

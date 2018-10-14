#include <iostream>
#include<vector>
#define abs(X) ((X) < 0 ? (-(X)) : (X))

using namespace std;

struct Query;

struct Nodo
{
    vector <Nodo*> adjacentes;
    vector <Query*> queries;
    int numero;
    long long distanciaCero;
    Nodo *parent;
    Nodo *ancestor;
    int rank;
    bool encontrado;

    void clear(int i)
    {
        numero = i;
        distanciaCero = 0;
        adjacentes.clear();
        queries.clear();
        encontrado = false;
    }
};

struct Query
{
    Nodo *a, *b;
    long long respuesta;
};

Nodo nodos[100001];
Query queries[100001];

void makeSet(Nodo *x)
{
     x->parent = x;
     x->rank   = 0;
}

Nodo* find(Nodo *x)
{
     if(x->parent == x)
        return x;
     else
     {
        x->parent = find(x->parent);
        return x->parent;
     }
}

int unir(Nodo *x, Nodo *y)
 {
     Nodo *xRoot = find(x);
     Nodo *yRoot = find(y);
     if(xRoot->rank > yRoot->rank)
         yRoot->parent = xRoot;
     else if(xRoot->rank < yRoot->rank)
         xRoot->parent = yRoot;
     else if(xRoot != yRoot)
     {
         yRoot->parent = xRoot;
         xRoot->rank = xRoot->rank + 1;
     }
 }


void tarjanOLCA(Nodo *u)
{
    makeSet(u);
    u->ancestor = u;
    for(int i = 0; i < u->adjacentes.size(); i++)
    {
        tarjanOLCA(u->adjacentes[i]);
        unir(u, u->adjacentes[i]);
        find(u)->ancestor = u;
    }
    u->encontrado = true;
    for(int i = 0; i < u->queries.size(); i++)
    {
        Query *actual = u->queries[i];
        Nodo *v;
        if(u == actual->a)
            v = actual->b;
        else
            v = actual->a;
        if(v->encontrado)
        {
            Nodo *ancestro = find(v)->ancestor;
            if(ancestro == v || ancestro == u)
                actual->respuesta = abs(v->distanciaCero - u->distanciaCero);
            else
                actual->respuesta = u->distanciaCero + v->distanciaCero - (2 * ancestro->distanciaCero);
        }
    }
}

int main()
{
    while(true)
    {
        int n;
        cin >> n;
        if(n == 0)
            break;
        nodos[0].clear(0);
        for(int i = 1; i < n; i++)
        {
            nodos[i].clear(i);
            int anterior, costo;
            cin >> anterior >> costo;
            nodos[anterior].adjacentes.push_back(&nodos[i]);
            nodos[i].distanciaCero = nodos[anterior].distanciaCero + costo;
        }
        int q;
        cin >> q;
        for(int i = 0; i < q; i++)
        {
            int s, t;
            cin >> s >> t;
            queries[i].a = &nodos[s];
            queries[i].b = &nodos[t];
            nodos[s].queries.push_back(&queries[i]);
            nodos[t].queries.push_back(&queries[i]);
        }
        tarjanOLCA(&nodos[0]);
        cout << queries[0].respuesta;
        for(int i = 1; i < q; i++)
        {
            cout << " " << queries[i].respuesta;
        }
        cout << endl;
    }
}
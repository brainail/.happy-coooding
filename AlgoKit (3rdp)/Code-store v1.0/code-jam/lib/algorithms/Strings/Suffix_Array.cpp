#include<iostream>
#include<stdio.h>
#include<math.h>
#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include<stdlib.h>
#include<assert.h>
#include<sstream>
#include<stack>
#include<queue>
#include<cstring>
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))
#define REP(i, n) for(int i = 0; i < n; i++)

using namespace std;

struct Letra
{
    char letra;
    char veces;
};

struct SAString
{
    char *s;
    int *letras;
    Letra *letrasTiene;
    int tam;
    int dp;

    SAString()
    {
        s = new char[1010];
        letras = new int[26];
        letrasTiene = new Letra[26];
    }

    void llenarLetras()
    {
        for(int i = 0; i < 26; i++)
        {
            letras[i] = 0;
            letrasTiene[i].veces = 0;
        }
        for(int i = 0; i < tam; i++)
        {
            letras[s[i] - 'a']++;
        }
        int cuenta = 0;
        for(int i = 0; i < 26; i++)
        {
            if(letras[i] > 0)
            {
                letrasTiene[cuenta].letra = i;
                letrasTiene[cuenta++].veces = letras[i];
            }
        }
        s[tam] = '$';
        s[++tam] = '\0';
    }

    bool chequearSubS(SAString *otro)
    {
        for(int i = 0; i < 26; i++)
        {
            if(letrasTiene[i].veces == 0)
                break;
            if(letrasTiene[i].veces > otro->letras[letrasTiene[i].letra])
                return false;
        }
        return true;
    }

    SAString(int tamMaximo)
    {
        s = new char[tamMaximo + 1];
        tam = 0;
        s[0] = '\0';
    }

    void strcat(char *actual, int numero)
    {
        while(*actual != '\0')
        {
            s[tam++] = *actual;
            actual++;
        }
    }

    bool operator<(const SAString &otro) const
    {
        return tam > otro.tam;
    }
};

struct SAComp {
  const int h, *g;
  SAComp(int h, int* g) : h(h), g(g) {}
  bool operator() (int a, int b) {
    return a == b ? false : g[a] != g[b] ? g[a] < g[b] : g[a+h] < g[b+h];
  }
};

inline bool leq(int a1, int a2,   int b1, int b2) { // lexic. order for pairs
  return(a1 < b1 || a1 == b1 && a2 <= b2);
}                                                   // and triples
inline bool leq(int a1, int a2, int a3,   int b1, int b2, int b3) {
  return(a1 < b1 || a1 == b1 && leq(a2,a3, b2,b3));
}

int c[10000];
// stably sort a[0..n-1] to b[0..n-1] with keys in 0..K from r
static void radixPass(int* a, int* b, int* r, int n, int K)
{ // count occurrences                      // counter array
  for (int i = 0;  i <= K;  i++) c[i] = 0;         // reset counters
  for (int i = 0;  i < n;  i++) c[r[a[i]]]++;    // count occurences
  for (int i = 0, sum = 0;  i <= K;  i++) { // exclusive prefix sums
     int t = c[i];  c[i] = sum;  sum += t;
  }
  for (int i = 0;  i < n;  i++) b[c[r[a[i]]]++] = a[i];      // sort
}

// find the suffix array SA of s[0..n-1] in {1..K}^n
// require s[n]=s[n+1]=s[n+2]=0, n>=2
void suffixArray(int* s, int* SA, int n, int K) {
  int n0=(n+2)/3, n1=(n+1)/3, n2=n/3, n02=n0+n2;
  int* s12  = new int[n02 + 3];  s12[n02]= s12[n02+1]= s12[n02+2]=0;
  int* SA12 = new int[n02 + 3]; SA12[n02]=SA12[n02+1]=SA12[n02+2]=0;
  int* s0   = new int[n0];
  int* SA0  = new int[n0];

  // generate positions of mod 1 and mod  2 suffixes
  // the "+(n0-n1)" adds a dummy mod 1 suffix if n%3 == 1
  for (int i=0, j=0;  i < n+(n0-n1);  i++) if (i%3 != 0) s12[j++] = i;

  // lsb radix sort the mod 1 and mod 2 triples
  radixPass(s12 , SA12, s+2, n02, K);
  radixPass(SA12, s12 , s+1, n02, K);
  radixPass(s12 , SA12, s  , n02, K);

  // find lexicographic names of triples
  int name = 0, c0 = -1, c1 = -1, c2 = -1;
  for (int i = 0;  i < n02;  i++) {
    if (s[SA12[i]] != c0 || s[SA12[i]+1] != c1 || s[SA12[i]+2] != c2) {
      name++;  c0 = s[SA12[i]];  c1 = s[SA12[i]+1];  c2 = s[SA12[i]+2];
    }
    if (SA12[i] % 3 == 1) { s12[SA12[i]/3]      = name; } // left half
    else                  { s12[SA12[i]/3 + n0] = name; } // right half
  }

  // recurse if names are not yet unique
  if (name < n02) {
    suffixArray(s12, SA12, n02, name);
    // store unique names in s12 using the suffix array
    for (int i = 0;  i < n02;  i++) s12[SA12[i]] = i + 1;
  } else // generate the suffix array of s12 directly
    for (int i = 0;  i < n02;  i++) SA12[s12[i] - 1] = i;

  // stably sort the mod 0 suffixes from SA12 by their first character
  for (int i=0, j=0;  i < n02;  i++) if (SA12[i] < n0) s0[j++] = 3*SA12[i];
  radixPass(s0, SA0, s, n0, K);

  // merge sorted SA0 suffixes and sorted SA12 suffixes
  for (int p=0,  t=n0-n1,  k=0;  k < n;  k++) {
#define GetI() (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2)
    int i = GetI(); // pos of current offset 12 suffix
    int j = SA0[p]; // pos of current offset 0  suffix
    if (SA12[t] < n0 ?
        leq(s[i],       s12[SA12[t] + n0], s[j],       s12[j/3]) :
        leq(s[i],s[i+1],s12[SA12[t]-n0+1], s[j],s[j+1],s12[j/3+n0]))
    { // suffix from SA12 is smaller
      SA[k] = i;  t++;
      if (t == n02) { // done --- only SA0 suffixes left
        for (k++;  p < n0;  p++, k++) SA[k] = SA0[p];
      }
    } else {
      SA[k] = j;  p++;
      if (p == n0)  { // done --- only SA12 suffixes left
        for (k++;  t < n02;  t++, k++) SA[k] = GetI();
      }
    }
  }
  delete [] s12; delete [] SA12; delete [] SA0; delete [] s0;
}

// ojo, las funciones de esta clase esperan que todos los SAStrings tengan un $
// al final
struct SuffixArray
{
    int *g, *b, *sa, *lcp, *rmq, n, *aux;
    char *t;

    SuffixArray(int tamMax)
    {
        g = new int[tamMax];
        b = new int[tamMax];
        sa = new int[tamMax];
        lcp = new int[tamMax];
        aux = new int[tamMax + 3];
        int logn = 1;
        int n = tamMax;
        for (int k = 1; k < n; k *= 2) ++logn;
        rmq = new int[n * logn];
    }

    void buildSA(SAString *sas) {
      n = sas->tam;
      t = sas->s;
      for(int i = 0; i < n; i++)
      {
          aux[i] = t[i];
      }
      aux[n] = aux[n + 1] = aux[n + 2] = 0;
      suffixArray(aux, sa, n, 256); // Construccion en O(n) usa new y delete
      n--;
// Construccion del SA en O(n * log n * log n)
//      REP(i,n+1) sa[i] = i, g[i] = t[i];
//      b[0] = 0; b[n] = 0;
//      sort(sa, sa+n+1, SAComp(0, g));
//      for(int h = 1; b[n] != n ; h *= 2) {
//        SAComp comp(h, g);
//        sort(sa, sa+n+1, comp);
//        REP(i, n) b[i+1] = b[i] + comp(sa[i], sa[i+1]);
//        REP(i, n+1) g[sa[i]] = b[i];
//      }
//      cout << t << endl;
//      for(int i = 0; i < n; i++)
//      {
//          cout << t + sa[i] <<  " jeje" << endl;
//      }
      buildLCP();
      buildRMQ();
    }

    // Naive matching O(m log n)
    int findN(SAString *o) {
      char *p = o->s;
      int m = o->tam - 1;
      int temp = n;
      int n = temp + 1;
      int a = 0, b = n;
      while (a < b) {
        int c = (a + b) / 2;
        if (strncmp(t+sa[c], p, m) < 0) a = c+1; else b = c;
      }
      return strncmp(t+sa[a], p, m) == 0 ? sa[a] : -1;
    }

    // Kasai-Lee-Arimura-Arikawa-Park's simple LCP computation: O(n)
    void buildLCP() {
      int *a = sa;
      int h = 0;
      REP(i, n+1) b[a[i]] = i;
      REP(i, n+1) {
        if (b[i]){
          for (int j = a[b[i]-1]; j+h<n && i+h<n && t[j+h] == t[i+h]; ++h);
          lcp[b[i]] = h;
        } else lcp[b[i]] = -1;
        if (h > 0) --h;
      }
    }

    // call RMQ = buildRMQ(lcp, n+1)
    void buildRMQ() {
      int temp = n;
      int n = temp + 1;
      int *b = rmq; copy(lcp, lcp+n, b);
      for (int k = 1; k < n; k *= 2) {
        copy(b, b+n, b+n); b += n;
        REP(i, n-k) b[i] = min(b[i], b[i+k]);
      }
    }

    // inner LCP computation with RMQ: O(1)
    int minimum(int x, int y) {
      int temp = n;
      int n = temp + 1;
      int z = y - x, k = 0, e = 1, s;
      s = ( (z & 0xffff0000) != 0 ) << 4; z >>= s; e <<= s; k |= s;
      s = ( (z & 0x0000ff00) != 0 ) << 3; z >>= s; e <<= s; k |= s;
      s = ( (z & 0x000000f0) != 0 ) << 2; z >>= s; e <<= s; k |= s;
      s = ( (z & 0x0000000c) != 0 ) << 1; z >>= s; e <<= s; k |= s;
      s = ( (z & 0x00000002) != 0 ) << 0; z >>= s; e <<= s; k |= s;
      return min( rmq[x+n*k], rmq[y+n*k-e+1] );
    }

    // outer LCP computation: O(m - o)
    int computeLCP(char *t, int n, char *p, int m, int o, int k) {
      int i = o;
      for (; i < m && k+i < n && p[i] == t[k+i]; ++i);
      return i;
    }

    // Mamber-Myers's O(m + log n) string matching with LCP/RMQ
    #define COMP(h, k) (h == m || (k+h<n && p[h]<t[k+h]))
    int find(SAString *o) {
      char *p = o->s;
      int m = o->tam - 1;
      int l = 0, lh = 0, r = n, rh = computeLCP(t,n+1,p,m,0,sa[n]);
      if (!COMP(rh, sa[r])) return -1;
      for (int k = (l+r)/2; l+1 < r; k = (l+r)/2) {
        int A = minimum(l+1, k), B = minimum(k+1, r);
        if (A >= B) {
          if (lh < A) l = k;
          else if (lh > A) r = k, rh = A;
          else {
            int i = computeLCP(t, n+1, p, m, A, sa[k]);
            if (COMP(i, sa[k])) r = k, rh = i; else l = k, lh = i;
          }
        } else {
          if (rh < B) r = k;
          else if (rh > B) l = k, lh = B;
          else {
            int i = computeLCP(t, n+1, p, m, B, sa[k]);
            if (COMP(i, sa[k])) r = k, rh = i; else l = k, lh = i;
          }
        }
      }
      return rh == m ? r : -1;
    }
};

bool comparar(SAString *a, SAString *b)
{
    return a->tam > b->tam;
}

SAString *palabras[10010];

int main()
{
    int n;
    SuffixArray sa(1200);
    for(int i = 0; i < 10010; i++)
    {
        palabras[i] = new SAString();
    }
    while (true)
    {
        cin >> n;
        if(n == 0)
            break;
        for (int i = 0; i < n; i++)
        {
            cin >> palabras[i]->s;
            palabras[i]->tam = strlen(palabras[i]->s);
            palabras[i]->dp = 1;
            palabras[i]->llenarLetras();
        }
        sort(palabras, palabras + n, comparar);
        for(int i = 0; i < n; i++)
        {
            SAString *actual = palabras[i];
            int dpSig = actual->dp + 1;
            int tamActual = actual->tam;
            sa.buildSA(actual);
            for(int j = i + 1; j < n; j++)
            {
                SAString *posible = palabras[j];
                if(dpSig < posible->dp || tamActual <= posible->tam)
                    continue;
                if(posible->chequearSubS(actual) && sa.find(posible) != -1)
                    posible->dp = dpSig;
            }
        }
        int mejor = 0;
        for(int i = 0; i < n; i++)
        {
            mejor = MAX(mejor, palabras[i]->dp);
        }
        cout << mejor << endl;
    }
}

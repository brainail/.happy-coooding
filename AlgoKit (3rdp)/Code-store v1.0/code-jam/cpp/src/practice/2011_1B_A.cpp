#include <algorithm>
#include <bitset>
#include <cassert>
#include <cfloat>
#include <climits>
#include <cmath>
#include <complex>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;
#define _USE_MATH_DEFINES  // exposes constants, eg. M_PI
#define s(n)                scanf("%d",&n)
#define sl(n)               scanf("%lld",&n)
#define sf(n)               scanf("%lf",&n)
#define ss(n)               scanf("%s",n)
#define INF                 (1<<30)
#define LINF                (long long) 1E18
#define EPS                 std::numeric_limits<double>::epsilon()
#define ABS(x)              ((x)<0?-(x):(x))
#define FOR(i,a,b)          for(int i=a; i<b; ++i)
#define RFOR(i,a,b)         for(int i=(a)-1,_b(b); i>=_b; --i)
#define REP(i,n)            for((i)=0;(i)<(int)(n);++(i))
#define DREP(a)             sort(all(a)); a.erase(unique(all(a)),a.end())
#define INDEX(arr,ind)      (lower_bound(all(arr),ind)-arr.begin())
#define FOREACH(c,itr)      for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();++itr)
#define mp                  make_pair
#define pb                  push_back
#define tri(a,b,c)          mp(a,mp(b,c))
#define fst                 first
#define snd                 second
#define FILL(a,v)           memset(a,v,sizeof(a))
#define SQR(a)              ((a)*(a))
#define MAX(a,b)            ((a)>(b)?(a):(b))
#define MIN(a,b)            ((a)<(b)?(a):(b))
#define ALL(x)              x.begin(),x.end()
#define SZ(v)               ((int)(v.size()))
#define LOG(a)              (cerr<<"line#"<<__LINE__<<": "#a" = "<<(a)<<endl)
#define DBG(...)            (__VA_ARGS__)
#define debug(args...)      {cerr<<"case#";dbg,args;cerr<<endl;}
struct debugger {
    template<typename T> debugger& operator, (const T& v) {
        cerr << v << " ";
        return *this;
    }
} dbg;
template<class T> T gcd(T a, T b)
{
    return b ? gcd(b, a % b) : a;
}
typedef long long        LL;
typedef unsigned long long ULL;
typedef unsigned int      uint;
typedef pair<int, int>   PII;
typedef pair<LL, LL>   PLL;
typedef pair<int, PII>   TRI;
typedef vector<int>   VI;
typedef vector<LL>     VL;
typedef vector<string>   VS;
typedef vector<PII>   VII;
typedef vector<PLL>   VLL;
typedef vector<TRI>   VT;
typedef vector<VI>     VVI;
typedef vector<VL>     VVL;
typedef vector<VII>   VVII;
typedef vector<VLL>   VVLL;
typedef vector<VT>     VVT;
typedef complex<double> pt;
typedef complex<LL>     pti;
const double PI   = M_PI;
double round(double x)
{
    const double sd = 100; // for accuracy to 2 decimal places
    return int(x * sd + (x < 0 ? -0.5 : 0.5)) / sd;
}
int cmp(double x, double y = 0, double tol = EPS)
{
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
/////////////////////////////////////////////////////////////////////////////
const int MAXN = 101;
int cc, T, i, j, k, N;
char table[MAXN][MAXN];
double OWP[MAXN], OOWP[MAXN], RPI[MAXN];
PII WP[MAXN];
int main()
{
    //clock_t start = clock();
    scanf("%d", &T);
    REP(cc, T) {
        scanf("%d", &N);
        memset(table, 0, MAXN * MAXN);
        REP(i, N) {
            scanf("%s", table[i]);
            WP[i] = mp(0, 0);
        }
        memset(OWP, 0.0f, MAXN);
        memset(OOWP, 0.0f, MAXN);
        memset(RPI, 0.0f, MAXN);
        REP(i, N) {
            int num_won = 0, num_played = 0;
            REP(j, N) {
                if(table[i][j] != '.') {
                    num_played++;
                }

                if(table[i][j] == '1') {
                    num_won++;
                }
            }
            WP[i] = mp(num_won, num_played);
        }
        REP(i, N) {
            double temp = 0.0;
            int num_games = 0;
            REP(j, N) {
                if(table[i][j] != '.') {
                    int num_won = 0, num_played = 0;
                    REP(k, N) {
                        if(k == i) continue;

                        if(table[j][k] != '.') {
                            num_played++;
                        }

                        if(table[j][k] == '1') {
                            num_won++;
                        }
                    }
                    temp += num_won / (double)num_played;
                    num_games++;
                }
            }
            OWP[i] = temp / (double)num_games;
        }
        REP(i, N) { // i team
            double temp = 0;
            int num_games = 0;
            REP(j, N) { // j opponent
                if(i == j || table[j][i] == '.') continue;

                temp += OWP[j];
                num_games++;
            }
            OOWP[i] = temp / (double)num_games;
        }
        printf("Case #%d:\n", cc + 1);
        for(int i = 0; i < N; ++i) {
            double RPI = 0.25 * (WP[i].first / (double)WP[i].second) + 0.50 * OWP[i] + 0.25 * OOWP[i];
            printf("%lf\n", RPI);//, WP[i].first / (double)WP[i].second, OWP[i], OOWP[i]);
        }

        /*for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                printf("%c", table[i][j]);
            }
            printf("\n");
        }*/
    }
    //fprintf(stderr, "*** Total time: %.3lf seconds ***\n",
    //        ((clock() - start) / (double) CLOCKS_PER_SEC));
    return 0;
}

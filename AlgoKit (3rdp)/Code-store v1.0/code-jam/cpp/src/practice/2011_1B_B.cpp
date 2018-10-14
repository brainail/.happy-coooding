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
#define S(n)                scanf("%d",&n)
#define SLL(n)              scanf("%lld",&n)
#define SD(n)               scanf("%lf",&n)
#define SS(n)               scanf("%s",n)
#define INF                 INT_MAX
#define LINF                LLONG_MAX
#define EPS                 std::numeric_limits<double>::epsilon()
#define ABS(x)              ((x)<0?-(x):(x))
#define FOR(i,a,b)          for(int i=a;i<b;++i)
#define RFOR(i,a,b)         for(int i=(a)-1,_b(b);i>=_b;--i)
#define REP(i,n)            for(int (i)=0;(i)<(int)(n);++(i))
#define RREP(i,n)           for(int (i)=n;(i)>=(int)0;--(i))
#define DREP(a)             sort(all(a)); a.erase(unique(all(a)),a.end())
#define INDEX(arr,ind)      (lower_bound(all(arr),ind)-arr.begin())
#define FOREACH(c,itr)      for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();++itr)
#define mp                  make_pair
#define pb                  push_back
#define tri(a,b,c)          mp(a,mp(b,c))
#define fst                 first
#define snd                 second
//#define FILL(a,v)           memset(a,v,sizeof(a))
#define SQT(a)              ((a)*(a))
//#define MAX(a,b)            ((a)>(b)?(a):(b))
//#define MIN(a,b)            ((a)<(b)?(a):(b))
#define ALL(x)              x.begin(),x.end()
#define SZ(v)               ((int)(v.size()))
#define LOG(a)              (cerr<<"\tline#"<<__LINE__<<": "#a" = "<<(a)<<endl)
#define DBG(args...)      {cerr<<"\tcase#"<<(cc+1)<<": ";dbg,args;cerr<<endl;}
struct debugger {
    template<typename T> debugger& operator, (const T& v) {
        cerr << v << " ";
        return *this;
    }
} dbg;
typedef long long       LL;
typedef long long       ll;
typedef unsigned long long ULL;
typedef unsigned int    uint;
typedef pair<int, int>  PII;
typedef pair<LL, LL>    PLL;
typedef pair<int, PII>  TRI;
typedef vector<int>     VI;
typedef vector<LL>      VL;
typedef vector<string>  VS;
typedef vector<PII>     VII;
typedef vector<PLL>     VLL;
typedef vector<TRI>     VT;
typedef vector<VI>      VVI;
typedef vector<VL>      VVL;
typedef vector<VII>     VVII;
typedef vector<VLL>     VVLL;
typedef vector<VT>      VVT;
typedef complex<double> pt;
typedef complex<LL>     pti;
const double PI   = M_PI;
template<class T> inline T gcd(T a, T b)
{
    return b ? gcd(b, a % b) : a;
}
inline double round(double x)
{
    const double sd = 100; // accuracy = 2 dp
    return int(x * sd + (x < 0 ? -0.5 : 0.5)) / sd;
}
inline int cmp(double x, double y = 0, double tol = EPS)
{
    return (x <= y + tol) ? (x + tol < y) ? -1 : 0 : 1;
}
template<typename T> inline void print(T *array, int size)
{
    printf("\tarray[] = [");

    for(int i = 0; i < size; ++i) {
        printf("%lld", (LL)array[i]);

        if(i < size - 1) printf(" ");
    }

    printf("]\n");
}
template<typename T> inline void print(T **array, int size1, int size2)
{
    printf("\tarray[][] = [");

    for(int i = 0; i < size1; ++i) {
        for(int j = 0; j < size2; ++j) {
            printf("%lld", (LL)array[i][j]);

            if(j < size2 - 1) printf(" ");
        }

        printf("]\n");
    }
}
/////////////////////////////////////////////////////////////////////////////
const int MAXC = 201, MAXD = 10E6+1, MAXP = 10E5+1;
int T;
int cc = 0;

bool can(double t, int C, int D, PII *pv)
{
	double position = -1;
	REP(i, C)
	{
		if (i == 0)
		{
			position = pv[i].fst - t;
			pv[i].snd--;
			//printf("\tinitial pos: %lf\n", position);
		}
		while(pv[i].snd>0)
		{
			//DBG("position:",position);
			//DBG(pv[i].fst+t,position+D,pv[i].fst,',',pv[i].snd);
			if ((pv[i].fst+t)<(position+D))
			{
				return false;
			}
			position = max(position+D, pv[i].fst-t);
			pv[i].snd--;
		}
	}
	return true;
}
int main()
{
    //clock_t start = clock();
    scanf("%d", &T);
    REP(cc, T) {
		int C,D;
		scanf("%d%d", &C, &D);
		
		PII pv[C];
		LL sum_V = 0LL;
		REP(i, C)
		{	
			int P,V;
			scanf("%d%d", &P,&V);
			pv[i] = mp(P,V);
			sum_V += V;
		}
		// copy array
		PII temp[C];
		memcpy(temp, pv, C*sizeof(PII));

		// binary search
		double t, lo = 0, hi = (sum_V-1)*D;
		REP(i, 50)
		{
			double mid = (lo + hi) / 2;
			if (can(mid, C, D, temp))
			{
				hi = mid;
			}
			else
			{
				lo = mid;
			}
			memcpy(temp, pv, C*sizeof(PII));
		}
		t = (lo + hi) / 2;

		// small input
		/*
		double t = 0;
		while(t<(sum_V-1)*D)
		{
			if (can(t, C, D, temp))
				break;
			memcpy(temp, pv, C*sizeof(PII));
			t += 0.5;
		}*/

        printf("Case #%d: %lf\n", cc + 1, t);
    }
    //fprintf(stderr, "*** Total time: %.3lf seconds ***\n",
    //        ((clock() - start) / (double) CLOCKS_PER_SEC));
    return 0;
}

#include<iostream>
#include<vector>
#include<complex>
using namespace std;

typedef complex<double> dataC;

#define forr(i,x,y) for(int i=(int)(x); i<=(int)(y); i++)
#define all(a) a.begin(), a.end()
#define sz(x) x.size()

const double PI=3.1415926535897932384626433832795; 
vector<int> a,b,ans;
int n,x,ost=0;

void fft(vector<dataC> &a,bool invert) {
 int n=sz(a);
 if(n==1) return;
 vector<dataC> a0(n/2),a1(n/2);
 forr(i,0,n/2-1) { a0[i]=a[i*2]; a1[i]=a[i*2+1]; }
 fft(a0,invert),fft(a1,invert);
 double ang=2*PI/n*(invert ? -1 : 1);
 dataC w(1),wpw(cos(ang),sin(ang));
 forr(i,0,n/2-1) {
  a[i]=a0[i]+w*a1[i]; a[i+n/2]=a0[i]-w*a1[i];
  if(invert) a[i]/=2,a[i+n/2]/=2;
  w*=wpw;
 }
}

void multDPF(vector<int> a,vector<int> b,vector<int> &res) {
 vector<dataC> fa(all(a)),fb(all(b));
 int n=1;
 while(n<max(sz(a),sz(b))) n<<=1;
 n<<=1;
 fa.resize(n),fb.resize(n),res.resize(n);
 fft(fa,false), fft(fb,false);
 forr(i,0,n-1) fa[i]*=fb[i];
 fft(fa,true);
 forr(i,0,n-1) res[i]=int(fa[i].real()+0.5);
}

int main() {
 freopen("input.txt","r",stdin);
 freopen("output.txt","w",stdout);
 scanf("%d",&n);
 forr(i,1,n) { scanf("%d",&x); a.push_back(x); } /* нужно что бы начиналось со степени меньшего порядка... */
 scanf("%d",&n);
 forr(i,1,n) { scanf("%d",&x); b.push_back(x); }
 multDPF(a,b,ans);
 forr(i,0,sz(ans)-1) { ans[i]+=ost; ost=ans[i]/10; ans[i]%=10; }
 while(sz(ans) && !ans[sz(ans)-1]) ans.pop_back();
 forr(i,0,sz(ans)-1) printf("%d",ans[i]);
}


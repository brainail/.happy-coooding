/* @begin_of_source_code */
/* @judge_id: 6401 10173 C++ */

# include <stdio.h>
# include <math.h>

typedef struct{
  double x,y;
}Point;

enum region { LEFT=0,RIGHT,BEHIND,BEYOND,ORIGIN,DESTINATION,BETWEEN};

int classify(Point p0,Point p1,Point p2)
{
  Point a,b;
  double t;
  a.x=p1.x-p0.x;
  a.y=p1.y-p0.y;
  b.x=p2.x-p0.x;
  b.y=p2.y-p0.y;
  t=a.x*b.y-a.y*b.x;
  if(t>0.0) return LEFT;
  if(t<0.0) return RIGHT;
  if((a.x*a.x+a.y*a.y)<(b.x*b.x+b.y*b.y)) return BEYOND;
  if((a.x>0.0 && b.x<0.0) || (a.x<0.0 && b.x>0.0)) return BEHIND;
  if((a.y>0.0 && b.y<0.0) || (a.y<0.0 && b.y>0.0)) return BEHIND;
  if(p0.x==p2.x && p0.y==p2.y) return ORIGIN;
  if(p1.x==p2.x && p1.y==p2.y) return DESTINATION;
  return BETWEEN;
}

void swap(Point *a,Point *b)
{
  Point t=*a;
  *a=*b;
  *b=t;
}

int GiftWrapHull(Point s[],int n)
{
  int a,i,m,c;
  for(a=0,i=1;i<n;i++)
    if(s[i].y<s[a].y || (s[i].y==s[a].y && s[i].x<s[a].x))
      a=i;
  s[n]=s[a];
  for(m=0;m<n;m++){
    swap(&s[a],&s[m]);
    a=m+1;
    for(i=m+2;i<=n;i++){
      c=classify(s[m],s[a],s[i]);
      if(c==RIGHT || c==BETWEEN)
	a=i;
    }
    if(a==n) break;
  }
  s[++m]=s[0];
  return m+1;
}

double dotProduct(Point a,Point b)
{
  return a.x*b.x+a.y*b.y;
}

int main(void)
{
  int n,m;
  Point p[1001];
  double x,y;
  double area,left,right,height;
  double tlr,th,tw,ta,aval;
  Point a,b,normal;
  int i,j;
  while(scanf("%d",&n)==1 && n){
    for(i=0;i<n;i++){
      scanf("%lf%lf",&x,&y);
      p[i].x=x;
      p[i].y=y;
    }
    if(n<=2) area=0.0;
    else{
      m=GiftWrapHull(p,n);
      area=-1;
      for(i=0;i<m-1;i++){
	a.x=p[i+1].x-p[i].x;
	a.y=p[i+1].y-p[i].y;
	aval=sqrt(dotProduct(a,a));
	a.x/=aval;
	a.y/=aval;
	left=right=height=0;
	for(j=0;j<m-1;j++){
	  b.x=p[j].x-p[i].x;
	  b.y=p[j].y-p[i].y;
	  tlr=dotProduct(a,b);
	  normal.x=a.y;
	  normal.y=-a.x;
	  th=dotProduct(normal,b);
	  if(th<0.0) th=-th;
	  if(tlr<left) left=tlr;
	  if(tlr>right) right=tlr;
	  if(th>height) height=th;
	}
	tw=right-left;
	ta=tw*height;
	if(area==-1 || ta<area) area=ta;
      }
    }
    printf("%.4lf\n",area);
  }
  return 0;
}

/* @end_of_source_code */

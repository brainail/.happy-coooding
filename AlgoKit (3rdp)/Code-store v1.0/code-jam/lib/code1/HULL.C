/* GiftWrap Convex Hull */

/* @begin_of_source_code */
/* @judge_id: 6401 681 C++ */

# include <stdio.h>
# include <math.h>

typedef struct{
  long x,y;
}Point;

enum region { LEFT=0,RIGHT,BEHIND,BEYOND,ORIGIN,DESTINATION,BETWEEN};

int classify(Point p0,Point p1,Point p2)
{
  Point a,b;
  long t;
  a.x=p1.x-p0.x;
  a.y=p1.y-p0.y;
  b.x=p2.x-p0.x;
  b.y=p2.y-p0.y;
  t=a.x*b.y-a.y*b.x;
  if(t>0) return LEFT;
  if(t<0) return RIGHT;
  if((a.x*a.x+a.y*a.y)<(b.x*b.x+b.y*b.y)) return BEYOND;
  if((a.x>0 && b.x<0) || (a.x<0 && b.x>0)) return BEHIND;
  if((a.y>0 && b.y<0) || (a.y<0 && b.y>0)) return BEHIND;
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
      if(c==RIGHT || c==BEYOND)
	a=i;
    }
    if(a==n) break;
  }
  s[++m]=s[0];
  return m+1;
}

int main(void)
{
  int T;
  int n,m;
  Point p[513];
  int i;
  scanf("%d",&T);
  printf("%d\n",T);
  while(T--){
    scanf("%d",&n);
    for(i=0;i<n;i++) scanf("%ld%ld",&p[i].x,&p[i].y);
    m=GiftWrapHull(p,n-1);
    printf("%d\n",m);
    for(i=0;i<m;i++) printf("%ld %ld\n",p[i].x,p[i].y);
    if(T){
      scanf("%*d");
      printf("-1\n");
    }
  }
  return 0;
}
/* @end_of_source_code */

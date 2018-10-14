/* Clipping */

/* @begin_of_source_code */
/* @judge_id: 6401 10084 C++ "Clipping" */

# include <stdio.h>
# include <math.h>
# include <string.h>

# define SIZE 61

typedef struct{
  double x,y;
}Point;

enum { LEFT=0,RIGHT,BEHIND,BEYOND,ORIGIN,DESTINATION,BETWEEN};
enum { COLLINEAR=0,PARALLEL,SKEW,SKEW_CROSS,SKEW_NO_CROSS};

/* p2 on which side of p1-p0 */
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

double dotProduct(Point a,Point b)
{
  return a.x*b.x+a.y*b.y;
}

/* intersection of b-a and d-c : t of b-a */
int intersect(Point a,Point b,Point c,Point d,double *t)
{
  double denom,num;
  int aclass;
  Point n,ba,ac;
  n.x=d.y-c.y;
  n.y=c.x-d.x;
  ba.x=b.x-a.x;
  ba.y=b.y-a.y;
  ac.x=a.x-c.x;
  ac.y=a.y-c.y;
  denom=dotProduct(n,ba);
  if(denom==0.0){
    aclass=classify(c,d,a);
    if(aclass==LEFT || aclass==RIGHT)
      return PARALLEL;
    else
      return COLLINEAR;
  }
  num=dotProduct(n,ac);
  *t=-num/denom;
  return SKEW;
}

/* clip polygon p[] using edge b-a */
int lineClip(Point a,Point b,Point p[],int n)
{
  Point r[SIZE];
  Point org,dest,crosspt;
  int orgIsInside,destIsInside;
  double t;
  int i,j;
  p[n]=p[0];
  for(i=j=0;i<n;i++){
    org=p[i];
    dest=p[i+1];
    orgIsInside=(classify(a,b,org)!=LEFT);
    destIsInside=(classify(a,b,dest)!=LEFT);
    if(orgIsInside!=destIsInside){
      intersect(a,b,org,dest,&t);
      crosspt.x=a.x+t*(b.x-a.x);
      crosspt.y=a.y+t*(b.y-a.y);
    }
    if(orgIsInside && destIsInside)
      r[j++]=dest;
    else if(orgIsInside && !destIsInside){
      if(org.x!=crosspt.x || org.y!=crosspt.y)
	r[j++]=crosspt;
    }
    else if(!orgIsInside && !destIsInside)
      ;
    else{
      r[j++]=crosspt;
      if(dest.x!=crosspt.x || dest.y!=crosspt.y)
	r[j++]=dest;
    }
  }
  for(i=0;i<j;i++)
    p[i]=r[i];
  return j;
}

double area(Point p[],int n)
{
  int i;
  double t;
  p[n]=p[0];
  for(t=0,i=1;i<=n;i++)
    t+=p[i-1].x*p[i].y-p[i].x*p[i-1].y;
  t/=2;
  if(t<0) t*=-1.0;
  return t;
}

int main(void)
{
  int m,n=4;
  Point p[SIZE]={{0,0},{0,10},{10,10},{10,0}};
  Point prev={0,0},next;
  Point mid,norm,ba,mn;
  char msg[10];
  double ta;
  while(scanf("%lf%lf%s",&next.x,&next.y,msg)==3){
    ba.x=next.x-prev.x;
    ba.y=next.y-prev.y;
    norm.x=-ba.y;
    norm.y=ba.x;
    mid.x=(prev.x+next.x)/2;
    mid.y=(prev.y+next.y)/2;
    mn.x=mid.x+norm.x;
    mn.y=mid.y+norm.y;
    if(strcmp(msg,"Same")==0){
      p[0]=mid;
      p[1]=mn;
      m=2;
    }
    else if(strcmp(msg,"Hotter")==0)
      m=lineClip(mid,mn,p,n);
    else
      m=lineClip(mn,mid,p,n);
    ta=area(p,m);
    printf("%.2lf\n",ta);
    prev=next;
    n=m;
  }
  return 0;
}

/* @end_of_source_code */

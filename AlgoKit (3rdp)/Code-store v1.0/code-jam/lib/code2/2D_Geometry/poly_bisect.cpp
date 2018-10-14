/*
 * Bisecting a Convex Polygon
 *
 * Author: Gilbert Lee
 *
 * Given a convex polygon, and a point that is on the polygon,
 * it returns the point on the polygon which is the endpoint of
 * the line which bisects the area of the polygon.
 *
 * Date: 22 January 2001
 *
 */

#include <stdio.h>
#include <math.h>

/* Maximum number of vertices in the polygon */
#define MAXVERTEX 100

/* For Floating point comparisons */
#define EPS 1E-8  

typedef struct{
  double x, y;
} Point;

Point polygon[MAXVERTEX];
int psize;

double area_poly(Point *p, int n){
  double sum = 0; int i, j;
  
  for(i = n-1, j = 0; j < n; i = j++)
    sum += p[i].x * p[j].y -
           p[i].y * p[j].x;
  return fabs(sum/2.0);
}

/* Given a point p, this function finds the edge of the polygon
   that p is on, and returns the index of the next point.  If the point
   is not on the polygon then the function returns -1 */

double edgenum(Point p){
  int i; double xratio, yratio;

  for(i = 0; i < psize; i++){
    xratio = (p.x - polygon[i].x)/(p.x-polygon[(i+1)%psize].x);
    yratio = (p.y-polygon[i].y)/(p.y-polygon[(i+1)%psize].y);
    if( fabs(xratio-yratio) < EPS) return (i+1)%psize;
  }
  return -1;
}

/* This is the function that finds the right point.  It is done by a
   binary search */
Point poly_bisect(Point p){
  Point tpoly[MAXVERTEX], ubound, lbound;
  double newarea, area = area_poly(polygon, psize)/2.0;
  int tsize = 0, startvertex = edgenum(p);
  
  /* if(startvertex == -1)   point is not on polygon */ 

  tpoly[0] = p;
  tpoly[1] = polygon[startvertex];
  tpoly[2] = polygon[(startvertex+1)%psize];
  tsize = 3;
  
  while(area_poly(tpoly, tsize) < area){
    tpoly[tsize] = polygon[(startvertex+tsize-1)%psize];
    tsize++;
  }

  newarea = area_poly(tpoly, tsize);
  lbound = tpoly[tsize-2];
  ubound = tpoly[tsize-1];

  /* This is where we can set the precision of the search */
  while(fabs(newarea - area) > EPS){
    if(newarea > area) ubound = tpoly[tsize-1];    
    else lbound = tpoly[tsize-1];

    tpoly[tsize-1].x = lbound.x + (ubound.x-lbound.x)/2.0;
    tpoly[tsize-1].y = lbound.y + (ubound.y-lbound.y)/2.0;
    newarea = area_poly(tpoly, tsize);
  }
  return tpoly[tsize-1];
}

int main(){
  int i; Point p; Point m;

  /* Read in the polygon */  
  while(scanf("%d", &psize) == 1 && psize > 2){
    for(i = 0; i < psize; i++)
      scanf("%lf %lf", &polygon[i].x, &polygon[i].y);
    scanf("%lf %lf", &p.x, &p.y);
    m = poly_bisect(p);
    printf("Area bisector point = (%f %f)\n", m.x, m.y);
  }
  return 0;
}

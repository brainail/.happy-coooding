/*
 * Convex Polygon Intersection
 *
 * Author: Howard Cheng
 *
 * This routine takes two convex polygon, and returns the intersection
 * which is also convex.  If the intersection contains less than
 * 3 points, it is considered empty.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* how close to call equal */
#define EPS 1E-8
#define SQR(x) ((x)*(x))

typedef struct {
  double x, y;
} Point;

/* Global point for computing convex hull */
Point start_p;

/* counterclockwise, clockwise, or undefined */
enum {CCW, CW, CNOT};

int ccw(Point a, Point b, Point c){
  double dx1 = b.x - a.x;  double dx2 = c.x - b.x;
  double dy1 = b.y - a.y;  double dy2 = c.y - b.y;
  double t1 = dy2 * dx1;
  double t2 = dy1 * dx2;

  if (fabs(t1 - t2) < EPS){
    if (dx1 * dx2 < 0 || dy1 * dy2 < 0) 
      if (SQR(dx1) + SQR(dy1) >= SQR(dx2) + SQR(dy2) - EPS)
        return CNOT;
      else 
        return CW;
    else 
      return CCW;
  }
  if (t1 > t2) return CCW;
  return CW;
}

int ccw_cmp(const void *a, const void *b){
  Point *p1 = (Point *)a;
  Point *p2 = (Point *)b;
  if (ccw(start_p, *p1, *p2) == CCW) return -1;
  if (ccw(start_p, *p2, *p1) == CCW) return 1;
  return 0;
}

int convex_hull(Point *p, int n, Point *hull) {
  int count, mini, i;

  start_p.x = p[0].x;
  start_p.y = p[0].y;
  for (mini = 0, i = 1; i < n; i++)
    if ((p[i].y < start_p.y) ||
        (p[i].y == start_p.y && p[i].x < start_p.x)) {
      start_p = p[i];
      mini = i;
    }
  p[mini] = p[0];
  p[0] = start_p;
  
  qsort((p+1), n-1, sizeof(Point), ccw_cmp);

  count = 0;
  hull[count] = p[count]; count++;
  hull[count] = p[count]; count++;
  for (i = 2; i < n; i++) {
    while (count > 1 &&
           ccw(hull[count-2], hull[count-1], p[i]) == CW) {
      count--;
    }
    hull[count++] = p[i];
  }
  return count;
}

int point_in_poly(Point *poly, int n, Point p){
  int i, j, c = 0;
  
  for (i = 0; i < n; i++)
    if (fabs(p.x - poly[i].x) < EPS && 
        fabs(p.y - poly[i].y) < EPS)
      return 1;
  
  for (i = n-1, j = 0; j < n; i=j++)
    if (ccw(poly[i], poly[j], p) == CNOT)
      return 1;
  
  for (i = 0, j = n-1; i < n; j = i++) {
    if (((poly[i].y <= p.y && p.y < poly[j].y) ||
         (poly[j].y <= p.y && p.y < poly[i].y)) &&
        (p.x < (poly[j].x - poly[i].x) * (p.y - poly[i].y)
             / (poly[j].y - poly[i].y) + poly[i].x))
      c = !c;
  }
  return c;
}

int intersect_line(Point a, Point b, Point c, Point d, Point *p){
  double r, s, denom, num1, num2;

  num1  = (a.y - c.y)*(d.x - c.x) - (a.x - c.x)*(d.y - c.y);
  num2  = (a.y - c.y)*(b.x - a.x) - (a.x - c.x)*(b.y - a.y);
  denom = (b.x - a.x)*(d.y - c.y) - (b.y - a.y)*(d.x - c.x);

  if (fabs(denom) >= EPS) {
    r = num1 / denom;
    s = num2 / denom;
    if (0-EPS <= r && r <= 1+EPS && 
	0-EPS <= s && s <= 1+EPS) {
      p->x = a.x + r*(b.x - a.x);
      p->y = a.y + r*(b.y - a.y);
      return 1;
    }
    return 0;
  }
  if (fabs(num1) >= EPS) return 0;
  return -1;
}

int intersect_polygon(Point *poly1, int n1, Point *poly2, int n2,
		      Point **out){
  Point *newpoly, p; char *used;
  int new_n = n1 + n2 + n1*n2;
  int count, i, j, new_count, n;
  
  newpoly = (Point *)malloc(new_n * sizeof(Point));
  *out    = (Point *)malloc(new_n * sizeof(Point));
  used    =          malloc(new_n * sizeof(Point));
  /* assert(newpoly && *out && used); */

  for (count = i = 0; i < new_n; i++) used[i] = 0;

  for (i = 0; i < n1; i++)
    if (point_in_poly(poly2, n2, poly1[i]))
      newpoly[count++] = poly1[i];
  
  for (i = 0; i < n2; i++) 
    if (point_in_poly(poly1, n1, poly2[i]))
      newpoly[count++] = poly2[i];

  for (i = 0; i < n1; i++) for (j = 0; j < n2; j++)
    if (intersect_line(poly1[i], poly1[(i+1)%n1],
		       poly2[j], poly2[(j+1)%n2], &p) == 1)
      newpoly[count++] = p;
  
  if (count >= 3) {
    n = convex_hull(newpoly, count, *out);
    if (n < 3) {
      free(*out);
      n = 0;
    }
  } else {
    free(*out);
    n = 0;
  }
  
  /* eliminate duplicates */
  for (i = 0; i < n-1; i++)
    for (j = i+1; j < n; j++)
      if ((*out)[i].x == (*out)[j].x &&
	  (*out)[i].y == (*out)[j].y)
        used[j] = 1;
  
  new_count = 0;
  for (i = 0; i < n; i++)
    if (!used[i]) (*out)[new_count++] = (*out)[i];
  n = new_count;
  free(used);
  free(newpoly);
  return n;
}

int read_poly(Point **poly){
  int n, i;
  
  scanf("%d", &n);
  if (n == 0) return 0;
  *poly = (Point *)malloc(n * sizeof(Point));
  /* assert(*poly); */
  for (i = 0; i < n; i++)
    scanf("%lf %lf", &((*poly)[i].x), &((*poly)[i].y));
  return n;
}

int main(void){
  Point *poly1, *poly2, *intersection;
  int n1, n2, n3, i;
  
  while ((n1 = read_poly(&poly1))) {
    n2 = read_poly(&poly2);
    n3 = intersect_polygon(poly1, n1, poly2, n2, &intersection);
    free(poly1);
    free(poly2);
    if (n3 >= 3) {
      for (i = 0; i < n3; i++) {
        printf("(%0.2f, %0.2f) ", intersection[i].x, intersection[i].y);
      }
      printf("\n");
      free(intersection);
    } else {
      printf("Empty Intersection\n");
    }
  }
  return 0;
}

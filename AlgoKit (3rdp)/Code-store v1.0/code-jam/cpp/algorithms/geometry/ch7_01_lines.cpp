#include <iostream>
#include <math.h>
using namespace std;

#define INF 1e9
#define EPS 1e-9
#define PI (2.0 * acos(0.0)) // important constant

double DEG_to_RAD(double d) { return d * PI / 180.0; }

double RAD_to_DEG(double r) { return r * 180.0 / PI; }

struct point { int x, y; }; // preferred mode
struct point_d { double x, y; };
struct vector { double x, y; }; // similar to point, but has different purpose
//struct vector_d { double x, y; };

// returns true if two point_d are equal, false otherwise
bool equal(point p1, point p2) {
  return p1.x == p2.x && p1.y == p2.y; // precise comparison
}

//bool equal(point_d p1, point_d p2) { // returns true if two point_d are equal, false otherwise
//  return fabs(p1.x - p2.x) < EPS && fabs(p1.y - p2.y) < EPS; // must use EPS
//}

struct line { double a, b, c; }; // one way to represent a line; x-coefficient, y-coefficient, constant term
void points_to_line(point p1, point p2, line *l) {
	if (p1.x == p2.x) { // vertical line, handled nicely here
		l->a = 1.0;
		l->b = 0.0;
		l->c = -(double)p1.x;
	}
  else {
		l->a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
    l->b = 1.0;
		l->c = -(double)(l->a * p1.x) - (l->b * p1.y);
	}
}

// not needed since we will use the more robust form: ax + by + c = 0
//struct line2 { double m, c; }; // another way to represent a line
//int points_to_line(point p1, point p2, line2 *l) { // returns 1 and line l contains value for m and c of the line equation y = mx + c;
//  if (p1.x == p2.x) { // vertical line             // returns 0 and line l contains m = INF and c = x_value to denote vertical line x = x_value
//    l->m = INF;
//    l->c = p1.x;
//    return 0; // we need this return variable to differentiate the type...
//  }
//  else {
//    l->m = (double)(p1.y - p2.y) / (p1.x - p2.x);
//    l->c = p1.y - l->m * p1.x;
//    return 1;
//  }
//}

void point_and_slope_to_line(point p, double m, line *l) { // convert point and gradient to line
	l->a = -m;
	l->b = 1;
	l->c = -((l->a * p.x) + (l->b * p.y));
}

bool parallel_line(line l1, line l2) { // returns true if two lines are parallel
	return (fabs(l1.a - l2.a) <= EPS) && (fabs(l1.b - l2.b) <= EPS);
}

bool same_line(line l1, line l2) { // returns true if two lines (not line segments) are the same
	return (parallel_line(l1 ,l2) && (fabs(l1.c - l2.c) <= EPS) );
}

void intersection_point(line l1, line l2, point_d *p) { // find the intersection point of two lines
	if (same_line(l1, l2)) {
		printf("Warning: Identical lines, all points intersect.\n");
		p->x = p->y = 0.0;
		return;
	}

	if (parallel_line(l1, l2)) {
		printf("Error: Distinct parallel lines do not intersect.\n");
		return;
	}

	p->x = (double)(l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
	if (fabs(l1.b) > EPS)	// test for vertical line
		p->y = - (l1.a * p->x + l1.c) / l1.b;
	else
		p->y = - (l2.a * p->x + l2.c) / l2.b;
}

int turn(point p, point q, point r) {
  int result = (r.x - q.x) * (p.y - q.y) - (r.y - q.y) * (p.x - q.x);
  if (result < 0) return -1; // P->Q->R is a right turn
  if (result > 0) return  1; // P->Q->R is a left turn
  return 0; // P->Q->R is a straight line, i.e. P, Q, R are collinear
}

//// another variant
//int area2(point a, point b, point c) { // returns 'twice' the area of this triangle a-b-c, or some people call this "cross" product
//  return a.x * b.y - a.y * b.x +
//         b.x * c.y - b.y * c.x +
//         c.x * a.y - c.y * a.x;
//}

bool collinear(point p, point q, point r) { // returns true if point r is on the same line as the line represented by point p and q
  return turn(p, q, r) == 0;
}

// note: sometime we change the '> 0' to '>= 0' to accept collinear points
bool ccw(point p, point q, point r) { // returns true if point c is on the left side of line represented by point a and b
  return turn(p, q, r) > 0;
}

double dist(point p1, point p2) { // returns Euclidean distance between two points
  double dx = (double)p1.x - p2.x, dy = (double)p1.y - p2.y;
  return hypot(dx, dy);
}

// Igor Naverniouk's library
// returns the distance from p to the line defined by two points a and b
// the closest point on the line is returned through point c
// does not work for degenerate lines (when answer is undefined)
double distToLine(point a, point b, point p, point_d *c) {
  // formula: cp = a + (p-a).(b-a) / |b-a| * (b-a)
  double proj = (double)((p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y)) /
                        ((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
  c->x = a.x + proj * (b.x - a.x);
  c->y = a.y + proj * (b.y - a.y);
  return hypot(p.x - c->x, p.y - c->y);
}

// Igor Naverniouk's library
// returns the distance from p to the line segment ab
// the closest point on ab is returned through point c
// works correctly for degenerate line segments (a == b)
double distToLineSegment(point a, point b, point p, point_d* c) {
  if ((b.x - a.x) * (p.x - a.x) + (b.y - a.y) * (p.y - a.y) < EPS) { // closer to a
    c->x = a.x;
    c->y = a.y;
    return hypot(a.x - p.x, a.y - p.y);
  }

  if ((a.x - b.x) * (p.x - b.x) + (a.y - b.y) * (p.y - b.y) < EPS) { // closer to b
    c->x = b.x;
    c->y = b.y;
    return hypot(b.x - p.x, b.y - p.y);
  }

  return distToLine(a, b, p, c); // in general
}

vector toVector(point_d p1, point_d p2) { // convert two points into a vector
  vector v = { p2.x - p1.x, p2.y - p1.y };
  return v;
}

point_d translate(point_d p, vector v) { // translate a point according to a vector
  point_d new_p = { p.x + v.x , p.y + v.y };
  return new_p;
}

point_d rotate(point_d p, double d) { // rotate p by d degrees w.r.t to origin (0, 0) in counter clockwise fashion
  // rotation matrix
  // R(theta) = [cos(theta) -sin(theta)]
  //            [sin(theta)  cos(theta)]
  point_d p_r = { p.x * cos(DEG_to_RAD(d)) - p.y * sin(DEG_to_RAD(d)),
                  p.x * sin(DEG_to_RAD(d)) + p.y * cos(DEG_to_RAD(d)) };
  return p_r;
}

int main() {
  // line equation
  point p1 = { 2, 2 };
  point p2 = { 4, 3 };
  line l1;
  points_to_line(p1, p2, &l1);
  printf("%.2lf * x + %.2lf * y + %.2lf = 0.00\n", l1.a, l1.b, l1.c); // should be 0.50 x - 1.00 y + 1.00 = 0.00

  point p3 = { 2, 4 };
  line l2;
  points_to_line(p1, p3, &l2); // vertical line
  printf("%.2lf * x + %.2lf * y + %.2lf = 0.00\n", l2.a, l2.b, l2.c); // should be 1.00 x + 0.00 y - 2.00 = 0.00

  // tests
  point p4 = { 6, 6 };
  line l3;
  points_to_line(p3, p4, &l3); // l1 and l3 are parallel
  printf("l1 & l2 parallel? %d\n", parallel_line(l1, l2)); // no
  printf("l1 & l3 parallel? %d\n", parallel_line(l1, l3)); // yes

  point p5 = { 2, 6 };
  line l4;
  points_to_line(p3, p5, &l4); // l2 and l4 are the same line (note, they are two different line segments, but same line)
  printf("l1 & l2 same? %d\n", same_line(l1, l2)); // no
  printf("l2 & l4 same? %d\n", same_line(l2, l4)); // yes

  point_d p34;
  intersection_point(l3, l4, &p34);
  printf("The intersection point between l3 and l4 is (%.2lf, %.2lf)\n", p34.x, p34.y);

  printf("p1, p3, p4 are collinear? %d\n", collinear(p1, p3, p4)); // no
  printf("p1, p3, p5 are collinear? %d\n", collinear(p1, p3, p5)); // yes

  printf("p1, p3, p4 form a left turn? %d\n", ccw(p1, p3, p4)); // no
  printf("p1, p4, p3 form a left turn? %d\n", ccw(p1, p4, p3)); // yes

  // distances
  point p6 = { 6, 5 };
  double d = dist(p1, p6);
  printf("d = %.2lf\n", d); // should be 5.000
  point_d p7;
  d = distToLine(p3, p4, p1, &p7);
  printf("Closest point from p1 to line         (p3-p4): (%.2lf, %.2lf), dist = %.2lf\n", p7.x, p7.y, d);
  d = distToLineSegment(p3, p4, p1, &p7);
  printf("Closest point from p1 to line SEGMENT (p3-p4): (%.2lf, %.2lf), dist = %.2lf\n", p7.x, p7.y, d);

  // translation
  point_d p1d = { p1.x, p1.y };
  point_d p2d = { p2.x, p2.y };
  vector v = toVector(p1d, p2d);
  point_d p8 = { 3.0, 2.0 };
  point_d p9 = translate(p8, v);
  printf("p9 = (%.2lf, %.2lf)\n", p9.x, p9.y);

  // rotation
  point_d p10 = { 2.0, 2.0 };
  printf("p10 = (%.2lf, %.2lf)\n", p10.x, p10.y);
  point_d p11 = rotate(p10, 90);
  printf("p11 = (%.2lf, %.2lf)\n", p11.x, p11.y);
  point_d p12 = rotate(p10, 180);
  printf("p12 = (%.2lf, %.2lf)\n", p12.x, p12.y);

  return 0;
}

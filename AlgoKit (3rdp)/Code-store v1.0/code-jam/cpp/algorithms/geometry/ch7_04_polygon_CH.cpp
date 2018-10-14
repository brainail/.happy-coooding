#include <algorithm>
#include <iostream>
#include <math.h>
#include <stack>
#include <vector>
using namespace std;

#define INF 1e9
#define EPS 1e-9
#define PI (2.0 * acos(0.0)) // important constant

double DEG_to_RAD(double d) { return d * PI / 180.0; }

double RAD_to_DEG(double r) { return r * 180.0 / PI; }

struct point { double x, y; }; // we use doubles for these examples

double dist(point p1, point p2) { // returns Euclidean distance between two points
  double dx = p1.x - p2.x, dy = p1.y - p2.y;
  return hypot(dx, dy);
}

double perimeter(vector<point> P) { // returns the perimeter (sum of Euclidean distances of consecutive line segments/polygon edges)
  double result = 0.0;
  for (int i = 0; i < (int)P.size(); i++)
    result += dist(P[i], P[(i + 1) % P.size()]);
  return result;
}

double area(vector<point> P) {
  double result = 0.0, x1, y1, x2, y2;
  for (int i = 0; i < (int)P.size(); i++) {
    x1 = P[i].x; x2 = P[(i + 1) % P.size()].x;
    y1 = P[i].y; y2 = P[(i + 1) % P.size()].y;
    result += (x1 * y2 - x2 * y1);
  }
  return fabs(result) / 2.0;
}

int turn(point p, point q, point r) {
  int result = (r.x - q.x) * (p.y - q.y) - (r.y - q.y) * (p.x - q.x);
  if (result < -EPS) return -1; // P->Q->R is a right turn
  if (result > EPS) return  1; // P->Q->R is a left turn
  return 0; // P->Q->R is a straight line, i.e. P, Q, R are collinear
}

bool collinear(point p, point q, point r) { // returns true if point r is on the same line as the line represented by point p and q
  return turn(p, q, r) == 0;
}

bool ccw(point p, point q, point r) { // returns true if point c is on the left side of line represented by point a and b
  return turn(p, q, r) > 0;
}

bool is_convex(vector<point> P) { // returns true if we always make the same turn while navigating all the edges of the polygon
  int sz = (int)P.size();
  if (sz < 3) // boundary case
    return false;

  int turn_value = turn(P[0], P[1], P[2]);
  for (int i = 1; i < (int)P.size(); i++)
    if (turn(P[i], P[(i + 1) % sz], P[(i + 2) % sz]) != turn_value)
      return false; // no, this polygon is not convex

  return true; // yes, this polygon is convex
}

double angle(point a, point b, point c) {
  double ux, uy, vx, vy;
  ux = b.x - a.x;
  uy = b.y - a.y;
  vx = c.x - a.x;
  vy = c.y - a.y;
  return acos((ux * vx + uy * vy) / sqrt((ux * ux + uy * uy) * (vx * vx + vy * vy)));
}

bool point_in_polygon(point p, vector<point> P) { // returns true if point p is in either convex/concave polygon P
  if ((int)P.size() == 0)
    return false;

  double sum = 0;
  for (int i = 0; i < (int)P.size() - 1; i++) {
    if (turn(p, P[i], P[i + 1]) < 0) sum -= angle(p, P[i], P[i + 1]);
    else                             sum += angle(p, P[i], P[i + 1]);
  }

  if (fabs(sum - 2 * PI) < EPS || fabs(sum + 2 * PI) < EPS)
    return true;
  return false;
}

// line segment p-q intersect with line A-B.
point lineIntersectSeg(point p, point q, point A, point B) {
  double a = B.y - A.y;
  double b = A.x - B.x;
  double c = B.x * A.y - A.x * B.y;
  double u = fabs(a * p.x + b * p.y + c);
  double v = fabs(a * q.x + b * q.y + c);
  point ans = { (p.x * v + q.x * u) / (u + v), (p.y * v + q.y * u) / (u + v) };
  return ans;
}

// cut up the polygon q with the along the line formed by a->b.
// a & b: two points that form a line segment
// q: given vector of point (the last point must be the same as first point)
vector<point> cut_polygon(point a, point b, vector<point> Q) {
  vector<point> P;
  for (int i = 0; i < (int)Q.size(); i++) {
    double left1 = turn(a, b, Q[i]);
    double left2 = 0.0;
    if (i != (int)Q.size() - 1)
      left2 = turn(a, b, Q[i + 1]);
    if (left1 > -EPS) {
      P.push_back(Q[i]);
    }
    if (left1 * left2 < -EPS)
      P.push_back(lineIntersectSeg(Q[i], Q[i + 1], a, b));
  }
  if (P.empty()) return P;
  if (fabs(P.back().x - P.front().x) > EPS || fabs(P.back().y - P.front().y) > EPS)
    P.push_back(P.front());
  return P;
}

point pivot;
bool angle_cmp(point a, point b) { // important angle-sorting function
  if (collinear(pivot, a, b))
    return dist(pivot, a) < dist(pivot, b); // which one is closer?

  double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
  double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
  return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0;
}

vector<point> GrahamScan(vector<point> P) {
  // first, find P0 = point with lowest Y and if tie: rightmost X
  int i, N = (int)P.size();
  if (N <= 3) // special case
    return P; // the convex hull should be P itself
  int P0 = 0;
  for (i = 1; i < N; i++)
    if (P[i].y  < P[P0].y ||
       (P[i].y == P[P0].y && P[i].x > P[P0].x))
      P0 = i;

  point temp = P[0]; // swap selected vertex with P[0]
  P[0] = P[P0];
  P[P0] = temp;

  // second, sort points by angle w.r.t. P0, skipping P [0]
  pivot = P[0]; // use this global variable as reference
  sort(++P.begin(), P.end(), angle_cmp);

  // third, the ccw tests
  stack<point> S;
  point prev, now;
  S.push(P[N - 1]); // put two starting vertices into stack S
  S.push(P[0]);

  i = 1; // and start checking the rest
  while (i < N) { // note: N must be >= 3 for this method to work
    now = S.top();
    S.pop(); prev = S.top(); S.push(now); // trick to get the 2nd item from top of S
    if (ccw(prev, now, P[i])) { // if these 3 points make a left turn
      S.push(P[i]); // accept
      i++;
    }
    else // otherwise
      S.pop(); // pop this point until we have a left turn
  }

  vector<point> ConvexHull;
  while (!S.empty()) { // from stack back to vector
    ConvexHull.push_back(S.top());
    S.pop();
  }
  ConvexHull.pop_back(); // the last one is a duplicate of first one

  return ConvexHull; // return the result
}

int main() {
  // 7 points, written in counter clockwise order
  point p1 = { 0, 0 };
  point p2 = { 1, 1 }; // not in CH
  point p3 = { 2, 2 }; // not in CH
  point p4 = { 10, 0 };
  point p5 = { 15, 5 };
  point p6 = { 10, 10 };
  point p7 = { 0, 10 };

  vector<point> P;
  P.push_back(p1);
  P.push_back(p2);
  P.push_back(p3);
  P.push_back(p4);
  P.push_back(p5);
  P.push_back(p6);
  P.push_back(p7);
  P.push_back(p1); // must loop back to itself (otherwise some functions do not work)

  printf("Perimeter of polygon = %.2lf\n", perimeter(P));
  printf("Area of polygon = %.2lf\n", area(P));
  printf("Is convex = %d\n", is_convex(P)); // false now

  point p8 = { 2, 1 }; // outside this (concave) polygon
  printf("Point p8 is inside this polygon = %d\n", point_in_polygon(p8, P)); // false now
  point p9 = { 2, 3 }; // inside this (concave) polygon
  printf("Point p9 is inside this polygon = %d\n", point_in_polygon(p9, P)); // true

  // cutting the original polygon based on line p4 -> p6 (get the left side)
  P = cut_polygon(p4, p6, P);
  printf("Perimeter of polygon = %.2lf\n", perimeter(P)); // smaller now
  printf("Area of polygon = %.2lf\n", area(P));

  // running convex hull
  P = GrahamScan(P); // now this is a square
  printf("Perimeter of polygon = %.2lf\n", perimeter(P)); // smaller now
  printf("Area of polygon = %.2lf\n", area(P));
  printf("Is convex = %d\n", is_convex(P)); // true now

  return 0;
}

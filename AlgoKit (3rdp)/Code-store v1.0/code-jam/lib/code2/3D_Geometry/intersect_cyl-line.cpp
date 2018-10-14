/*
 * Intersection of a line and an infinite cylinder.
 *
 * Modified by: Scott Crosshwite
 * Reference:
 *   `Modified' C++ code which was located at:
 *     http://www.magic-software.com/src/graphics/intr/linecyln.cpp
 *   or alternatively at:
 *     http://www.magic-software.com/
 *     under the category "Computer Graphics" in the subsection
 *     "Intersection".
 *   The author was Dave Eberly, who obtained at least some of the
 *     contents of this page from comp.graphics.algorithms.
 *   Actually, the only modifications that were made were to the
 *     comments and to slightly modify some of the C++ sematics so that
 *     the C compiler wouldn't complain. Oh yes, and I prefer doubles
 *     to floats.
 *
 * Description:
 *   Expanded description below.
 *
 * Problems:
 *  - Infinite interesections returned as 1 intersection that is NaN.
 *  - Doesn't do point-cylinder intersection very well. :-)
 *    ie) returns 1 intersection that is NaN.  Obviously, it is impossible
 *        to distiguish between these 2 based on the result... however, it
 *        should usually be infinite.
 *  - Doesn't recognise values less that 0.0001... I think it's because
 *    they get squared, and if they are any lower, it puts them below
 *    the 1E-8 threshold I set.
 *  - No intersection reported as 1 intersection at (NaN, NaN, NaN)
 *    I guess that will have to be fixed up
 *
 * Date: April 24, 1999
 * Comments (problems) updated 15 June 1999 by RK
 *
 * WARNING: In incoming
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/* A description of how this algorithm works, cut and pasted from the
 * original code, since I had no desire to type it out myself:

// General quadric equation is X^T A X + B^T X + C = 0 where A is a 3x3
// symmetric matrix, B is a 3x1 vector, and C is a scalar.  X is a 3x1
// vector of unknowns.  Factor A = R^T D R using an eigendecomposition
// where R is an orthonormal matrix and D = diag(d0,d1,d2) is a diagonal
// matrix.  Define E = RB and Y = RX.  The quadric becomes
//
//   Y^T D Y + E^T Y + C = 0
//
// Let Y = (y0,y1,y2) and E = (e0,e1,e2).  If d0 = d1 = 1 and d2 = 0 and
// e2 = 0, the equation describes a cylinder.  The last row of R is the
// cylinder axis (last row corresponds to eigenvalue d2 = 0).  Completing
// the square yields
//
//   (y0+0.5*e0)^2 + (y1+0.5*e1)^2 = 0.25*(e0^2+e1^2) - C.
//
// If the right-hand side is positive, then the cylinder squared radius
// is the right-hand side.  A point on the cylinder axis is -(e0,e1,0)/2
// = -E/2, where the components are in the Y coordinate system.  In the
// original X coordinates, the point is P = -R^T E/2.  The direction of
// the cylinder axis is (0,0,1) in the Y coordinate system.  In the X
// coordinate system, the axis is F = R^T (0,0,1) [the last row of R).
//
//
// The reverse problem is to specify the cylinder axis P+t*F and radius
// r, then compute the corresponding quadric equation X^T A X + B^T X + C
// = 0.  Choose vectors U and V so that U, V, and F form an orthonormal
// set.  Transpose of orthogonal matrix is R^T = [U V F] where U, V, and
// F are the columns of the matrix.  Diagonal matrix is D = diag(1,1,0).
// E = -2*R*P implies B = R^T E = -2*P.  Matrix A = R^T D R.  Finally,
// r^2 = 0.25*(e0^2+e1^2)-C implies C = 0.25*(e0^2+e1^2)-r^2.
//
//
// Given a line X(t) = Q+t*G and quadric equation X^T A X + B^T X + C = 0,
// plug in X(t) to get
//
//   (G^T A G) t^2 + (B^T G + 2 Q^T A G) t + (Q^T A Q + B^T Q + C) = 0.
//
// or c0+c1*t+c2*t^2.  Solve for t.  If two distinct real roots, line
// intersects cylinder in two points.  If one repeated real root, line
// is tangent to cylinder.  If no real roots, line and cylinder do not
// intersect.
*
*/


/* Defined Values */

#define EPS 1E-8

/* Type Definitions */

typedef struct {
  double x, y, z;
} Point;

typedef struct {
  Point origin, direction;
} Line;

typedef struct {
  Line axis;
  double radius;
} Cylinder;


/* Procedures and functions */

/* The main function.  Note that the variable intersection requires
 * space for 2 points.
 */
void IntersectLineCylinder (Line *line, Cylinder *cylinder,
    int *numIntersections, Point *intersection)
{
  Point U, V, F = cylinder->axis.direction, P, B, Q, G, AG, AQ;
  double length, invLength, prod;
  double R[3][3], A[3][3];
  double e0, e1, C, c0, c1, c2, discr, invC2, root0, root1, root;

  /* choose U, V so that U,V,F is orthonormal set */

  if ( fabs(F.x) > fabs(F.y) && fabs(F.x) > fabs(F.z) )
    {
      length = sqrt(F.x*F.x+F.y*F.y);
      invLength = 1.0/length;
      U.x = -F.y*invLength;
      U.y = +F.x*invLength;
      U.z = 0.0;
      prod = -F.z*invLength;
      V.x = F.x*prod;
      V.y = F.y*prod;
      V.z = length;
    }
  else
    {
      length = sqrt(F.y*F.y+F.z*F.z);
      invLength = 1.0/length;
      U.x = 0.0;
      U.y = -F.z*invLength;
      U.z = +F.y*invLength;
      prod = -F.x*invLength;
      V.x = length;
      V.y = F.y*prod;
      V.z = F.z*prod;
    }
  
  /* orthonormal matrix */
  R[0][0] = U.x;  R[0][1] = U.y;  R[0][2] = U.z;
  R[1][0] = V.x;  R[1][1] = V.y;  R[1][2] = V.z;
  R[2][0] = F.x;  R[2][1] = F.y;  R[2][2] = F.z;

  /* matrix A */
  A[0][0] = R[0][0]*R[0][0]+R[1][0]*R[1][0];
  A[0][1] = R[0][0]*R[0][1]+R[1][0]*R[1][1];
  A[0][2] = R[0][0]*R[0][2]+R[1][0]*R[1][2];

  A[1][0] = R[0][1]*R[0][0]+R[1][1]*R[1][0];
  A[1][1] = R[0][1]*R[0][1]+R[1][1]*R[1][1];
  A[1][2] = R[0][1]*R[0][2]+R[1][1]*R[1][2];

  A[2][0] = R[0][2]*R[0][0]+R[1][2]*R[1][0];
  A[2][1] = R[0][2]*R[0][1]+R[1][2]*R[1][1];
  A[2][2] = R[0][2]*R[0][2]+R[1][2]*R[1][2];

  /* vector B */
  P = cylinder->axis.origin;
  B.x = -2.0*P.x;  B.y = -2.0*P.y;  B.z = -2.0*P.z;

  /* constant C */
  e0 = -2.0*(R[0][0]*P.x+R[0][1]*P.y+R[0][2]*P.z);
  e1 = -2.0*(R[1][0]*P.x+R[1][1]*P.y+R[1][2]*P.z);
  C = 0.25*(e0*e0+e1*e1) - cylinder->radius*cylinder->radius;

  /* line */
  Q = line->origin;
  G = line->direction;

  /* compute A*G */
  AG.x = A[0][0]*G.x+A[0][1]*G.y+A[0][2]*G.z;
  AG.y = A[1][0]*G.x+A[1][1]*G.y+A[1][2]*G.z;
  AG.z = A[2][0]*G.x+A[2][1]*G.y+A[2][2]*G.z;

  /* compute A*Q */
  AQ.x = A[0][0]*Q.x+A[0][1]*Q.y+A[0][2]*Q.z;
  AQ.y = A[1][0]*Q.x+A[1][1]*Q.y+A[1][2]*Q.z;
  AQ.z = A[2][0]*Q.x+A[2][1]*Q.y+A[2][2]*Q.z;

  /* compute quadratic equation c0+c1*t+c2*t^2 = 0 */
  c2 = G.x*AG.x+G.y*AG.y+G.z*AG.z;
  c1 = B.x*G.x+B.y*G.y+B.z*G.z+2.0f*(Q.x*AG.x+Q.y*AG.y+Q.z*AG.z);
  c0 = Q.x*AQ.x+Q.y*AQ.y+Q.z*AQ.z+B.x*Q.x+B.y*Q.y+B.z*Q.z+C;

  /* solve for intersections */
  discr = c1*c1-4.0*c0*c2;
  if ( discr > EPS )
    {
      *numIntersections = 2;
      discr = sqrt(discr);
      invC2 = 1.0/c2;
      root0 = -0.5*(c1+discr)*invC2;
      root1 = -0.5*(c1-discr)*invC2;
      intersection[0].x = Q.x+root0*G.x;
      intersection[0].y = Q.y+root0*G.y;
      intersection[0].z = Q.z+root0*G.z;
      intersection[1].x = Q.x+root1*G.x;
      intersection[1].y = Q.y+root1*G.y;
      intersection[1].z = Q.z+root1*G.z;
    }
  else if ( discr < -EPS )
    {
      *numIntersections = 0;
    }
  else
    {
      *numIntersections = 1;
      root = -0.5*c1/c2;
      intersection[0].x = Q.x+root*G.x;
      intersection[0].y = Q.y+root*G.y;
      intersection[0].z = Q.z+root*G.z;
    }
}


/* Our test main() function. */

int main ()
{
  Line line;
  Point intersection[2];
  Cylinder cylinder;
  int numIntersections, i;
  
  line.origin.x = 0.0;
  line.origin.y = 0.0;
  line.origin.z = 0.0;
  line.direction.x = 1.0;
  line.direction.y = 0.0;
  line.direction.z = 0.0;
  
  cylinder.axis.origin.x = 0.0;
  cylinder.axis.origin.y = 0.0;
  cylinder.axis.origin.z = 0.0;
  cylinder.axis.direction.x = 0.0;
  cylinder.axis.direction.y = 0.0;
  cylinder.axis.direction.z = 1.0;
  cylinder.radius = 1.0;
  
  IntersectLineCylinder(&line, &cylinder, &numIntersections, intersection);

  printf("Results: \n");

  printf("\tNumber of intersections: %d\n", numIntersections);

  for (i=0; i<numIntersections; i++) {
    printf("\tPoint %d of intersection: (%.3f, %.3f, %.3f)\n", i+1,
	   intersection[i].x, intersection[i].y, intersection[i].z);
  }
  return 0;
}

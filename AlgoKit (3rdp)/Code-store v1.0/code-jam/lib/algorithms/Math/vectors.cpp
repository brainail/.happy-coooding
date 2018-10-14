#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>

#define REP(i,n) for((i)=0; (i)<(n); (i)++)
#define REPB(i,n) for((i)=(n)-1; (i)>=0; (i)--)

#define min(X,Y) ( ((X)<(Y)) ? (X) : (Y) )
#define max(X,Y) ( ((X)>(Y)) ? (X) : (Y) )

#define SIZE 50
#define DIMS 2
#define PI 3.141592
#define PREC 10E6
#define EQ(X,Y) ( ((int)round(PREC*X)) == ((int)round(PREC*Y)) )
#define LT(X,Y) ( ((int)round(PREC*X)) < ((int)round(PREC*Y)) )
#define GT(X,Y) ( ((int)round(PREC*X)) > ((int)round(PREC*Y)) )

int dims=DIMS;

void diff(double *r, double *a, double *b) {
    int i;
    REP(i,dims) {
        r[i] = a[i]-b[i];
    }
}

void sumv(double *r, double *a, double *b) {
    int i;
    REP(i,dims) {
        r[i]=a[i]+b[i];
    }
}

double norm(double *a) {
    double r=0;
    int i;
    REP(i,dims) {
        r += a[i]*a[i];
    }
    return sqrt(r);
}

double dotp(double *a, double *b) {
    double r=0;
    int i;
    REP(i,dims) {
        r += a[i]*b[i];
    }
    return r;
}

void multv(double *res, double *v, double scalar) {
    int i;
    REP(i,dims) {
        res[i] = v[i]*scalar;
    }
}

double vect_ang(double *a, double *b) {
    double r = acos( dotp(a,b)/(norm(a),norm(b)) );
    r = r*180/PI;
    r = round(100*r)/100.0;
    if (r < 0) r+=180;
    return r;
}

double dist(double *a, double *b) {
    double d[DIMS];
    diff(d,b,a);
    return norm(d);
}

void cp_v(double *dest, double *org) {
    int i;
    REP(i,dims) {
        dest[i] = org[i];
    }
}

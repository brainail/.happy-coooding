#include<iostream>
#include<math.h>
#include<stdlib.h>
using namespace std;

/*  Watch out the coordinates are integers! */
struct Point{
  int x,y; };

/*  The cross product: (p1-p) X (p2-p): Zero if parallel */
int CrossProduct(Point p1, Point p2, Point p)
{ return ((p1.x-p.x)*(p2.y-p.y) - (p2.x-p.x)*(p1.y-p.y)); }

istream &operator>>(istream &is, Point &p){
  is>>p.x>>p.y;
  return is;
}

ostream &operator<<(ostream &os, Point &p){
  os<<"("<<p.x<<","<<p.y<<")";
  return os;
}

/* -1 => _p1<_p2; 1 => _p1>_p2; 0 => _p1=_p2; */
int comparePoints(const void *_p1, const void *_p2)
{
  Point p1 = *((Point *)_p1);
  Point p2 = *((Point *)_p2);
  if(p1.x<p2.x)
    if(p1.y<p2.y)
      return 1;
    else
      return -1;
  else if(p1.x>p2.x)
    if(p1.y<=p2.y)
      return 1;
    else
      return -1;
  else
    if(p1.y<p2.y)
      return 1;
    else if(p1.y>p2.y)
      return -1;
    else
      return 0;
}

void LargestSetOfPointsOverALine(Point **points, int nPoints)
{
  Point tempAlignedPoints[nPoints];
  Point alignedPoints[nPoints];
  int max = 0, count;
  for(int i=0; i<nPoints; i++)
    for(int j=i+1; j<nPoints; j++)
    {
      count = 0;
      for(int k=j+1; k<nPoints; k++)
      {
//        if( k == i || k == j ) continue;
        if( CrossProduct((*points[i]),(*points[j]),(*points[k])) == 0 )
          tempAlignedPoints[count++] = *points[k];
      }
      if(count > max)
      {
        for(int x = 0; x<count; x++)
          alignedPoints[x] = tempAlignedPoints[x];
        alignedPoints[count++] = *points[i];
        alignedPoints[count++] = *points[j];
        max = count;
      }
    }
  cout<<"The largest set of points over a line has "<<max<<" elements. The points are:"<<endl;
  qsort(alignedPoints, max, sizeof(Point), comparePoints);
  for(int i=0; i<max; i++)
    cout<<(alignedPoints[i])<<endl;
}

int main(){
  int i,nPoints;
  while(!cin.eof()){
    cin>>nPoints;
    if(!nPoints) break;
    Point *points[nPoints];
    Point *p;
    for(i=0;i<nPoints;i++){
      p = new Point;
      cin>>(*p);
      points[i] = p;
    }
    LargestSetOfPointsOverALine(points, nPoints);
  }
  return 0;
}

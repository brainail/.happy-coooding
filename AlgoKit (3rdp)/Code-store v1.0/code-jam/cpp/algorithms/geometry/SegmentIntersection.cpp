#include<iostream>
using namespace std;

/*  Watch out the coordinates are integers! */
int maxi(int x, int y){
  return ((x>y)?x:y); }

int mini(int x, int y){
  return ((x<y)?x:y); }

struct Point{
  int x,y; };

struct Segment{
  Point p1,p2; };

bool isInBoundingBox(Segment s, Point p){
  if((mini(s.p1.x,s.p2.x)<=p.x && p.x<=maxi(s.p1.x,s.p2.x)) &&
     (mini(s.p1.y,s.p2.y)<=p.y && p.y<=maxi(s.p1.y,s.p2.y)))
    return true;
  return false;
}

/*  The cross product: (pk-pi) X (pj-pi): Is zero if
parallel segments*/
int CrossProduct(Point pi, Point pj, Point pk){
  return ((pk.x-pi.x)*(pj.y-pi.y) - (pj.x-pi.x)*(pk.y-pi.y));
}

bool isIntersection(Segment s1, Segment s2){
  int d1,d2,d3,d4;
  d1 = CrossProduct(s1.p1, s1.p2, s2.p1);
  d2 = CrossProduct(s1.p1, s1.p2, s2.p2);
  d3 = CrossProduct(s2.p1, s2.p2, s1.p1);
  d4 = CrossProduct(s2.p1, s2.p2, s1.p2);
  
  if( ((d1>0 && d2<0) || (d1<0 && d2>0)) && 
      ((d3>0 && d4<0) || (d3<0 && d4>0)) )
    return true;
  
  if((d1==0 && isInBoundingBox(s1,s2.p1)) || 
     (d2==0 && isInBoundingBox(s1,s2.p2)) ||
     (d3==0 && isInBoundingBox(s2,s1.p1)) ||
     (d4==0 && isInBoundingBox(s2,s1.p2)) )
    return true;
  
  return false;
}

istream &operator>>(istream &is, Point &p){
  is>>p.x>>p.y;
  return is;
}

istream &operator>>(istream &is, Segment &s){
  is>>s.p1>>s.p2;
  return is;
}

int main(){
  int c;
  c = 0;
  Segment s1,s2;
  while(!cin.eof()){
    cin>>s1; // using operator oeverload!  :)
    if(cin.eof()) break;
    cin>>s2; // using operator oeverload!  :)
    cout<<"Case #"<<++c<<":"<<endl;
    if(isIntersection(s1,s2))
      cout<<"Yes.";
    else 
      cout<<"No.";
    cout<<endl;
  }
  return 0;
}
